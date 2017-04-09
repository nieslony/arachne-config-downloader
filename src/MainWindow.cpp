// https://stackoverflow.com/questions/37968689/implementing-spnego-in-qt

#include "DlgSettings.h"
#include "DlgUserPassword.h"
#include "MainWindow.h"
#include "Settings.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QDir>
#include <QList>
#include <QMenu>
#include <QRegExp>
#include <QStringListIterator>
#include <QTextStream>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QTemporaryFile>
#include <QUrl>
#include <QDir>
#include <QPixmap>
#include <QProcess>

#include <KIO/CopyJob>
#include <KIO/MetaData>
#include <KJobUiDelegate>
#include <KIconLoader>

MainWindow::MainWindow()
{
    downloadTimer = new QTimer(this);
    
    createActions();
    createTrayIcon();

    trayIcon->show();
    createTimer();
}

void MainWindow::createTimer()
{
    connect(downloadTimer, SIGNAL(timeout()), SLOT(onDownloadTimerTimeout()));
    
    if (Settings::getGlobalSettings().autoDownload()) {
        int interval = Settings::getGlobalSettings().downloadIntervalMS();
        int delay = Settings::getGlobalSettings().downloadDelayMS();
        qDebug() << "Starting download in " << delay / 1000 
                << "sec, interval: " << interval / 1000 << "sec";
        downloadTimer->setInterval(interval);        
        downloadTimer->start(delay);
    }    
}

void MainWindow::onDownloadTimerTimeout() {
    downloadAndExcecute();
}

void MainWindow::onSettings()
{
    DlgSettings dlg;
    if (dlg.exec() == QDialog::Accepted) {
        qDebug() << "Updating download timer interval";
        if (Settings::getGlobalSettings().autoDownload()) {
            int interval = Settings::getGlobalSettings().downloadIntervalMS();
            if (downloadTimer->interval() != interval)
                downloadTimer->setInterval(interval);            
            if (downloadTimer->remainingTime() > interval) {
                downloadTimer->start();
            }
            if (!downloadTimer->isActive()) {
                downloadTimer->start();
            }
        }
        else {
            downloadTimer->stop();
        }
    }
}

void MainWindow::onDownloadNow()
{
    downloadAndExcecute();
    if (Settings::getGlobalSettings().autoDownload()) {
        qDebug() << "Restarting download timer";
        downloadTimer->start();
    }
}

void MainWindow::downloadAndExcecute()
{
    QString url = Settings::getGlobalSettings().downloadUrl();
    QUrl dest;
    if (Settings::getGlobalSettings().downloadType() == Settings::NM_EXECUTE) {
        QTemporaryFile tmpFile;
        tmpFile.open();        
        dest = QUrl("file://" + tmpFile.fileName());
        tmpFile.close();
    }
    else {
        QString dir = Settings::getGlobalSettings().openvpnConfigFolder();
        dir.replace("~", QDir::homePath());
        qDebug() << dir;
        dest = QUrl("file://" + dir);
    }
    qDebug() << "Downloading " << url << " to " << dest.toString();
    KIO::CopyJob *copyJob = KIO::copy(QUrl(url), dest, KIO::Overwrite | KIO::DefaultFlags);
    copyJob->setUiDelegateExtension(0); 
    connect(copyJob, SIGNAL(result(KJob*)), SLOT(onJobResult(KJob*)));
}


void MainWindow::onJobResult(KJob* job)
{
    KIO::CopyJob *copyJob = reinterpret_cast<KIO::CopyJob*>(job);

    if (job->error() == 0) {
        qDebug() << "File copied to" << copyJob->destUrl().path();

        if (Settings::getGlobalSettings().downloadType() == Settings::NM_EXECUTE) {
            QFile *destFile = new QFile(copyJob->destUrl().path());
            qDebug() << "Set executable flag of" 
                    << destFile->fileName() 
                    << (destFile->setPermissions(destFile->permissions() | QFileDevice::ExeOwner) ?
                        "successful" : "failed");
            
            
            QProcess *process = new QProcess();
            connect(process, 
                    static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                    [process, destFile](int exitCode, QProcess::ExitStatus exitStatus) {
                        if (exitStatus == QProcess::NormalExit) {
                            qDebug() << "nmcli exited with exit code" << exitCode;
                        }
                        else {
                            qDebug() << "nmcli crashed.";
                        }   
                        
                        delete process;

                        qDebug() << "Adding/modifying NetworkManager configuration";
                        qDebug() << "Removing of" 
                                << destFile->fileName() 
                                << (destFile->remove() ? "successfull" : "failed");
                        delete destFile;
                    });
            process->start(destFile->fileName());            
        }
    }    
    else {
         qDebug() << "Job finished mith error " << job->error() << job->errorString();
    }
}

void MainWindow::onGotoWebpage()
{
    QString url(Settings::getGlobalSettings().adminServerUrl());
   
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::createActions()
{
    downloadAction = new QAction(tr("&Downlaod configuration now"), this);
    connect(downloadAction, SIGNAL(triggered()), SLOT(onDownloadNow()));
    
    settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), SLOT(onSettings()));
    
    gotoWebpageAction = new QAction(tr("Goto OpenVPN_Admin webpage"), this);
    connect(gotoWebpageAction, SIGNAL(triggered()), SLOT(onGotoWebpage()));
    
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}   

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addAction(downloadAction);
    trayIconMenu->addAction(gotoWebpageAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QLatin1String iconName("ovpncdl-green");
    QPixmap icon( KIconLoader::global()->loadIcon(iconName, KIconLoader::Panel ) );
    if (icon.isNull()) {
        qDebug() << "Icon " << iconName << "not found";
    }
    
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("OpenVPN config downloader");
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setObjectName(tr("Configuration downloader for OpenVPN_Admin"));
}

QString MainWindow::formatDirmame(const QString& dirname)
{
    QString ret(dirname);
    
    if (dirname.startsWith("~")) {
        ret.replace(0, 1, QDir::homePath());
    }
    
    return ret;
}
