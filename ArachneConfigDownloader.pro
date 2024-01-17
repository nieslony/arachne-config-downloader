QT       += core gui dbus network widgets
unix: QT += KIOCore

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/arachneconfigdownloaderapplication.cpp \
    src/main.cpp \
    src/settings.cpp \
    src/settingsdialog.cpp
unix: SOURCES += \
    src/dbus_extra.cpp \
    src/download-linux.cpp
windows: SOURCES += \
    src/download-windows.cpp

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

DISTFILES += \
    ArachneConfigDownloader.spec \
    arachnecdl.wxs \
    build-msi.sh \
    gen-archive.sh
