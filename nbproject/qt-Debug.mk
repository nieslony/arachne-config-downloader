#############################################################################
# Makefile for building: dist/Debug/GNU-Linux/openvpnadmin_configdownloader
# Generated by qmake (3.0) (Qt 5.7.1)
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/bin/qmake-qt5 VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

MAKEFILE      = qttmp-Debug.mk

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_XML_LIB -DQT_DBUS_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -Inbproject -I. -isystem /usr/include/KF5/KIconThemes -isystem /usr/include/KF5/KIOFileWidgets -isystem /usr/include/KF5/KIOWidgets -isystem /usr/include/KF5/KBookmarks -isystem /usr/include/KF5/KXmlGui -isystem /usr/include/KF5/KConfigWidgets -isystem /usr/include/KF5/KWidgetsAddons -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/KF5/KConfigGui -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtNetwork -isystem /usr/include/KF5/KIOCore -isystem /usr/include/KF5/KAuth -isystem /usr/include/KF5/KNTLM -isystem /usr/include/KF5/KCoreAddons -isystem /usr/include/KF5/KService -isystem /usr/include/KF5/KConfigCore -isystem /usr/include/qt5/QtXml -isystem /usr/include/qt5/QtDBus -isystem /usr/include/KF5/KCodecs -isystem /usr/include/KF5/Solid -isystem /usr/include/qt5/QtCore -Ibuild/Debug/GNU-Linux/moc -I/usr/lib64/qt5/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake-qt5
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = openvpnadmin_configdownloader1.0.0
DISTDIR = /home/claas/NetBeansProjects/openvpnadmin_configdownloader/build/Debug/GNU-Linux/openvpnadmin_configdownloader1.0.0
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS) -lKF5IconThemes -lKF5KIOFileWidgets -lKF5KIOWidgets -lKF5Bookmarks -lKF5XmlGui -lKF5ConfigWidgets -lKF5WidgetsAddons -lQt5Widgets -lKF5ConfigGui -lQt5Gui -lQt5Network -lKF5KIOCore -lKF5Auth -lKF5KIONTLM -lKF5CoreAddons -lKF5Service -lKF5ConfigCore -lQt5Xml -lQt5DBus -lKF5Codecs -lKF5Solid -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux/

####### Files

SOURCES       = src/DlgSettings.cpp \
		src/DlgUserPassword.cpp \
		src/MainWindow.cpp \
		src/Settings.cpp \
		src/main.cpp build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp \
		build/Debug/GNU-Linux/moc/moc_MainWindow.cpp
OBJECTS       = build/Debug/GNU-Linux/DlgSettings.o \
		build/Debug/GNU-Linux/DlgUserPassword.o \
		build/Debug/GNU-Linux/MainWindow.o \
		build/Debug/GNU-Linux/Settings.o \
		build/Debug/GNU-Linux/main.o \
		build/Debug/GNU-Linux/moc_DlgSettings.o \
		build/Debug/GNU-Linux/moc_MainWindow.o
