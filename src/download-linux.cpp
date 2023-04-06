#include "arachneconfigdownloaderapplication.h"
#include "settings.h"
#include "dbus_extra.h"

#include <QTemporaryFile>
#include <QFileInfo>
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>
#include <QtDBus/QDBusVariant>
#include <QtDBus/QDBusObjectPath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaType>
#include <QTextStream>
#include <QIODevice>
#include <KIO/CopyJob>

void ArachneConfigDownloaderApplication::onDownloadNow()
{
    Settings &settings = Settings::getInstance();

    QString url = settings.adminServerUrl()
            + ArachneConfigDownloaderApplication::USER_CONFIG_API_PATH
            + "?json";
    QUrl dest;
    if (settings.downloadType() == Settings::DownloadType::NETWORK_MANAGER) {
        QTemporaryFile tmpFile;
        tmpFile.open();
        dest = QUrl("file://" + tmpFile.fileName());
        tmpFile.close();
    }
    else {
        QString dir = settings.downloadDestination();
        dir.replace("~", QDir::homePath());
        qDebug() << dir;
        QFileInfo fileInfo(dir);
        if (!fileInfo.exists()) {
            QDir d("");
            d.mkpath(dir);
        }
        dest = QUrl("file://" + dir);
    }
    qDebug() << "Downloading " << url << " to " << dest.toString();
    KIO::CopyJob *copyJob = KIO::copy(QUrl(url), dest, KIO::Overwrite | KIO::DefaultFlags);

    if (copyJob != NULL) {
        copyJob->setUiDelegateExtension(0);
        connect(copyJob, &KIO::CopyJob::result,
                this, &ArachneConfigDownloaderApplication::onDownloadJobResult);
        if (settings.downloadType() == Settings::DownloadType::NETWORK_MANAGER) {
            connect(copyJob, &KIO::CopyJob::copyingDone,
                    this, &ArachneConfigDownloaderApplication::networkManagerCopyJobDone);
        }

    }
    else {
        qDebug() << "Cannot create copy job.";
    }

}

void ArachneConfigDownloaderApplication::onDownloadJobResult(KJob* job)
{
    KIO::CopyJob *copyJob = reinterpret_cast<KIO::CopyJob*>(job);

    if (job->error() == 0) {
        qDebug() << "File copied to" << copyJob->destUrl().path();
    }
    else {
        qDebug() << "Job finished with error " << job->error() << job->errorString();
   }
}

void addKeyValue(QDBusArgument &arg, const QString &key, const QVariant &value)
{
    arg.beginStructure();
    arg << key << QDBusVariant(value);
    arg.endStructure();
}

void ArachneConfigDownloaderApplication::networkManagerCopyJobDone(
        KIO::Job*, const QUrl &, const QUrl &to, const QDateTime&, bool, bool
        )
{
    QFile f(to.path());
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonStr(f.readAll());
    f.close();
    f.remove();

    QString conUuid = Settings::getInstance().connectionUuid();
    qDebug() << "Found connetioUuid in settings: " << conUuid;
    if (conUuid.isEmpty())
        addNetworkManagerConnection(jsonStr);
    else
        updateNetworkManagerConnection(conUuid, jsonStr);
}

void ArachneConfigDownloaderApplication::buildDBusArgument(
        QDBusArgument &arg,
        const QByteArray&json,
        const QString &conUuid)
{
    Settings &settings = Settings::getInstance();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &jsonError);
    if (jsonDoc.isNull()) {
        QString msg = QString("Cannot parse json at %1: %2")
                .arg(jsonError.offset)
                .arg(jsonError.error);
       throw NMException(msg);
    }
    QJsonObject jsonObj = jsonDoc.object();
    QString connectionName = jsonObj.take("name").toString();
    if (connectionName.isEmpty())
        throw NMException("No connection name provided");
    QJsonValue value = jsonObj.take("certificates");
    if (value.isUndefined()) {
        throw NMException("No connection found in json");
    }
    QJsonObject connectionObj = value.toObject();
    QString userCert = connectionObj.take("userCert").toString();
    if (userCert.isEmpty())
        throw NMException("No userCert privided in json");
    QString caCert = connectionObj.take("caCert").toString();
    if (caCert.isEmpty())
        throw NMException("No caCert provided in json");
    QString privateKey = connectionObj.take("privateKey").toString();
    if (privateKey.isEmpty())
        throw NMException("No privateKey provided in jsoin");

    QJsonObject dataObj = jsonObj.take("connection").toObject();
    if (dataObj.isEmpty())
        throw NMException("No connction data provided in json");

    QString caFileName(settings.certsFolder() + "/arachne-ca.crt");
    QString certFileName(settings.certsFolder() + "/arachne-cert.crt");
    QString keyFileName(settings.certsFolder() + "/arachne-cert.key");

    createFile(caFileName, caCert);
    createFile(certFileName, userCert);
    createFile(keyFileName, privateKey, true);

    ConnectionSettings c;
    QMap<QString, QVariant> conSettings = {
        {"id", connectionName},
        {"type", "vpn"},
        {"autoconnect", false},
        {"permissions", QVariant(QList<QString>{
             "user:claas"
         })
        }
    };
    if (!conUuid.isEmpty())
        conSettings.insert("uuid", conUuid);

    c.insert("connection", conSettings);
    StringMap data;
    data.insert("ca", caFileName);
    data.insert("cert", certFileName);
    data.insert("key", keyFileName);
    for (const QString &key : dataObj.keys()) {
        QString value = dataObj.value(key).toString();
        qDebug().noquote().nospace() << "Data setting " << key << "=" << value;
        data.insert(key, value);
    }


    c.insert("vpn", QMap<QString,QVariant>{
                {"service-type", "org.freedesktop.NetworkManager.openvpn"},
                 {"data", QVariant::fromValue(data)}
             });
    arg << c;
}

