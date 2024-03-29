%global debug_package %{nil}

Name:       ArachneConfigDownloader
Version:    1.5
Release:    1
License:    GPLv3
Summary:    Arachne Config Downloader
Source:     %{name}-%{version}.tar.gz
Url:        http://www.nieslony.at/arachne
BuildRequires:  qt5-qtbase-devel
BuildRequires:  qt5-linguist
BuildRequires:  make
BuildRequires:  kf5-kio-devel
Recommends:     gnome-shell-extension-appindicator

%if 0%{?suse_version}
BuildRequires:  libqt5-qtbase-common-devel kio-devel kiconthemes-devel
BuildRequires:  update-desktop-files
%define icons_dir %{_kf5_iconsdir}
%define desktop_dir %{_kf5_applicationsdir}
%define autostart_dir   %{_sysconfdir}/xdg/autostart
%else
BuildRequires:  qt5-qtbase-devel kf5-kio-devel kf5-kiconthemes-devel
BuildRequires:  desktop-file-utils kf5-rpm-macros
%define icons_dir   %{_datadir}/icons
%define desktop_dir %{_datadir}/applications
%define autostart_dir   %{_sysconfdir}/xdg/autostart
%endif

%description
Downloads and installs openvpn configuration from Archne server
as .ovpn file or creates a NetwormManager connection

%prep
%setup

%build
qmake-qt5
make %{?_smp_mflags}

%install
mkdir -vp %{buildroot}/%{_bindir}
install \
    %{_builddir}/%{?buildsubdir}/ArachneConfigDownloader \
    %{buildroot}/%{_bindir}/arachnecdl

mkdir -pv %{buildroot}/%{desktop_dir}
touch %{buildroot}/%{desktop_dir}/arachnecdl.desktop
desktop-file-edit --set-name=arachnecdl \
    --set-generic-name="Arachjne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachnecdl \
    %{buildroot}/%{desktop_dir}/arachnecdl.desktop

mkdir -pv %{buildroot}/%{autostart_dir}
touch %{buildroot}/%{autostart_dir}/arachnecdl.desktop
desktop-file-edit --set-name=arachnecdl \
    --set-generic-name="Arachne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachnecdl \
    %{buildroot}/%{autostart_dir}/arachnecdl.desktop

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
%{autostart_dir}/arachnecdl.desktop
%{desktop_dir}/arachnecdl.desktop
%license LICENSE

%changelog
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
