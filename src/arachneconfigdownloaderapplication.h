#ifndef ARACHNECONFIGDOWNLOADERAPPLICATION_H
#define ARACHNECONFIGDOWNLOADERAPPLICATION_H

#include <QApplication>
#include <QObject>

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

    static const QString USER_CONFIG_API_PATH;

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    void createTrayIcon();
#ifdef Q_OS_LINUX
    void addNetworkManagerConnection(const QByteArray&json);
    void updateNetworkManagerConnection(const QByteArray&json);
    void buildDBusArgument(QDBusArgument &arg, const QByteArray&json);
    void createFile(const QString &fileName, const QString &content, bool isPrivate=false);
#endif

private slots:
    void onSettings();
    void onDownloadNow();
#ifdef Q_OS_LINUX
    void onDownloadJobResult(KJob*);
    void networkManagerCopyJobDone(KIO::Job*, const QUrl &from, const QUrl &to, const QDateTime&, bool, bool);
#endif

};

#endif // ARACHNECONFIGDOWNLOADERAPPLICATION_H
