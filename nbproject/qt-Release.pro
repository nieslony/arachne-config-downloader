# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux
TARGET = ovpncdl
VERSION = 0.1.3
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network
SOURCES += src/DlgSettings.cpp src/DlgUserPassword.cpp src/MainWindow.cpp src/Settings.cpp src/main.cpp
HEADERS += src/DlgSettings.h src/DlgUserPassword.h src/MainWindow.h src/Settings.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = build/Release/GNU-Linux/moc
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++14
}
QT += KIconThemes KIOCore KIOFileWidgets KIOWidgets KNTLM
