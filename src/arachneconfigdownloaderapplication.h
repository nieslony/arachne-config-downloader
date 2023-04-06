#ifndef ARACHNECONFIGDOWNLOADERAPPLICATION_H
#define ARACHNECONFIGDOWNLOADERAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <QTimer>

class QSystemTrayIcon;
class QMenu;

#ifdef Q_OS_LINUX
class KJob;
class QDBusArgument;

namespace KIO {
class Job;
}
#endif

class ArachneConfigDownloaderApplication : public QApplication
{
    Q_OBJECT
public:
    ArachneConfigDownloaderApplication(int argc, char** argv);
    QTimer &downloadTimer();

    static const QString USER_CONFIG_API_PATH;

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTimer timer;

    void createTrayIcon();
#ifdef Q_OS_LINUX
    void addNetworkManagerConnection(const QByteArray&json);
    void updateNetworkManagerConnection(
            const QString &conUuid,
            const QByteArray&json);
    void buildDBusArgument(QDBusArgument &arg,
                           const QByteArray&json,
                           const QString &conUuid="");
    void createFile(const QString &fileName, const QString &content, bool isPrivate=false);
#endif

private slots:
    void onSettings();
    void onDownloadNow();
    void onStartup();
#ifdef Q_OS_LINUX
    void onDownloadJobResult(KJob*);
    void networkManagerCopyJobDone(KIO::Job*, const QUrl &from, const QUrl &to, const QDateTime&, bool, bool);
#endif

};

#endif // ARACHNECONFIGDOWNLOADERAPPLICATION_H