DIST          = /usr/lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib64/qt5/mkspecs/qconfig.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KAuth.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KBookmarks.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCodecs.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCompletion.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigCore.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCoreAddons.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIconThemes.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOCore.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOFileWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KItemViews.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KJobWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KNTLM.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KService.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KWidgetsAddons.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KXmlGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_help.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldebug_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_uiplugin.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_Solid.pri \
		/usr/lib64/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt5/mkspecs/features/qt_config.prf \
		/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib64/qt5/mkspecs/features/spec_post.prf \
		nbproject/.qmake.stash \
		/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt5/mkspecs/features/toolchain.prf \
		/usr/lib64/qt5/mkspecs/features/default_pre.prf \
		/usr/lib64/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib64/qt5/mkspecs/features/default_post.prf \
		/usr/lib64/qt5/mkspecs/features/warn_on.prf \
		/usr/lib64/qt5/mkspecs/features/qt.prf \
		/usr/lib64/qt5/mkspecs/features/resources.prf \
		/usr/lib64/qt5/mkspecs/features/moc.prf \
		/usr/lib64/qt5/mkspecs/features/dbuscommon.pri \
		/usr/lib64/qt5/mkspecs/features/dbusinterfaces.prf \
		/usr/lib64/qt5/mkspecs/features/dbusadaptors.prf \
		/usr/lib64/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib64/qt5/mkspecs/features/uic.prf \
		/usr/lib64/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt5/mkspecs/features/file_copies.prf \
		/usr/lib64/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib64/qt5/mkspecs/features/exceptions.prf \
		/usr/lib64/qt5/mkspecs/features/yacc.prf \
		/usr/lib64/qt5/mkspecs/features/lex.prf \
		nbproject/nbproject/qt-Debug.pro src/DlgSettings.h \
		src/DlgUserPassword.h \
		src/MainWindow.h \
		src/Settings.h src/DlgSettings.cpp \
		src/DlgUserPassword.cpp \
		src/MainWindow.cpp \
		src/Settings.cpp \
		src/main.cpp
QMAKE_TARGET  = openvpnadmin_configdownloader
DESTDIR       = dist/Debug/GNU-Linux/
TARGET        = dist/Debug/GNU-Linux/openvpnadmin_configdownloader


first: all
####### Build rules

$(TARGET):  $(OBJECTS)  
	@test -d dist/Debug/GNU-Linux/ || mkdir -p dist/Debug/GNU-Linux/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

qttmp-Debug.mk: nbproject/qt-Debug.pro /usr/lib64/qt5/mkspecs/linux-g++/qmake.conf /usr/lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib64/qt5/mkspecs/qconfig.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KAuth.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KBookmarks.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCodecs.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCompletion.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigCore.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KConfigWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KCoreAddons.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIconThemes.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOCore.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOFileWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KIOWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KItemViews.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KJobWidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KNTLM.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KService.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KWidgetsAddons.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_KXmlGui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_help.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldebug_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_uiplugin.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib64/qt5/mkspecs/modules/qt_Solid.pri \
		/usr/lib64/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt5/mkspecs/features/qt_config.prf \
		/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt5/mkspecs/features/toolchain.prf \
		/usr/lib64/qt5/mkspecs/features/default_pre.prf \
		/usr/lib64/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib64/qt5/mkspecs/features/default_post.prf \
		/usr/lib64/qt5/mkspecs/features/warn_on.prf \
		/usr/lib64/qt5/mkspecs/features/qt.prf \
		/usr/lib64/qt5/mkspecs/features/resources.prf \
		/usr/lib64/qt5/mkspecs/features/moc.prf \
		/usr/lib64/qt5/mkspecs/features/dbuscommon.pri \
		/usr/lib64/qt5/mkspecs/features/dbusinterfaces.prf \
		/usr/lib64/qt5/mkspecs/features/dbusadaptors.prf \
		/usr/lib64/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib64/qt5/mkspecs/features/uic.prf \
		/usr/lib64/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt5/mkspecs/features/file_copies.prf \
		/usr/lib64/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib64/qt5/mkspecs/features/exceptions.prf \
		/usr/lib64/qt5/mkspecs/features/yacc.prf \
		/usr/lib64/qt5/mkspecs/features/lex.prf \
		nbproject/qt-Debug.pro \
		/usr/lib64/libQt5Widgets.prl \
		/usr/lib64/libQt5Gui.prl \
		/usr/lib64/libQt5Network.prl \
		/usr/lib64/libQt5Xml.prl \
		/usr/lib64/libQt5DBus.prl \
		/usr/lib64/libQt5Core.prl
	$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/lib64/qt5/mkspecs/features/spec_pre.prf:
