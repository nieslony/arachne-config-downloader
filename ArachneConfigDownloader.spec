%global debug_package %{nil}

Name:       ArachneConfigDownloader
Version:    0.1.0
Release:    1
License:    GPLv3
Summary:    Arachne Config Downloader
Source:     %{name}-%{version}.tar.gz
Url:        http://www.nieslony.at/arachne
BuildRequires:  qt5-qtbase-devel
BuildRequires:  make
BuildRequires:  kf5-kio-devel

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
    %{_builddir}/%{name}-%{version}/ArachneConfigDownloader \
    %{buildroot}/%{_bindir}/arachnecdl

mkdir -pv %{buildroot}/%{desktop_dir}
touch %{buildroot}/%{desktop_dir}/arachnecdl.desktop
desktop-file-edit --set-name=arachnecdl \
    --set-generic-name="Arachjne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachnecdl \
    --add-only-show-in="KDE" \
    --add-category="KDE" \
    %{buildroot}/%{desktop_dir}/arachnecdl.desktop

mkdir -pv %{buildroot}/%{autostart_dir}
touch %{buildroot}/%{autostart_dir}/arachnecdl.desktop
desktop-file-edit --set-name=arachnecdl \
    --set-generic-name="Arachne Config Downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=arachnecdl \
    --add-only-show-in="KDE" \
    --add-category="KDE" \
    %{buildroot}/%{autostart_dir}/arachnecdl.desktop


%files
%{_bindir}/*
%{autostart_dir}/arachnecdl.desktop
%{desktop_dir}/arachnecdl.desktop
%license LICENSE

%changelog
* Thu Apr 06 2023 Claas Nieslony <claas@nieslony.at> 0.1.0
- Initial version
