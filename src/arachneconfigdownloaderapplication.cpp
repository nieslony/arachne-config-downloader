#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>

#include "arachneconfigdownloaderapplication.h"
#include "settingsdialog.h"

const QString ArachneConfigDownloaderApplication::USER_CONFIG_API_PATH
    = QString("/api/openvpn/user_config");

ArachneConfigDownloaderApplication::ArachneConfigDownloaderApplication(int& argc, char** argv)
    : QApplication(argc, argv)
{
#ifdef Q_OS_LINUX
    enableSystemTrayExtension();
#endif

    setOrganizationName("Claas Nieslony");
    setOrganizationDomain("nieslony.at");
    setApplicationName("Arachne Config Downloader");

    Settings &settings = Settings::getInstance();

    setQuitOnLastWindowClosed(false);

    createTrayIcon();
    if (settings.autoDownload())
        QTimer::singleShot(settings.downloadDeleayMsec(), this, &ArachneConfigDownloaderApplication::onStartup);

    updateLastDownload(settings.lastSuccessfulDownload());
}

void ArachneConfigDownloaderApplication::updateLastDownload(const QDateTime&when)
{
    QLocale locale;
    QString msg("%1\nLast Configuration Update: %2");
    trayIcon->setToolTip(
        msg
            .arg(qApp->applicationDisplayName())
            .arg(
                when.toSecsSinceEpoch() == 0
                    ? "Never"
                    : when.toLocalTime().toString(locale.dateTimeFormat(QLocale::ShortFormat))
                )
        );
}

void ArachneConfigDownloaderApplication::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    setStatusIcon(UNKNOWN);

    QAction *downloadNowAction = new QAction(tr("Download now"), this);
    connect(downloadNowAction, &QAction::triggered, this, &ArachneConfigDownloaderApplication::onDownloadNow);

    QAction *settingsAction = new QAction(tr("Settings..."), this);
    connect(settingsAction, &QAction::triggered, this, &ArachneConfigDownloaderApplication::onSettings);

    QAction *configureArachne = new QAction(tr("Goto Arachne Configuration"), this);
    connect(configureArachne, &QAction::triggered, this, &ArachneConfigDownloaderApplication::onGotoArachneConfiguration);

    QAction *aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, &QAction::triggered, this, &QApplication::aboutQt);

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, this, QApplication::quit);

    QMenu *menu = new QMenu();
    menu->addAction(downloadNowAction);
    menu->addAction(settingsAction);
    menu->addAction(configureArachne);
    menu->addSeparator();
    menu->addAction(aboutQtAction);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);

    trayIcon->show();
}

void ArachneConfigDownloaderApplication::onSettings()
{
    SettingsDialog dlg;
    dlg.exec();
}

void ArachneConfigDownloaderApplication::onStartup()
{
    Settings &settings = Settings::getInstance();

    onDownloadNow();

    connect(&timer, &QTimer::timeout, this, &ArachneConfigDownloaderApplication::onDownloadNow);
    timer.start(settings.downloadIntervalMsec());
}

QTimer &ArachneConfigDownloaderApplication::downloadTimer()
{
    return timer;
}

void ArachneConfigDownloaderApplication::onGotoArachneConfiguration()
{
    Settings &settings = Settings::getInstance();
    QDesktopServices::openUrl (QUrl(settings.adminServerUrl()));
}

void ArachneConfigDownloaderApplication::setStatusIcon(DownloadStatus status)
{
    QString iconName;

    switch (status) {
        case UNKNOWN:
            iconName = ":/resources/images/ovpncdl-blue.svg";
            break;
        case SUCCESS:
            iconName = ":/resources/images/ovpncdl-green.svg";
            break;
        case OUTDATED:
            iconName = ":/resources/images/ovpncdl-yellow.svg";
            break;
        case FAILED:
            iconName = ":/resources/images/ovpncdl-red.svg";
            break;
    }

        trayIcon->setIcon(QIcon(QIcon(iconName).pixmap(128)));
}
