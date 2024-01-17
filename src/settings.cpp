#include "settings.h"

#include <QtNetwork/QHostInfo>
#include <QDir>
#include <QTimeZone>

const QString Settings::SN_ADMIN_SERVER_URL("adminServerurl");
const QString Settings::SN_IGNORE_SSL_ERRORS("ignoreSslErrors");
const QString Settings::SN_AUTO_DOWNLOAD("autoDownload");
const QString Settings::SN_DOWNLOAD_INTERVAL_UNIT("downloadIntervalUnit");
const QString Settings::SN_DOWNLOAD_INTERVAL("downloadInterval");
const QString Settings::SN_DOWNLOAD_DELAY_UNIT("downloadDelayUnit");
const QString Settings::SN_DOWNLOAD_DELAY("downloadDelay");
const QString Settings::SN_DOWNLOAD_TYPE("downloadType");
const QString Settings::SN_DOWNLOAD_DESTINATION("downloadDestination");
#ifdef Q_OS_LINUX
const QString Settings::SN_CONNECTION_UUID("connectionUuid");
#endif
const QString Settings::SN_LAST_SUCCESSFUL_DOWNLOAD("lastSuccesfulDownload");

Settings::Settings()
{
    settings.setAtomicSyncRequired(false);
}

QString Settings::adminServerUrl()
{
    static const QString defaultUrl(QString("http://arachne.%1/arachne").arg(QHostInfo::localDomainName()));
    return settings.value(SN_ADMIN_SERVER_URL, defaultUrl).toString();
}

bool Settings::ignoreSslErrors()
{
    return settings.value(SN_IGNORE_SSL_ERRORS, false).toBool();
}

bool Settings::autoDownload()
{
    return settings.value(SN_AUTO_DOWNLOAD, true).toBool();
}

Settings::TimeUnit Settings::downloadIntervalUnit()
{
    return static_cast<TimeUnit>(settings.value(SN_DOWNLOAD_INTERVAL_UNIT, MIN).toInt());
}

int Settings::downloadInterval()
{
    return settings.value(SN_DOWNLOAD_INTERVAL, 60).toInt();
}

Settings::TimeUnit Settings::downloadDelayUnit()
{
    return static_cast<TimeUnit>(settings.value(SN_DOWNLOAD_DELAY_UNIT, MIN).toInt());
}

int Settings::downloadDelay()
{
    return settings.value(SN_DOWNLOAD_DELAY, 5).toInt();
}

Settings::DownloadType Settings::downloadType()
{
    return static_cast<DownloadType>(settings.value(SN_DOWNLOAD_TYPE, NETWORK_MANAGER).toInt());
}

QString Settings::downloadDestination()
{
    static const QString defaultDestination("~/.openvpn");
    return settings.value(SN_DOWNLOAD_DESTINATION, defaultDestination).toString();
}

#ifdef Q_OS_LINUX
QString Settings::certsFolder()
{
    return QDir::homePath() + "/.cert";
}

QString Settings::connectionUuid()
{
    return settings.value(SN_CONNECTION_UUID).toString();
}
#endif

void Settings::setAdminServerUrl(const QString& url)
{
    settings.setValue(SN_ADMIN_SERVER_URL, url);
}

void Settings::setIgnoreSslErrors(bool ignore)
{
    settings.setValue(SN_IGNORE_SSL_ERRORS, ignore);
}

void Settings::setAutoDownload(bool ad)
{
    settings.setValue(SN_AUTO_DOWNLOAD, ad);
}

void Settings::setDownloadIntervalUnit(TimeUnit tu)
{
    settings.setValue(SN_DOWNLOAD_INTERVAL_UNIT, tu);
}

void Settings::setDownloadInterval(int interval)
{
    settings.setValue(SN_DOWNLOAD_INTERVAL, interval);
}

void Settings::setDownloadDelayUnit(TimeUnit tu)
{
    settings.setValue(SN_DOWNLOAD_DELAY_UNIT, tu);
}

void Settings::setDownloadDelay(int delay)
{
    settings.setValue(SN_DOWNLOAD_DELAY, delay);
}

void Settings::setDownloadType(DownloadType dt)
{
    settings.setValue(SN_DOWNLOAD_TYPE, dt);
}

void Settings::setDownloadDestination(const QString &dest)
{
    settings.setValue(SN_DOWNLOAD_DESTINATION, dest);
}

#ifdef Q_OS_LINUX
void Settings::setConnectionUuid(const QString &path)
{
    settings.setValue(SN_CONNECTION_UUID, path);
}
#endif

int Settings::downloadDeleayMsec()
{
    return buildTime(downloadDelay(), downloadDelayUnit());
}

int Settings::downloadIntervalMsec()
{
    return buildTime(downloadInterval(), downloadIntervalUnit());
}

int Settings::buildTime(int timeSpan, TimeUnit unit)
{
    switch (unit) {
        case SEC:
            return timeSpan * 100;
    case MIN:
        return timeSpan * 1000 * 60;
    case HOUR:
        return timeSpan * 1000 * 60 * 60;
    }

    return INT_MAX;
}

void Settings::sync()
{
    qDebug() << "Syncing settings to" << settings.fileName();
    settings.sync();
}

QDateTime Settings::lastSuccessfulDownload()
{
    int secs = settings.value(SN_LAST_SUCCESSFUL_DOWNLOAD, 0).toInt();
    return QDateTime::fromSecsSinceEpoch(secs, QTimeZone::utc());
}

void Settings::touchSuccessfulDownload()
{
    QDateTime now = QDateTime::currentDateTimeUtc();
    settings.setValue(SN_LAST_SUCCESSFUL_DOWNLOAD, now.currentSecsSinceEpoch());
}