void ArachneConfigDownloaderApplication::updateNetworkManagerConnection(
        const QString &conUuid,
        const QByteArray&json)
{
    qDebug() << "Adding connection";
    QDBusArgument arg;
    try {
        buildDBusArgument(arg, json, conUuid);
    }
    catch (NMException ex) {
        qWarning() << ex.msg();
        return;
    }

    try {
        QString conPath = dbus_call<QDBusObjectPath>(
                    QString("org.freedesktop.NetworkManager"),
                    QString("/org/freedesktop/NetworkManager/Settings"),
                    QString("org.freedesktop.NetworkManager.Settings"),
                    QString("GetConnectionByUuid"), QVariant(conUuid)
                    )
                .value().path();
        qDebug() << "Found connection:" << conPath;
        if (conPath.isEmpty()) {
            qDebug()
                    << "No connection found with uuid "
                    << conUuid
                    << ", creating new one";
            addNetworkManagerConnection(json);
            return;
        }

        dbus_call<void>(
                            QString("org.freedesktop.NetworkManager"),
                            conPath,
                            QString("org.freedesktop.NetworkManager.Settings.Connection"),
                            QString("Update"), QVariant::fromValue(arg)
                            );
        qDebug() << "Connection" << conUuid << "updated";
    }
    catch (DBusException ex) {
        qWarning() << ex.msg();
        addNetworkManagerConnection(json);
    }
}

void ArachneConfigDownloaderApplication::addNetworkManagerConnection(const QByteArray&json)
{
    Settings &settings = Settings::getInstance();

    qDebug() << "Adding connection";
    QDBusArgument arg;
    try {
        buildDBusArgument(arg, json);
    }
    catch (NMException ex) {
        qWarning() << ex.msg();
        return;
    }

    try {
        QString conPath = dbus_call<QDBusObjectPath>(
                    QString("org.freedesktop.NetworkManager"),
                    QString("/org/freedesktop/NetworkManager/Settings"),
                    QString("org.freedesktop.NetworkManager.Settings"),
                    QString("AddConnection"), QVariant::fromValue(arg)
                    )
                .value().path();

        QString conUuid = dbus_call<ConnectionSettings>(
                    QString("org.freedesktop.NetworkManager"),
                    conPath,
                    QString("org.freedesktop.NetworkManager.Settings.Connection"),
                    QString("GetSettings"), QVariant())
                .value()
                .value("connection")
                .value("uuid")
                .toString();
        qDebug() << conUuid;
        settings.setConnectionUuid(conUuid);
    }
    catch (DBusException ex) {
        qWarning() << ex.msg();
    }
}

void ArachneConfigDownloaderApplication::createFile(
        const QString &fileName,
        const QString &content,
        bool isPrivate
        )
{
    QString absFileName(fileName);
    if (fileName.startsWith("~"))
        absFileName.replace("~", QDir::homePath());
    QFileInfo fi(absFileName);

    QDir dir;
    if (!dir.mkpath(fi.dir().absolutePath()))
        throw NMException("Cannot create folder " + fi.dir().absolutePath());

    qDebug() << "Writing " << fileName;
    QFile f(absFileName);
    if (!f.open(QIODevice::WriteOnly | QFileDevice::Text))
        throw NMException("Cannot open " + absFileName);
    QTextStream stream(&f);
    stream << content;
    f.close();

    if (isPrivate)
        f.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
}
