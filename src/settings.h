#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QDateTime>

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

    QString adminServerUrl() const;
    bool ignoreSslErrors() const;
    bool autoDownload() const;
    TimeUnit downloadIntervalUnit() const;
    int downloadInterval() const;
    TimeUnit downloadDelayUnit() const;
    int downloadDelay() const;
    DownloadType downloadType() const;
    QString downloadDestination() const;
    int downloadDeleayMsec() const;
    int downloadIntervalMsec() const;
#ifdef Q_OS_LINUX
    QString connectionUuid() const;
    QString certsFolder() const;
    bool allowDownloadFromVpn() const;
    bool allowDownloadAllWifi() const;
    bool allowDownloadAllWired() const;
#endif
    QDateTime lastSuccessfulDownload();

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
    void setAllowDownloadFromVpn(bool);
    void setAllowDownloadAllWifi(bool);
    void setAllowDownloadAllWired(bool);
#endif
    void touchSuccessfulDownload();

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
    static const QString SN_ALLOW_DOWNLOAD_FROM_VPN;
    static const QString SN_ALLOW_DOWNLOAD_ALL_WIFI;
    static const QString SN_ALLOW_DOWNLOAD_ALL_WIRED;
#endif
    static const QString SN_LAST_SUCCESSFUL_DOWNLOAD;

    static int buildTime(int timeSpan, TimeUnit unit);
};

#endif // SETTINGS_H