/usr/lib64/qt5/mkspecs/common/unix.conf:
/usr/lib64/qt5/mkspecs/common/linux.conf:
/usr/lib64/qt5/mkspecs/common/sanitize.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib64/qt5/mkspecs/common/g++-base.conf:
/usr/lib64/qt5/mkspecs/common/g++-unix.conf:
/usr/lib64/qt5/mkspecs/qconfig.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KAuth.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KBookmarks.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KCodecs.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KCompletion.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KConfigCore.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KConfigGui.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KConfigWidgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KCoreAddons.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KIconThemes.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KIOCore.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KIOFileWidgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KIOGui.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KIOWidgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KItemViews.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KJobWidgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KNTLM.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KService.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KWidgetsAddons.pri:
/usr/lib64/qt5/mkspecs/modules/qt_KXmlGui.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_clucene_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_designer.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_designer_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_help.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_help_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_packetprotocol_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qml.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qml_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldebug_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_qmltest_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_quick.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_quick_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_uiplugin.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib64/qt5/mkspecs/modules/qt_Solid.pri:
/usr/lib64/qt5/mkspecs/features/qt_functions.prf:
/usr/lib64/qt5/mkspecs/features/qt_config.prf:
/usr/lib64/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib64/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib64/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib64/qt5/mkspecs/features/toolchain.prf:
/usr/lib64/qt5/mkspecs/features/default_pre.prf:
/usr/lib64/qt5/mkspecs/features/resolve_config.prf:
/usr/lib64/qt5/mkspecs/features/default_post.prf:
/usr/lib64/qt5/mkspecs/features/warn_on.prf:
/usr/lib64/qt5/mkspecs/features/qt.prf:
/usr/lib64/qt5/mkspecs/features/resources.prf:
/usr/lib64/qt5/mkspecs/features/moc.prf:
/usr/lib64/qt5/mkspecs/features/dbuscommon.pri:
/usr/lib64/qt5/mkspecs/features/dbusinterfaces.prf:
/usr/lib64/qt5/mkspecs/features/dbusadaptors.prf:
/usr/lib64/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib64/qt5/mkspecs/features/uic.prf:
/usr/lib64/qt5/mkspecs/features/unix/thread.prf:
/usr/lib64/qt5/mkspecs/features/file_copies.prf:
/usr/lib64/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib64/qt5/mkspecs/features/exceptions.prf:
/usr/lib64/qt5/mkspecs/features/yacc.prf:
/usr/lib64/qt5/mkspecs/features/lex.prf:
nbproject/qt-Debug.pro:
/usr/lib64/libQt5Widgets.prl:
/usr/lib64/libQt5Gui.prl:
/usr/lib64/libQt5Network.prl:
/usr/lib64/libQt5Xml.prl:
/usr/lib64/libQt5DBus.prl:
/usr/lib64/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

qmake_all: FORCE


all: qttmp-Debug.mk $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib64/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents src/DlgSettings.h src/DlgUserPassword.h src/MainWindow.h src/Settings.h $(DISTDIR)/
	$(COPY_FILE) --parents src/DlgSettings.cpp src/DlgUserPassword.cpp src/MainWindow.cpp src/Settings.cpp src/main.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) qttmp-Debug.mk


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: build/Debug/GNU-Linux/moc/moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) build/Debug/GNU-Linux/moc/moc_predefs.h
build/Debug/GNU-Linux/moc/moc_predefs.h: /usr/lib64/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -g -Wall -W -dM -E -o build/Debug/GNU-Linux/moc/moc_predefs.h /usr/lib64/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp build/Debug/GNU-Linux/moc/moc_MainWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp build/Debug/GNU-Linux/moc/moc_MainWindow.cpp
build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp: src/DlgSettings.h \
		build/Debug/GNU-Linux/moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include build/Debug/GNU-Linux/moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/claas/NetBeansProjects/openvpnadmin_configdownloader/nbproject -I/usr/include/KF5/KIconThemes -I/usr/include/KF5/KIOFileWidgets -I/usr/include/KF5/KIOWidgets -I/usr/include/KF5/KBookmarks -I/usr/include/KF5/KXmlGui -I/usr/include/KF5/KConfigWidgets -I/usr/include/KF5/KWidgetsAddons -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/KF5/KConfigGui -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtNetwork -I/usr/include/KF5/KIOCore -I/usr/include/KF5/KAuth -I/usr/include/KF5/KNTLM -I/usr/include/KF5/KCoreAddons -I/usr/include/KF5/KService -I/usr/include/KF5/KConfigCore -I/usr/include/qt5/QtXml -I/usr/include/qt5/QtDBus -I/usr/include/KF5/KCodecs -I/usr/include/KF5/Solid -I/usr/include/qt5/QtCore -I. -I/usr/include/c++/6.3.1 -I/usr/include/c++/6.3.1/x86_64-redhat-linux -I/usr/include/c++/6.3.1/backward -I/usr/lib/gcc/x86_64-redhat-linux/6.3.1/include -I/usr/local/include -I/usr/include src/DlgSettings.h -o build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp

