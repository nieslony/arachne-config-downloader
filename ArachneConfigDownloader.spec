%global debug_package %{nil}

%define qt_version 6
%define kf_version 6

Name:       ArachneConfigDownloader
Version:    1.5.1
Release:    1
License:    GPL-3.0-or-later
Summary:    Arachne Config Downloader
Source:     %{name}-%{version}.tar.gz
Url:        http://www.nieslony.at/arachne
BuildRequires:  qt%{qt_version}-qtbase-devel
BuildRequires:  qt%{qt_version}-linguist
BuildRequires:  make
Recommends:     gnome-shell-extension-appindicator

BuildRequires:  qt%{qt_version}-qtbase-devel
BuildRequires:  kf%{kf_version}-kio-devel kf%{kf_version}-kiconthemes-devel
BuildRequires:  desktop-file-utils kf%{kf_version}-rpm-macros
%define icons_dir   %{_datadir}/icons
%define desktop_dir %{_datadir}/applications
%define autostart_dir   %{_sysconfdir}/xdg/autostart

%description
Downloads and installs openvpn configuration from Archne server
as .ovpn file or creates a NetwormManager connection

%prep
%autosetup

%build
%cmake_kf6
%cmake_build

%install
%cmake_install --strip

mkdir -pv %{buildroot}/%{desktop_dir}
touch %{buildroot}/%{desktop_dir}/arachne-cdl.desktop
desktop-file-edit --set-name=arachne-cdl \
    --set-generic-name="Arachne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachne-cdl \
    %{buildroot}/%{desktop_dir}/arachne-cdl.desktop

mkdir -pv %{buildroot}/%{autostart_dir}
touch %{buildroot}/%{autostart_dir}/arachne-cdl.desktop
desktop-file-edit --set-name=arachne-cdl \
    --set-generic-name="Arachne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachne-cdl \
    %{buildroot}/%{autostart_dir}/arachne-cdl.desktop

%post
CONF_DIR="/etc/xdg/Claas Nieslony"
CONF_FILE="$CONF_DIR/Arachne Config Downloader.conf"
if [ ! -e "$CONF_FILE" ]; then
    DOMAINNAME=$( domainname )
    mkdir -pv "$CONF_DIR"
    cat <<EOF > "$CONF_FILE"
[General]
adminServerurl=http://arachne.$DOMAINNAME/arachne
autoDownload=true
downloadDelay=5
downloadDelayUnit=1
downloadDestination=~/.openvpn
downloadInterval=60
downloadIntervalUnit=1
downloadType=0
ignoreSslErrors=false
EOF
fi

%files
%{_bindir}/*
%{autostart_dir}/arachne-cdl.desktop
%{desktop_dir}/arachne-cdl.desktop
%license LICENSE

%changelog
* Tue Apr 22 2025 Claas Nieslony <github@nieslony.at> 1.5.1-1
- Many fixes (github@nieslony.at)
- Fix: ArachneConfigDownloaderApplication::isNmConnectionValid
  (github@nieslony.at)
- Load/Save allowd connections (github@nieslony.at)
- Remove debug info (github@nieslony.at)
- Edit allowed connections (github@nieslony.at)
- Ignore build folder (github@nieslony.at)
- Check NM connection name (github@nieslony.at)
- Add function dbus_property (github@nieslony.at)
- Uncomment signal (github@nieslony.at)
- Strip binary (github@nieslony.at)
- Enable exceptions with function (github@nieslony.at)
- Fix: license (github@nieslony.at)
- Fix: qt version and kf version (github@nieslony.at)
- Add install target (github@nieslony.at)
- Fix: remove dependency (github@nieslony.at)
- Add header files (github@nieslony.at)
- Migrate to cmake and KF6 (github@nieslony.at)
- - change slots -> Q_SLOTS - change QString(const char*) -> QString::fromUtf8
  (github@nieslony.at)
- Switch from qmake to cmake (github@nieslony.at)

* Thu Mar 21 2024 Claas Nieslony <github@nieslony.at> 1.5-1
- Show last successful download (github@nieslony.at)

* Wed Jan 17 2024 Claas Nieslony <claas@nieslony.at> 1.4-1
- Fix: show download errors (claas@nieslony.at)

* Fri Jan 12 2024 Claas Nieslony <github@nieslony.at> 0.1.3-1
- 

* Fri Jan 12 2024 Claas Nieslony <github@nieslony.at> 0.1.2-1
- new package built with tito

* Thu Apr 06 2023 Claas Nieslony <claas@nieslony.at> 0.1.0
- Initial version
