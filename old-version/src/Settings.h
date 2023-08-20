/* 
 * File:   Settings.h
 * Author: claas
 *
 * Created on 16. September 2016, 16:03
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include <QSettings>
#include <QString>

class Settings {
public:
    enum TimeUnit {
        SEC,
        MIN,
        HOUR
    };
    
    enum DownloadType {
        NM_DOWNLOAD,
        NM_EXECUTE,
        OVPN_DOWNLOAD
    };
    
    Settings();
    virtual ~Settings();
        
    void setAdminServerUrl(const QString&);
    void setDownloadInterval(int);
    void setDownloadIntervalUnit(TimeUnit);
    void setDownloadDelay(int);
    void setDownloadDelayUnit(TimeUnit);
    void setAutoDownload(bool);
    void setOpenvpnConfigFolder(const QString&);
    void setIgnoreSslErrors(bool);
    void setDownloadType(DownloadType);
    
    QString adminServerUrl();
    int downloadInterval();
    TimeUnit downloadIntervalUnit();
    int downloadDelay();
    TimeUnit downloadDelayUnit();
    bool autoDownload();
    QString openvpnConfigFolder();
    bool ignoreSslErrors();
    DownloadType downloadType();
    
    static Settings &getGlobalSettings();
    
    const QString& downloadFilename();
    QString downloadUrl();
    
    int downloadIntervalMS();
    int downloadDelayMS();
    
private:
    static const QString ADMIN_SERVER_URL;
    static const QString DOWNLOAD_INTERVAL;
    static const QString DOWNLOAD_INTERVAL_UNIT;
    static const QString DOWNLOAD_DELAY;
    static const QString DOWNLOAD_DELAY_UNIT;
    static const QString AUTO_DOWNLOAD;
    static const QString OVPN_CONFIG_FOLDER;
    static const QString IGNORE_SSL_ERRORS;
    static const QString DOWNLOAD_TYPE;

    static Settings globalSettings;
    
    QSettings settings;
    
    int calculateTime(int time, Settings::TimeUnit tu);
};

#endif	/* SETTINGS_H */

