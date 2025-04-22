cmake_minimum_required(VERSION 3.30)
project(ArachneConfigDownloader VERSION 1.0.0 LANGUAGES CXX)

find_package(ECM ${KF_MIN_VERSION} REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Network
    Widgets
)

find_package(KF5 REQUIRED COMPONENTS
    KIO
)

set(SOURCES
    src/arachneconfigdownloaderapplication.cpp
    src/main.cpp
    src/settings.cpp
    src/settingsdialog.cpp
    src/dbus_extra.cpp
    src/download-linux.cpp
    src/nmconnection.cpp
    src/arachneconfigdownloaderapplication.h
    src/dbus_extra.h
    src/settingsdialog.h
    src/settings.h
    src/nmconnection.h
)

qt_add_resources(
    SOURCES arachne.qrc
)

add_executable(arachne-cdl
    ${SOURCES}
)

kde_enable_exceptions()

target_link_libraries(arachne-cdl
    Qt::Core
    Qt::Gui
    Qt::DBus
    Qt::Network
    Qt::Widgets
    KF5::KIOCore
)

install(TARGETS arachne-cdl ${KDE_INSTALL_TARGET_ARGS})
