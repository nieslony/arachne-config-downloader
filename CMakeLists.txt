cmake_minimum_required(VERSION 3.30)
project(ArachneConfigDownloader VERSION 1.0.0 LANGUAGES CXX)

set(QT_MIN_VERSION "6.5.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(FeatureSummary)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Network
    Widgets
)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    KIO
)

add_executable(arachne-cdl
    src/arachneconfigdownloaderapplication.cpp
    src/main.cpp
    src/settings.cpp
    src/settingsdialog.cpp
    src/dbus_extra.cpp
    src/download-linux.cpp
    src/arachneconfigdownloaderapplication.h
    src/dbus_extra.h
    src/settingsdialog.h
    src/settings.h
)

qt_add_resources(arachne-cdl icons
    PREFIX "/"
    FILES
        resources/images/ovpncdl-green.svg
        resources/images/ovpncdl-red.svg
        resources/images/ovpncdl-yellow.svg
        resources/images/ovpncdl-blue.svg
)


target_compile_options(arachne-cdl PUBLIC -fexceptions)

target_link_libraries(arachne-cdl
    Qt::Core
    Qt::Gui
    Qt::DBus
    Qt::Network
    Qt::Widgets
    KF6::KIOCore
)

install(TARGETS arachne-cdl ${KDE_INSTALL_TARGET_ARGS})
