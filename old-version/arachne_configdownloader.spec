Name:       arachne-config-downloader-qt
Version:    0.1.4
Release:    1
Summary:    Web application for administering openVPN
Obsoletes:  arachne_ConfigDownloader

License:    GPL-2.0+
URL:        http://www.nieslony.site/OpenVPN_Admin
Source0:    %{name}-%{version}.tar.gz
BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if 0%{?suse_version}
BuildRequires:  libqt5-qtbase-common-devel kio-devel kiconthemes-devel
BuildRequires:  update-desktop-files
%define icons_dir %{_kf5_iconsdir}
%define desktop_dir %{_kf5_applicationsdir}
%define autostart_dir   %{_sysconfdir}/xdg/autostart
%else
BuildRequires:  qt5-qtbase-devel kf5-kio-devel kf5-kiconthemes-devel 
BuildRequires:  desktop-file-utils kf5-rpm-macros  pinentry-qt 
%define icons_dir   %{_datadir}/icons
%define desktop_dir %{_datadir}/applications
%define autostart_dir   %{_sysconfdir}/xdg/autostart
%endif

%description
Downloads configuration file from OpenVPN_Admin server

%prep
%setup -q

%build
qmake-qt5 -after \
    MOC_DIR=%{_builddir}/%{name}-%{version}/moc \
    OBJECTS_DIR=%{_builddir}/%{name}-%{version}/obj \
    DESTDIR=%{_builddir}/%{name}-%{version}/bin \
    QMAKE_CXXFLAGS+=-std=c++11 \
    nbproject/qt-Release.pro

make    
    
%files
%{_bindir}/ovpncdl
%{icons_dir}/hicolor/*/apps/ovpncdl-green.png
%{desktop_dir}/ovpncdl.desktop
/%{autostart_dir}/ovpncdl.desktop

%doc doc/COPYING 

%install
mkdir -vp %{buildroot}/%{_bindir}
mkdir -vp %{buildroot}/%{icons_dir}/hicolor/{16x16,22x22,32x32,48x48,64x64}/apps
install %{_builddir}/%{name}-%{version}/bin/ovpncdl %{buildroot}/%{_bindir}
install %{_builddir}/%{name}-%{version}/icons/ovpncdl-green-16x16.png %{buildroot}/%{icons_dir}/hicolor/16x16/apps/ovpncdl-green.png
install %{_builddir}/%{name}-%{version}/icons/ovpncdl-green-22x22.png %{buildroot}/%{icons_dir}/hicolor/22x22/apps/ovpncdl-green.png
install %{_builddir}/%{name}-%{version}/icons/ovpncdl-green-32x32.png %{buildroot}/%{icons_dir}/hicolor/32x32/apps/ovpncdl-green.png
install %{_builddir}/%{name}-%{version}/icons/ovpncdl-green-48x48.png %{buildroot}/%{icons_dir}/hicolor/48x48/apps/ovpncdl-green.png
install %{_builddir}/%{name}-%{version}/icons/ovpncdl-green-64x64.png %{buildroot}/%{icons_dir}/hicolor/64x64/apps/ovpncdl-green.png


mkdir -pv %{buildroot}/%{desktop_dir}
touch %{buildroot}/%{desktop_dir}/ovpncdl.desktop
desktop-file-edit --set-name=ovpncdl \
    --set-generic-name="OpenVPN config downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=ovpncdl \
    --add-only-show-in="KDE" \
    --add-category="KDE" \
    %{buildroot}/%{desktop_dir}/ovpncdl.desktop

mkdir -pv %{buildroot}/%{autostart_dir}
touch %{buildroot}/%{autostart_dir}/ovpncdl.desktop
desktop-file-edit --set-name=ovpncdl \
    --set-generic-name="OpenVPN config downloader" \
    --set-icon=ovpncdl-green \
    --set-key=Type --set-value=Application \
    --set-key=Exec --set-value=ovpncdl \
    --add-only-show-in="KDE" \
    --add-category="KDE" \
    %{buildroot}/%{autostart_dir}/ovpncdl.desktop

%changelog
* Sun Nov 06 2016 Claas Nieslony <claas@nieslony.at> 0.1.0
- Initial version
