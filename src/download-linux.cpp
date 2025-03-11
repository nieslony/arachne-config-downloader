#include "arachneconfigdownloaderapplication.h"
#include "settings.h"
#include "dbus_extra.h"
#include "nmconnection.h"

#include <QTemporaryFile>
#include <QFileInfo>
#include <QUrl>
#include <QHostAddress>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QtEndian>
#include <QJsonArray>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>
#include <QtDBus/QDBusVariant>
#include <QtDBus/QDBusObjectPath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSystemTrayIcon>
#include <QTimeZone>
#include <QMetaType>
#include <QTextStream>
#include <QIODevice>
#include <KIO/CopyJob>
#include <KJobUiDelegate>
#include <QSequentialIterable>

#include <unistd.h>

struct NmConfiguration {
    QString conName;
    QString conType;
    QString conUuid;
};

bool ArachneConfigDownloaderApplication::isNmConnectionValid(const Settings&)
{
    QList<NmConnection> activeCons = NmConnection::activeNmConnections();
    QList<NmConnection> allCons = NmConnection::allNmConnections();

    return false;
}

void ArachneConfigDownloaderApplication::onDownloadNow()
{
    Settings &settings = Settings::getInstance();
    if (!isNmConnectionValid(settings))
        return;

    QString url = settings.adminServerUrl()
            + ArachneConfigDownloaderApplication::USER_CONFIG_API_PATH
            + QString::fromUtf8("?format=json");
    QUrl dest;
    if (settings.downloadType() == Settings::DownloadType::NETWORK_MANAGER) {
        QTemporaryFile tmpFile;
        tmpFile.open();
        dest = QUrl(QString::fromUtf8("file://") + tmpFile.fileName());
        tmpFile.close();
    }
    else {
        QString dir = settings.downloadDestination();
        dir.replace(QString::fromUtf8("~"), QDir::homePath());
        qDebug() << dir;
        QFileInfo fileInfo(dir);
        if (!fileInfo.exists()) {
            QDir d;
            d.mkpath(dir);
        }
        dest = QUrl(QString::fromUtf8("file://") + dir);
    }
    qDebug() << "Downloading " << url << " to " << dest.toString();
    KIO::CopyJob *copyJob = KIO::copy(QUrl(url), dest, KIO::Overwrite | KIO::DefaultFlags);

    if (copyJob != NULL) {
        KJobUiDelegate *uiDelegate = new KJobUiDelegate();
        copyJob->setUiDelegate(uiDelegate);
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
    Settings &settings = Settings::getInstance();

    if (job->error() == 0) {
        qDebug() << "File copied to" << copyJob->destUrl().path();
        setStatusIcon(SUCCESS);
        trayIcon->showMessage(QString::fromUtf8("Configuration Updataed"),
                              QString::fromUtf8("OpenVPN Configuration successfully downloaded"));
        settings.touchSuccessfulDownload();
        settings.sync();
        updateLastDownload();
    }
    else {
        QString msg = QString::fromUtf8("Error downloading %1: %2")
                          .arg(copyJob->srcUrls().at(0).toString())
                          .arg(job->errorString());
        qDebug() << msg;
        QDateTime lastDownload = settings.lastSuccessfulDownload();
        QDateTime now = QDateTime::currentDateTimeUtc();
        if (lastDownload.addMonths(1) < now)
            setStatusIcon(FAILED);
        else if (lastDownload.addDays(1) < now)
            setStatusIcon(OUTDATED);
        else
            setStatusIcon(SUCCESS);

        trayIcon->showMessage(QString::fromUtf8("Error"), msg, QSystemTrayIcon::MessageIcon::Critical);
   }
}

void addKeyValue(QDBusArgument &arg, const QString &key, const QVariant &value)
{
    arg.beginStructure();
    arg << key << QDBusVariant(value);
    arg.endStructure();
}

void ArachneConfigDownloaderApplication::networkManagerCopyJobDone(
        KIO::Job* job, const QUrl& from, const QUrl &to, const QDateTime&, bool, bool
        )
{
    QFile f(to.path());
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonStr(f.readAll());
    f.close();
    f.remove();

    if (job->error() != 0) {
        qWarning() << QString::fromUtf8("Error downloading from %1: %2")
            .arg(from.toString())
                          .arg(job->errorString());
        return;
    }

    QString conUuid = Settings::getInstance().connectionUuid();
    qDebug() << "Found connetionUuid in settings: " << conUuid;
    try {
        if (conUuid.isEmpty())
            addNetworkManagerConnection(jsonStr);
        else
            updateNetworkManagerConnection(conUuid, jsonStr);
    }
    catch (NMException &ex) {
        qCritical() << QString::fromUtf8("Error processing result URL: %1: %2")
                        .arg(from.toString())
                        .arg(ex.msg());
    }
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
        QString msg = QString::fromUtf8("Cannot parse json at %1: %2\n%3")
                .arg(jsonError.offset)
                .arg(jsonError.error)
                          .arg(QString::fromUtf8(json));
       throw NMException(msg);
    }
    QJsonObject jsonObj = jsonDoc.object();
    QString connectionName = jsonObj.take(QString::fromUtf8("name")).toString();
    if (connectionName.isEmpty())
        throw NMException(QString::fromUtf8("No connection name provided"));
    QJsonValue value = jsonObj.take(QString::fromUtf8("certificates"));
    if (value.isUndefined()) {
        throw NMException(QString::fromUtf8("No connection found in json"));
    }
    QJsonObject connectionObj = value.toObject();
    QString userCert = connectionObj.take(QString::fromUtf8("userCert")).toString();
    if (userCert.isEmpty())
        throw NMException(QString::fromUtf8("No userCert privided in json"));
    QString caCert = connectionObj.take(QString::fromUtf8("caCert")).toString();
    if (caCert.isEmpty())
        throw NMException(QString::fromUtf8("No caCert provided in json"));
    QString privateKey = connectionObj.take(QString::fromUtf8("privateKey")).toString();
    if (privateKey.isEmpty())
        throw NMException(QString::fromUtf8("No privateKey provided in jsoin"));

    QJsonObject dataObj = jsonObj.take(QString::fromUtf8("data")).toObject();
    if (dataObj.isEmpty())
        throw NMException(QString::fromUtf8("No connection data provided in json"));

    QJsonObject ipv4Obj = jsonObj.take(QString::fromUtf8("ipv4")).toObject();
    if (ipv4Obj.isEmpty())
        throw NMException(QString::fromUtf8("No ipv4 provided in json"));

    QString caFileName(settings.certsFolder() + QString::fromUtf8("/arachne-ca.crt"));
    QString certFileName(settings.certsFolder() + QString::fromUtf8("/arachne-cert.crt"));
    QString keyFileName(settings.certsFolder() + QString::fromUtf8("/arachne-cert.key"));

    createFile(caFileName, caCert);
    createFile(certFileName, userCert);
    createFile(keyFileName, privateKey, true);

    ConnectionSettings c;
    QMap<QString, QVariant> conSettings = {
        {QString::fromUtf8("id"), connectionName},
        {QString::fromUtf8("type"), QString::fromUtf8("vpn")},
        {QString::fromUtf8("autoconnect"), false},
        {QString::fromUtf8("permissions"), QVariant(QList<QString>{
            QString::fromUtf8("us<er:") + QString(QString::fromUtf8(getlogin()))
         })
        }
    };
    if (!conUuid.isEmpty())
        conSettings.insert(QString::fromUtf8("uuid"), conUuid);
    c.insert(QString::fromUtf8("connection"), conSettings);

    StringMap data;
    data.insert(QString::fromUtf8("ca"), caFileName);
    data.insert(QString::fromUtf8("cert"), certFileName);
    data.insert(QString::fromUtf8("key"), keyFileName);
    for (const QString &key : dataObj.keys()) {
        QString value = dataObj.value(key).toString();
        qDebug().noquote().nospace() << "Data setting " << key << "=" << value;
        data.insert(key, value);
    }
    c.insert(QString::fromUtf8("vpn"), QMap<QString,QVariant>{
                {QString::fromUtf8("service-type"), QString::fromUtf8("org.freedesktop.NetworkManager.openvpn")},
                {QString::fromUtf8("data"), QVariant::fromValue(data)}
             });

    QMap<QString, QVariant> ipv4;
    bool neverDefault = ipv4Obj.value(QString::fromUtf8("never-default")).toBool();
    ipv4.insert(QString::fromUtf8("never-default"), neverDefault);
    ipv4.insert(QString::fromUtf8("method"), QString::fromUtf8("auto"));
    QStringList dnsSearch;
    for (auto s: ipv4Obj.value(QString::fromUtf8("dns-search")).toArray()) {
        dnsSearch.append(s.toString());
    }
    ipv4.insert(QString::fromUtf8("dns-search"), dnsSearch);
    Uint32List dnsServers;
    for (auto v: ipv4Obj.value(QString::fromUtf8("dns")).toArray()) {
        QHostAddress addr(v.toString());
        quint32 ip = qFromBigEndian(addr.toIPv4Address());
        dnsServers.append(ip);
        qInfo() << "DNS: " << v.toString() << addr.toIPv4Address();
    }
    qInfo() << "DNS servers: " << dnsServers;
    QVariant dnsServersV;
    dnsServersV.setValue(dnsServers);
    ipv4.insert(QString::fromUtf8("dns"), dnsServersV);
    qInfo() << ipv4;

    c.insert(QString::fromUtf8("ipv4"), ipv4);

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
                    QString::fromUtf8("org.freedesktop.NetworkManager"),
                    QString::fromUtf8("/org/freedesktop/NetworkManager/Settings"),
                    QString::fromUtf8("org.freedesktop.NetworkManager.Settings"),
                    QString::fromUtf8("GetConnectionByUuid"), QVariant(conUuid)
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
                            QString::fromUtf8("org.freedesktop.NetworkManager"),
                            conPath,
                            QString::fromUtf8("org.freedesktop.NetworkManager.Settings.Connection"),
                            QString::fromUtf8("Update"), QVariant::fromValue(arg)
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
                    QString::fromUtf8("org.freedesktop.NetworkManager"),
                    QString::fromUtf8("/org/freedesktop/NetworkManager/Settings"),
                    QString::fromUtf8("org.freedesktop.NetworkManager.Settings"),
                    QString::fromUtf8("AddConnection"), QVariant::fromValue(arg)
                    )
                .value().path();

        QString conUuid = dbus_call<ConnectionSettings>(
                    QString::fromUtf8("org.freedesktop.NetworkManager"),
                    conPath,
                    QString::fromUtf8("org.freedesktop.NetworkManager.Settings.Connection"),
                    QString::fromUtf8("GetSettings"), QVariant())
                .value()
                .value(QString::fromUtf8("connection"))
                .value(QString::fromUtf8("uuid"))
                .toString();
        qDebug() << "Added conenction " << conUuid;
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
    if (fileName.startsWith(QString::fromUtf8("~")))
        absFileName.replace(QString::fromUtf8("~"), QDir::homePath());
    QFileInfo fi(absFileName);

    QDir dir;
    if (!dir.mkpath(fi.dir().absolutePath()))
        throw NMException(QString::fromUtf8("Cannot create folder ") + fi.dir().absolutePath());

    qDebug() << "Writing " << fileName;
    QFile f(absFileName);
    if (!f.open(QIODevice::WriteOnly | QFileDevice::Text))
        throw NMException(QString::fromUtf8("Cannot open ") + absFileName);
    QTextStream stream(&f);
    stream << content;
    f.close();

    if (isPrivate)
        f.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
}

void ArachneConfigDownloaderApplication::enableSystemTrayExtension()
{
    qInfo() << "Activating extension";
    // dbus-send --dest=org.gnome.Shell --print-reply --session /org/gnome/Shell org.gnome.Shell.Extensions.EnableExtension string:appindicatorsupport@rgcjonas.gmail.com
    try {
        QDBusConnection con = QDBusConnection::sessionBus();
        QDBusInterface iface(
            QString::fromUtf8("org.gnome.Shell"),
            QString::fromUtf8("/org/gnome/Shell"),
            QString::fromUtf8("org.gnome.Shell.Extensions"),
            con
            );
        QDBusReply<bool> reply =
            iface.call(QString::fromUtf8("EnableExtension"), QString::fromUtf8("appindicatorsupport@rgcjonas.gmail.com"));
        qDebug() << "shell extension avtivated: " << reply.value();
    }
    catch (DBusException ex) {
        qWarning() << ex.msg();
    }
    qDebug() << "finished";
}