build/Debug/GNU-Linux/moc/moc_MainWindow.cpp: src/Settings.h \
		src/MainWindow.h \
		build/Debug/GNU-Linux/moc/moc_predefs.h \
		/usr/lib64/qt5/bin/moc
	/usr/lib64/qt5/bin/moc $(DEFINES) --include build/Debug/GNU-Linux/moc/moc_predefs.h -I/usr/lib64/qt5/mkspecs/linux-g++ -I/home/claas/NetBeansProjects/openvpnadmin_configdownloader/nbproject -I/usr/include/KF5/KIconThemes -I/usr/include/KF5/KIOFileWidgets -I/usr/include/KF5/KIOWidgets -I/usr/include/KF5/KBookmarks -I/usr/include/KF5/KXmlGui -I/usr/include/KF5/KConfigWidgets -I/usr/include/KF5/KWidgetsAddons -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/KF5/KConfigGui -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtNetwork -I/usr/include/KF5/KIOCore -I/usr/include/KF5/KAuth -I/usr/include/KF5/KNTLM -I/usr/include/KF5/KCoreAddons -I/usr/include/KF5/KService -I/usr/include/KF5/KConfigCore -I/usr/include/qt5/QtXml -I/usr/include/qt5/QtDBus -I/usr/include/KF5/KCodecs -I/usr/include/KF5/Solid -I/usr/include/qt5/QtCore -I. -I/usr/include/c++/6.3.1 -I/usr/include/c++/6.3.1/x86_64-redhat-linux -I/usr/include/c++/6.3.1/backward -I/usr/lib/gcc/x86_64-redhat-linux/6.3.1/include -I/usr/local/include -I/usr/include src/MainWindow.h -o build/Debug/GNU-Linux/moc/moc_MainWindow.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

build/Debug/GNU-Linux/DlgSettings.o: src/DlgSettings.cpp src/Settings.h \
		src/DlgSettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/DlgSettings.o src/DlgSettings.cpp

build/Debug/GNU-Linux/DlgUserPassword.o: src/DlgUserPassword.cpp src/DlgUserPassword.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/DlgUserPassword.o src/DlgUserPassword.cpp

build/Debug/GNU-Linux/MainWindow.o: src/MainWindow.cpp src/DlgSettings.h \
		src/DlgUserPassword.h \
		src/MainWindow.h \
		src/Settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/MainWindow.o src/MainWindow.cpp

build/Debug/GNU-Linux/Settings.o: src/Settings.cpp src/Settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/Settings.o src/Settings.cpp

build/Debug/GNU-Linux/main.o: src/main.cpp src/MainWindow.h \
		src/Settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/main.o src/main.cpp

build/Debug/GNU-Linux/moc_DlgSettings.o: build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/moc_DlgSettings.o build/Debug/GNU-Linux/moc/moc_DlgSettings.cpp

build/Debug/GNU-Linux/moc_MainWindow.o: build/Debug/GNU-Linux/moc/moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/moc_MainWindow.o build/Debug/GNU-Linux/moc/moc_MainWindow.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

