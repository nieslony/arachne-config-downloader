/*
 * File:   main.cpp
 * Author: claas
 *
 * Created on 15. September 2016, 17:27
 */

#include <QApplication>
#include <QMessageBox>
#include <QSystemTrayIcon>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                               QObject::tr("I couldn't detect any system tray "
                                           "on this system."));
        return 1;
    }

    MainWindow mw;
    //mw.show();    
    
    return app.exec();
}
