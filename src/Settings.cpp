/* 
 * File:   Settings.cpp
 * Author: claas
 * 
 * Created on 16. September 2016, 16:03
 */

#include "Settings.h"

#include <QHostInfo>

const QString Settings::ADMIN_SERVER_URL("adminServerUrl");
const QString Settings::AUTO_DOWNLOAD("autoDownload");
const QString Settings::DOWNLOAD_DELAY("downloadDelay");
const QString Settings::DOWNLOAD_DELAY_UNIT("downloadDelayUnit");
const QString Settings::DOWNLOAD_INTERVAL("downloadInterval");
const QString Settings::DOWNLOAD_INTERVAL_UNIT("downloadIntervalUnit");
const QString Settings::OVPN_CONFIG_FOLDER("openvpnConfigFolder");
const QString Settings::IGNORE_SSL_ERRORS("ignoreSslErrors");
const QString Settings::DOWNLOAD_TYPE("downloadType");

Settings Settings::globalSettings;

Settings::Settings() 
    : settings("OpenVPN_Admin_ConfigDownloader")
{
    
}

Settings::~Settings() 
{
}

Settings &Settings::getGlobalSettings()
{
    return globalSettings;
}

QString Settings::adminServerUrl()
{
    QString defaultUrl(QString("https://openvpn.%1/OpenVPN_Admin").arg(QHostInfo::localDomainName()));
    
    return settings.value(ADMIN_SERVER_URL, defaultUrl).toString();
}

bool Settings::autoDownload()
{
    return settings.value(AUTO_DOWNLOAD, true).toBool();
}

int Settings::downloadDelay()
{
    return settings.value(DOWNLOAD_DELAY, 15).toInt();
}

Settings::TimeUnit Settings::downloadDelayUnit()
{
    return static_cast<TimeUnit>(settings.value(DOWNLOAD_DELAY_UNIT, MIN).toInt());
}

int Settings::downloadInterval()
{
    return settings.value(DOWNLOAD_INTERVAL, 60).toInt();
}

Settings::TimeUnit Settings::downloadIntervalUnit()
{
    return static_cast<TimeUnit>(settings.value(DOWNLOAD_INTERVAL_UNIT, MIN).toInt());
}

QString Settings::openvpnConfigFolder()
{
    return settings.value(OVPN_CONFIG_FOLDER, "~/.openvpn").toString();
}

bool Settings::ignoreSslErrors()
{
    return settings.value(IGNORE_SSL_ERRORS, false).toBool();
}

Settings::DownloadType Settings::downloadType()
{
    return static_cast<DownloadType>(settings.value(DOWNLOAD_TYPE, NM_EXECUTE).toInt());
}

void Settings::setAdminServerUrl(const QString& url)
{
    settings.setValue(ADMIN_SERVER_URL, url);
}

void Settings::setAutoDownload(bool ad)
{
    settings.setValue(AUTO_DOWNLOAD, ad);
}

void Settings::setDownloadDelay(int dd)
{
    settings.setValue(DOWNLOAD_DELAY, dd);
}

void Settings::setDownloadDelayUnit(TimeUnit ddu)
{
    settings.setValue(DOWNLOAD_DELAY_UNIT, ddu);
}

void Settings::setDownloadInterval(int di)
{
    settings.setValue(DOWNLOAD_INTERVAL, di);
}

void Settings::setDownloadIntervalUnit(TimeUnit diu)
{
    settings.setValue(DOWNLOAD_INTERVAL_UNIT, diu);
}

void Settings::setOpenvpnConfigFolder(const QString& folder)
{
    settings.setValue(OVPN_CONFIG_FOLDER, folder);
}

void Settings::setIgnoreSslErrors(bool b)
{
    settings.setValue(IGNORE_SSL_ERRORS, b);
}

void Settings::setDownloadType(DownloadType dt)
{
    settings.setValue(DOWNLOAD_TYPE, dt);           
}

const QString& Settings::downloadFilename()
{
    static const QString dlOpenVpn("client-config.ovpn");
    static const QString dlNetworkManager("add-vpn-to-networkmanager.sh");
    static const QString dlUnknown("unkwnon");
    
    switch (downloadType()) {
        case OVPN_DOWNLOAD:
            return dlOpenVpn;
        case NM_EXECUTE:
        case NM_DOWNLOAD:
            return dlNetworkManager;
        default:
            return dlUnknown;
    }
}

QString Settings::downloadUrl()
{
    return QString("%1/download/%2").arg(adminServerUrl()).arg(downloadFilename());
}

int Settings::calculateTime(int time, Settings::TimeUnit tu)
{
    switch (tu) {
        case Settings::SEC:
            return time * 1000;
        case Settings::MIN:
            return time * 1000 * 60;
        case Settings::HOUR:
            return time * 1000 * 60 * 60;
    }
    
    qDebug() << "Why am I here?";
    return -1;
}

int Settings::downloadDelayMS()
{
    return calculateTime(downloadDelay(), downloadDelayUnit());
}

int Settings::downloadIntervalMS()
{
    return calculateTime(downloadInterval(), downloadIntervalUnit());
}
    