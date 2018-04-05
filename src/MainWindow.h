/*
 * File:   MainWindow.h
 * Author: claas
 *
 * Created on 15. September 2016, 17:31
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include <QWidget>

#include "Settings.h"

class QAction;
class QMenu;
class QSystemTrayIcon;
class QTimer;
class KJob;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *downloadAction;
    QAction *settingsAction;
    QAction *gotoWebpageAction;
    QAction *quitAction;

    QTimer *downloadTimer;

    void createActions();
    void createTrayIcon();
    void createTimer();
    void downloadAndExcecute();
    QString formatDirmame(const QString&);

private slots:
    void onSettings();
    void onDownloadNow();
    void onDownloadTimerTimeout();
    void onGotoWebpage();

#ifdef Q_OS_LINUX
    void onJobResult(KJob*);
#endif
};

#endif	/* MAINWINDOW_H */
