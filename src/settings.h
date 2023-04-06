#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>

class Settings
{
public:
    enum TimeUnit {
        SEC,
        MIN,
        HOUR
    };

    enum DownloadType {
        NETWORK_MANAGER,
        OVPN
    };

    inline static Settings &getInstance() {
        static Settings settings;
        return settings;
    }

    QString adminServerUrl();
    bool ignoreSslErrors();
    bool autoDownload();
    TimeUnit downloadIntervalUnit();
    int downloadInterval();
    TimeUnit downloadDelayUnit();
    int downloadDelay();
    DownloadType downloadType();
    QString downloadDestination();
    int downloadDeleayMsec();
    int downloadIntervalMsec();
#ifdef Q_OS_LINUX
    QString connectionUuid();
    QString certsFolder();
#endif

    void setAdminServerUrl(const QString&);
    void setIgnoreSslErrors(bool);
    void setAutoDownload(bool);
    void setDownloadIntervalUnit(TimeUnit);
    void setDownloadInterval(int);
    void setDownloadDelayUnit(TimeUnit);
    void setDownloadDelay(int);
    void setDownloadType(DownloadType);
    void setDownloadDestination(const QString&);
#ifdef Q_OS_LINUX
    void setConnectionUuid(const QString&);
#endif

    void sync();

private:
    Settings();

    QSettings settings;

    static const QString SN_ADMIN_SERVER_URL;
    static const QString SN_IGNORE_SSL_ERRORS;
    static const QString SN_AUTO_DOWNLOAD;
    static const QString SN_DOWNLOAD_INTERVAL_UNIT;
    static const QString SN_DOWNLOAD_INTERVAL;
    static const QString SN_DOWNLOAD_DELAY_UNIT;
    static const QString SN_DOWNLOAD_DELAY;
    static const QString SN_DOWNLOAD_TYPE;
    static const QString SN_DOWNLOAD_DESTINATION;
#ifdef Q_OS_LINUX
    static const QString SN_CONNECTION_UUID;
#endif

    int buildTime(int timeSpan, TimeUnit unit);
};

#endif // SETTINGS_H
