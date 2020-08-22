Summary:	Implementation of the MSN protocol plug-in for libpurple
Name:		pidgin-msn-pecan
Version:	0.1.4
Release:	2.1
License:	GPLv2+
Group:		Networking/Instant messaging
Source0:	https://github.com/felipec/msn-pecan/archive/v%{version}.zip?/msn-pecan-%{version}.zip
Source1:	msn16.png
Source2:	msn22.png
Source3:        msn48.png
Patch0:		msn-pecan-0.1.4-adapt-to-escagot-server.patch
# Our system library is more recent than the embedded one
Patch1:		msn-pecan-0.1.3-use-system-libmspack.patch
Url:		https://github.com/felipec/msn-pecan
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(libmspack)
BuildRequires:	pkgconfig(purple)

%description
msn-pecan is a "fork" of libpurple's MSN plug-in with a different development
process, clear priorities, and plan forward. It's more fair to call libpurple's
stock msn protocol the fork, and msn-pecan the trunk, as the main development
has moved.
Compared to libpurple's stock plug-in:
 * Faster log-in.
 * Fewer crashes and connection issues.
 * Support for direct file transfers.
 * Support for winks (animoticons) (view-only) (Pidgin).
 * Support for Plus! sounds (receive-only).
 * Option to hide Plus! tags.
Other features (which the stock plug-in also has):
 * No timeout issues.
 * Server-side storage for display names (private alias).
 * Support for personal status messages.
 * Support for offline messaging.
 * Send custom emoticons (Pidgin >= 2.5).
 * Support for handwritten messages (read-only).
 * Support for voice clips (receive-only).

%files
%doc COPYING README TODO
%{_libdir}/purple-2/libmsn-pecan.so
%{_datadir}/pixmaps/pidgin/protocols/*/msn.png

#-----------------------------------------------------------------------------

%prep
%setup -qn msn-pecan-%{version}
%patch0 -p1
rm -rf ext/libmspack
%patch1 -p1 -b .bundled-libmspack


%build
%setup_compile_flags
%make


%install
%makeinstall_std
mkdir -p %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/16
mkdir -p %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/22
mkdir -p %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/48
install %{SOURCE1} %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/16/msn.png
install %{SOURCE2} %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/22/msn.png
install %{SOURCE3} %{buildroot}/%{_datadir}/pixmaps/pidgin/protocols/48/msn.png

