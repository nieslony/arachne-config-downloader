QT       += core gui dbus network KIOCore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/arachneconfigdownloaderapplication.cpp \
    src/dbus_extra.cpp \
    src/main.cpp \
    src/settings.cpp \
    src/settingsdialog.cpp
unix: SOURCES += \
    src/download-linux.cpp

HEADERS += \
    src/arachneconfigdownloaderapplication.h \
    src/settingsdialog.h \
    src/settings.h
unix: HEADERS += src/dbus_extra.h

TRANSLATIONS += \
    src/ArachneConfigDownloader_de_DE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ArachneConfigDownloader.qrc
