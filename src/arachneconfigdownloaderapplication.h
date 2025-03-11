#ifndef ARACHNECONFIGDOWNLOADERAPPLICATION_H
#define ARACHNECONFIGDOWNLOADERAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDateTime>

class QSystemTrayIcon;
class QMenu;

#ifdef Q_OS_LINUX
class KJob;
class QDBusArgument;
class Settings;

namespace KIO {
class Job;
}
#endif

class ArachneConfigDownloaderApplication : public QApplication
{
    Q_OBJECT
public:
    ArachneConfigDownloaderApplication(int &argc, char** argv);
    QTimer &downloadTimer();

    static const QString USER_CONFIG_API_PATH;

private:
    enum DownloadStatus {
        UNKNOWN,
        SUCCESS,
        OUTDATED,
        FAILED
    };

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTimer timer;

    void createTrayIcon();
    void setStatusIcon(DownloadStatus);
    void updateLastDownload(const QDateTime&when = QDateTime::currentDateTimeUtc());
#ifdef Q_OS_LINUX
    bool isNmConnectionValid(const Settings&);
    void addNetworkManagerConnection(const QByteArray&json);
    void updateNetworkManagerConnection(
            const QString &conUuid,
            const QByteArray&json);
    void buildDBusArgument(QDBusArgument &arg,
                           const QByteArray&json,
                           const QString &conUuid=QString());
    void createFile(const QString &fileName, const QString &content, bool isPrivate=false);
    void enableSystemTrayExtension();
#endif

private Q_SLOTS:
    void onSettings();
    void onDownloadNow();
    void onStartup();
    void onGotoArachneConfiguration();
#ifdef Q_OS_LINUX
    void onDownloadJobResult(KJob*);
    void networkManagerCopyJobDone(KIO::Job*, const QUrl &from, const QUrl &to, const QDateTime&, bool, bool);
#endif

};

#endif // ARACHNECONFIGDOWNLOADERAPPLICATION_H
