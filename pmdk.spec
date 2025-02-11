# SPDX-License-Identifier: BSD-2-Clause-Patent
# Copyright (c) 2017-2024 Intel Corporation

# do not terminate build if files in the $RPM_BUILD_ROOT
# directory are not found in the %%files (without rpmem case)
#define _unpackaged_files_terminate_build 0

# Ignore an issue with unpackaged libpmem2 files
%define _unpackaged_files_terminate_build 0

%if %{defined suse_version}
    %define dist .suse%{suse_version}
%endif

%global major 2
%global minor 1
%global bugrelease 0
#%%global prerelease rc1
%global buildrelease 3

%global _hardened_build 1

%define min_ndctl_ver 63
%define make_common_args EXTRA_CFLAGS="-Wno-error" NORPATH=1 BUILD_EXAMPLES=n BUILD_BENCHMARKS=n

Name:       pmdk
Version:    %{major}.%{minor}.%{bugrelease}%{?prerelease:~%{prerelease}}
Release:    %{buildrelease}%{?dist}
Summary:    Persistent Memory Development Kit
Group:      System Environment/Libraries
License:    BSD-3-Clause
URL:        https://github.com/pmem/pmdk

# upstream version with ~ removed
%{lua:
    rpm.define("upstream_version " .. string.gsub(rpm.expand("%{version}"), "~", "-"))
}

Source:     https://github.com/pmem/%{name}/releases/download/%{upstream_version}/%{name}-%{upstream_version}.tar.gz
%if "%{?commit}" != ""
Patch0: %{version}..%{commit}.patch
%endif
# Fix https://github.com/pmem/pmdk/issues/6107 : Annoying error message on user intentional transaction abort
Patch1: https://github.com/pmem/pmdk/commit/61e32285370e629e2b36bbb991b919e44f87d915.patch
# Fix https://github.com/pmem/pmdk/issues/6126 : Unnecessary warning: "Cannot find any matching device, no bad blocks found" for non-pmem HW
Patch2: https://github.com/pmem/pmdk/commit/518b7426a13b21f98b2d2c435fa645770899446a.patch

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  glibc-devel
BuildRequires:  man
BuildRequires:  pkgconfig
BuildRequires:  pandoc
BuildRequires:  perl
BuildRequires:  fdupes

%if %{defined suse_version}
BuildRequires:  libndctl-devel >= %{min_ndctl_ver}
%else
BuildRequires:  ndctl-devel >= %{min_ndctl_ver}
BuildRequires:  daxctl-devel >= %{min_ndctl_ver}
%endif

# Debug variants of the libraries should be filtered out of the provides.
%global __provides_exclude_from ^%{_libdir}/pmdk_debug/.*\\.so.*$

# By design, PMDK does not support any 32-bit architecture.
# Due to dependency on xmmintrin.h and some inline assembly, it can be
# compiled only for x86_64 at the moment.
# Other 64-bit architectures could also be supported, if only there is
# a request for that, and if somebody provides the arch-specific
# implementation of the low-level routines for flushing to persistent
# memory.

# https://bugzilla.redhat.com/show_bug.cgi?id=1340634
# https://bugzilla.redhat.com/show_bug.cgi?id=1340635
# https://bugzilla.redhat.com/show_bug.cgi?id=1340636
# https://bugzilla.redhat.com/show_bug.cgi?id=1340637

ExclusiveArch: x86_64 ppc64le

%description
The Persistent Memory Development Kit is a collection of libraries for
using memory-mapped persistence, optimized specifically for persistent memory.


%if 0%{?suse_version} >= 01315
%define libmajor 1
%endif

%package -n libpmem%{?libmajor}
Summary: Low-level persistent memory support library
Group: System Environment/Libraries
%description -n libpmem%{?libmajor}
The libpmem provides low level persistent memory support. In particular,
support for the persistent memory instructions for flushing changes
to pmem is provided.

%files -n libpmem%{?libmajor}
%defattr(-,root,root,-)
%dir %{_datadir}/pmdk
%{_libdir}/libpmem.so.*
%{_datadir}/pmdk/pmdk.magic
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmem-devel
Summary: Development files for the low-level persistent memory library
Group: Development/Libraries
Requires: libpmem%{?libmajor} = %{version}-%{release}
%description -n libpmem-devel
The libpmem provides low level persistent memory support. In particular,
support for the persistent memory instructions for flushing changes
to pmem is provided.

This library is provided for software which tracks every store to
pmem and needs to flush those changes to durability. Most developers
will find higher level libraries like libpmemobj to be much more
convenient.

%files -n libpmem-devel
%defattr(-,root,root,-)
%{_libdir}/libpmem.so
%{_libdir}/pkgconfig/libpmem.pc
%{_includedir}/libpmem.h
%{_mandir}/man7/libpmem.7.gz
%{_mandir}/man5/pmem_ctl.5.gz
%{_mandir}/man3/pmem_*.3.gz
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmem-debug
Summary: Debug variant of the low-level persistent memory library
Group: Development/Libraries
Requires: libpmem%{?libmajor} = %{version}-%{release}
%description -n libpmem-debug
The libpmem provides low level persistent memory support. In particular,
support for the persistent memory instructions for flushing changes
to pmem is provided.

This sub-package contains debug variant of the library, providing
run-time assertions and trace points. The typical way to access the
debug version is to set the environment variable LD_LIBRARY_PATH to
/usr/lib64/pmdk_debug.

%files -n libpmem-debug
%defattr(-,root,root,-)
%dir %{_libdir}/pmdk_debug
%{_libdir}/pmdk_debug/libpmem.so
%{_libdir}/pmdk_debug/libpmem.so.*
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmemobj%{?libmajor}
Summary: Persistent Memory Transactional Object Store library
Group: System Environment/Libraries
Requires: libpmem%{?libmajor} >= %{version}-%{release}
%description -n libpmemobj%{?libmajor}
The libpmemobj library provides a transactional object store,
providing memory allocation, transactions, and general facilities for
persistent memory programming.

%files -n libpmemobj%{?libmajor}
%defattr(-,root,root,-)
%{_libdir}/libpmemobj.so.*
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmemobj-devel
Summary: Development files for the Persistent Memory Transactional Object Store library
Group: Development/Libraries
Requires: libpmemobj%{?libmajor} = %{version}-%{release}
Requires: libpmem-devel = %{version}-%{release}
%description -n libpmemobj-devel
The libpmemobj library provides a transactional object store,
providing memory allocation, transactions, and general facilities for
persistent memory programming. Developers new to persistent memory
probably want to start with this library.

%files -n libpmemobj-devel
%defattr(-,root,root,-)
%{_libdir}/libpmemobj.so
%{_libdir}/pkgconfig/libpmemobj.pc
%{_includedir}/libpmemobj.h
%{_includedir}/libpmemobj/*.h
%{_mandir}/man7/libpmemobj.7.gz
%{_mandir}/man5/poolset.5.gz
%{_mandir}/man3/pmemobj_*.3.gz
%{_mandir}/man3/pobj_*.3.gz
%{_mandir}/man3/oid_*.3.gz
%{_mandir}/man3/toid*.3.gz
%{_mandir}/man3/direct_*.3.gz
%{_mandir}/man3/d_r*.3.gz
%{_mandir}/man3/tx_*.3.gz
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmemobj-debug
Summary: Debug variant of the Persistent Memory Transactional Object Store library
Group: Development/Libraries
Requires: libpmemobj%{?libmajor} = %{version}-%{release}
%description -n libpmemobj-debug
The libpmemobj library provides a transactional object store,
providing memory allocation, transactions, and general facilities for
persistent memory programming. Developers new to persistent memory
probably want to start with this library.

This sub-package contains debug variant of the library, providing
run-time assertions and trace points. The typical way to access the
debug version is to set the environment variable LD_LIBRARY_PATH to
/usr/lib64/pmdk_debug.

%files -n libpmemobj-debug
%defattr(-,root,root,-)
%dir %{_libdir}/pmdk_debug
%{_libdir}/pmdk_debug/libpmemobj.so
%{_libdir}/pmdk_debug/libpmemobj.so.*
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmempool%{?libmajor}
Summary: Persistent Memory pool management library
Group: System Environment/Libraries
Requires: libpmem%{?libmajor} >= %{version}-%{release}
%description -n libpmempool%{?libmajor}
The libpmempool library provides a set of utilities for off-line
administration, analysis, diagnostics and repair of persistent memory
pools created by libpmemobj library.

%files -n libpmempool%{?libmajor}
%defattr(-,root,root,-)
%{_libdir}/libpmempool.so.*
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmempool-devel
Summary: Development files for Persistent Memory pool management library
Group: Development/Libraries
Requires: libpmempool%{?libmajor} = %{version}-%{release}
Requires: libpmem-devel = %{version}-%{release}
%description -n libpmempool-devel
The libpmempool library provides a set of utilities for off-line
administration, analysis, diagnostics and repair of persistent memory
pools created by libpmemobj library.

%files -n libpmempool-devel
%defattr(-,root,root,-)
%{_libdir}/libpmempool.so
%{_libdir}/pkgconfig/libpmempool.pc
%{_includedir}/libpmempool.h
%{_mandir}/man7/libpmempool.7.gz
%{_mandir}/man5/poolset.5.gz
%{_mandir}/man3/pmempool_*.3.gz
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n libpmempool-debug
Summary: Debug variant of the Persistent Memory pool management library
Group: Development/Libraries
Requires: libpmempool%{?libmajor} = %{version}-%{release}
%description -n libpmempool-debug
The libpmempool library provides a set of utilities for off-line
administration, analysis, diagnostics and repair of persistent memory
pools created by libpmemobj library.

This sub-package contains debug variant of the library, providing
run-time assertions and trace points. The typical way to access the
debug version is to set the environment variable LD_LIBRARY_PATH to
/usr/lib64/pmdk_debug.

%files -n libpmempool-debug
%defattr(-,root,root,-)
%dir %{_libdir}/pmdk_debug
%{_libdir}/pmdk_debug/libpmempool.so
%{_libdir}/pmdk_debug/libpmempool.so.*
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md

%package -n pmempool
Summary: Utilities for Persistent Memory
Group: System Environment/Base
Requires: libpmem%{?libmajor} >= %{version}-%{release}
Requires: libpmemobj%{?libmajor} >= %{version}-%{release}
Requires: libpmempool%{?libmajor} >= %{version}-%{release}
Obsoletes: nvml-tools < %{version}-%{release}
%description -n pmempool
The pmempool is a standalone utility for management and off-line analysis
of Persistent Memory pools created by PMDK libraries. It provides a set
of utilities for administration and diagnostics of Persistent Memory pools.
The pmempool may be useful for troubleshooting by system administrators
and users of the applications based on PMDK libraries.

%files -n pmempool
%{_bindir}/pmempool
%{_mandir}/man1/pmempool.1.gz
%{_mandir}/man1/pmempool-*.1.gz
%config(noreplace) %{_sysconfdir}/bash_completion.d/pmempool
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md

%package -n pmreorder
Summary: Consistency Checker for Persistent Memory
Group: System Environment/Base
BuildArch: noarch
%description -n pmreorder
The pmreorder tool is a collection of python scripts designed to parse
and replay operations logged by pmemcheck - a persistent memory checking tool.
Pmreorder performs the store reordering between persistent memory barriers -
a sequence of flush-fence operations. It uses a consistency checking routine
provided in the command line options to check whether files are in a consistent
state.

%files -n pmreorder
%{_bindir}/pmreorder
%{_datadir}/pmreorder/*.py
%{_mandir}/man1/pmreorder.1.gz
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%package -n daxio
Summary: Perform I/O on Device DAX devices or zero a Device DAX device
Group: System Environment/Base
Requires: libpmem%{?libmajor} >= %{version}-%{release}
%description -n daxio
The daxio utility performs I/O on Device DAX devices or zero
a Device DAX device.  Since the standard I/O APIs (read/write) cannot be used
with Device DAX, data transfer is performed on a memory-mapped device.
The daxio may be used to dump Device DAX data to a file, restore data from
a backup copy, move/copy data to another device or to erase data from
a device.

%files -n daxio
%{_bindir}/daxio
%{_mandir}/man1/daxio.1.gz
%license LICENSE
%doc ChangeLog CONTRIBUTING.md README.md


%prep
%autosetup -p1 -n %{name}-%{upstream_version}

%build
%if 0%{?suse_version} > 0
export CFLAGS="%{optflags} -fPIC -pie"
export LDFLAGS="%{?__global_ldflags} -pie"
%else
export CFLAGS="%{optflags}"
export LDFLAGS="%{?__global_ldflags}"
%endif
# For debug build default flags may be overridden to disable compiler
# optimizations.
make %{?_smp_mflags} %{make_common_args}


# Override LIB_AR with empty string to skip installation of static libraries
%install
make install DESTDIR=%{buildroot} %{make_common_args} \
    LIB_AR= \
    prefix=%{_prefix} \
    libdir=%{_libdir} \
    includedir=%{_includedir} \
    mandir=%{_mandir} \
    bindir=%{_bindir} \
    sysconfdir=%{_sysconfdir} \
    docdir=%{_docdir}
mkdir -p %{buildroot}%{_datadir}/pmdk
cp utils/pmdk.magic %{buildroot}%{_datadir}/pmdk/
# PMDK tends to document multiple functions in a single groff file which
# translates into multiple copies of one file.
%fdupes -s %{buildroot}%{_mandir}


%check
echo "PMEM_FS_DIR=/dev/shm" > src/test/testconfig.sh
echo "PMEM_FS_DIR_FORCE_PMEM=1" >> src/test/testconfig.sh
echo 'PMEMOBJ_CONF="sds.at_create=0"' >> src/test/testconfig.sh
echo 'TEST_BUILD="debug nondebug"' >> src/test/testconfig.sh
echo 'TEST_FS="pmem any none"' >> src/test/testconfig.sh
make %{make_common_args} check

%if 0%{?suse_version} >= 01315
%post   -n libpmem%{?libmajor} -p /sbin/ldconfig
%postun -n libpmem%{?libmajor} -p /sbin/ldconfig
%post   -n libpmemobj%{?libmajor} -p /sbin/ldconfig
%postun -n libpmemobj%{?libmajor} -p /sbin/ldconfig
%post   -n libpmempool%{?libmajor} -p /sbin/ldconfig
%postun -n libpmempool%{?libmajor} -p /sbin/ldconfig

%else
%if (0%{?rhel} < 8)
# EL8 triggers ldconfig from glibc
%ldconfig_scriptlets   -n libpmem
%ldconfig_scriptlets   -n libpmemobj
%ldconfig_scriptlets   -n libpmempool
%endif
%endif

%if 0%{?__debug_package} == 0
%debug_package
%endif


%changelog
* Wed Nov 06 2024  Tomasz Gromadzki <tomasz.gromadzki@intel.com> - 2.1.0-3
- Apply patches to silence annoying error messages on:
  - an intentional transaction abort and
  - PMDK being used with non-PMem HW.

* Wed Sep 04 2024  Tomasz.Gromadzki <tomasz.gromadzki@intel.com> - 2.1.0-2
- Enable NDCTL on the top of PMDK 2.1.0
  - remove an option to build PMDK w/o NDCTL.

* Tue Aug 06 2024  Tomasz Gromadzki <tomasz.gromadzki@intel.com> - 2.1.0-1
- Update to release 2.1.0 w/o NDCTL support which:
  - Introduces the new logging subsystem in the release build for all libraries.
  - Messages by default are printed to syslog and stderr but might be redirected to a user-defined function, see pmem(obj)_log_set_function() for details.
  - Log level thresholds are controlled via new API, see pmem(obj)_log_set_treshold() for details.
  - These new APIs are not available for LIBPMEMPOOL at the moment.
  - The new logging subsystem is suppressed in the debug build when any of the legacy debug logging environment variables is set:
    - PMEM_LOG_LEVEL/_FILE
    - PMEMOBJ_LOG_LEVEL/_FILE
    - PMEMPOOL_LOG_LEVEL/_FILE
    - The debug logging subsystem becomes DEPRECATED.
  - Drops support for building without libpthread (NO_LIBPTHREAD build-time define).
  - Introduces fuses against ill-considered use of NDCTL_ENABLE=n.
    - PMEMOBJ_IGNORE_DIRTY_SHUTDOWN and PMEMOBJ_IGNORE_BAD_BLOCKS are required to acknowledge the understanding of what production-critical functions are missing for the build without NDCTL.
  - Does not allow create PMEMOBJ pool without unsafe shutdown counter (USC) if not explicitly disabled when NDCTL is in use.
    - use PMEMOBJ_CONF="sds.at_create=0" to disable USC when working without PMem (emulated PMem, Docker, etc.).

- Includes also release 2.0.1 which:
    - Reduces libpmemobj's stack usage below the 11kB threshold.

* Fri Sep 22 2023 Jan Michalski <jan.michalski@intel.com> - 2.0.0-1
- Update to release 2.0.0 which
    - removes libpmemlog and libpmemblk,
    - removes all pmem2_async operations (and the miniasync dependency).
- Remove BUILD_RPMEM which was removed in release 1.13 (no change to
  the resulting packaging).
- Remove deprecated build requirements (autoconf, automake and gdb).
- Add perl to requirements (previously provided by autoconf).
- Stop building and testing examples and benchmarks.

* Tue Sep 12 2023 Jan Michalski <jan.michalski@intel.com> - 1.12.1-2
- Make pmreorder a noarch - fixing a rpmlint issue
- Use /dev/shm instead of /tmp for testing - workaround docker flock(2) issue
- Deduplicate manpages

* Thu Aug 25 2022 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.12.1-1
- Update to release 1.12.1

* Tue Aug 16 2022 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.12.1~rc1-1
- Update to release 1.12.1~rc1
- Fixes DAOS-11151

* Tue Jul 26 2022 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.12.0-1
- Update to release 1.12.0
- Remove rpmem packages

* Fri Oct 08 2021 Alexander Oganezov <alexander.a.oganezov@intel.com> - 1.11.0-3
- Update to DAOS_8273 patch

* Tue Jul 06 2021 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.11.0-2
- Update to official release 1.11.0

* Fri Jun 11 2021 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.11.0-1
- Update to 1.11.0-rc1
- Single threaded PMDK allocator mode

* Tue Jan 19 2021 Brian J. Murrell <brian.murrell@intel.com> - 1.9.2-1
- Update to 1.9.2
- use autosetup

* Tue Jun 16 2020 Brian J. Murrell <brian.murrell@intel.com> - 1.8-2
- Update License: for SUSE builds

* Tue Feb 18 2020 Brian J. Murrell <brian.murrell@intel.com> - 1.8-1
- Build --without=ndctl

* Mon Feb 03 2020 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.8-0.3
- Update to 1.8 stable release

* Wed Jan 29 2020 Jeff Olivier <jeffrey.v.olivier@intel.com> - 1.8-0.2
- Fix some errors in rpmlint

* Thu Jan 23 2020 Brian J. Murrell <brian.murrell@intel.com> - 1.8-0.1
- Update to PMDK version 1.8-rc1

* Mon Oct 21 2019 Brian J. Murrell <brian.murrell@intel.com> - 1.6-1
- Update to PMDK version 1.6

* Tue May 14 2019 Brian J. Murrell <brian.murrell@intel.com> - 1.5.1-4
- Fix SLES 12.3 OS conditionals >= 1315

* Sat May 04 2019 Brian J. Murrell <brian.murrell@intel.com> - 1.5.1-3
- Fix Source URL
- Add a requires for ndctl-libs

* Wed Apr 17 2019 Brian J. Murrell <brian.murrell@intel.com> - 1.5.1-2
- Add a Reqires: for ndctl-libs

* Wed Apr 03 2019 Brian J. Murrell <brian.murrell@intel.com> - 1.5.1-1
- Pass down --without ndctl to the make commands
- Add a --without rpmem switch
- Remove the unpackaged files check skip and remove files
  that shouldn't be packaged
- put %%{_mandir}/man5/pmem_ctl.5.gz into libpmem-devel

* Fri Mar 08 2019 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.5.1-1
- Update to PMDK version 1.5.1

* Fri Feb 01 2019 Fedora Release Engineering <releng@fedoraproject.org> - 1.5-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_30_Mass_Rebuild

* Fri Dec 14 2018 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.5-2
- Remove Group: tag and add ownership information for libpmemobj headers
  directory.

* Tue Nov 6 2018 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.5-1
- Update to PMDK version 1.5
  libpmemobj C++ bindings moved to separate package (RHBZ #1647145)
  pmempool convert is now a thin wrapper around pmdk-convert (RHBZ #1647147)

* Fri Aug 17 2018 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.4.2-1
- Update to PMDK version 1.4.2 (RHBZ #1589406)

* Tue Aug 14 2018 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.4.2-0.2.rc1
- Revert package name change

* Tue Aug 14 2018 Marcin Ślusarz <marcin.slusarz@intel.com> - 1.4.2-0.1.rc1
- Update to PMDK version 1.4.2-rc1 (RHBZ #1589406)

* Fri Jul 13 2018 Fedora Release Engineering <releng@fedoraproject.org> - 1.4-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_29_Mass_Rebuild

* Fri Mar 30 2018 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.4-3
- Revert package name change
- Re-enable check

* Thu Mar 29 2018 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.4-2
- Fix issues found by rpmlint

* Thu Mar 29 2018 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.4-1
- Rename NVML project to PMDK
- Update to PMDK version 1.4 (RHBZ #1480578, #1539562, #1539564)

* Thu Feb 08 2018 Fedora Release Engineering <releng@fedoraproject.org> - 1.3.1-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_28_Mass_Rebuild

* Sat Jan 27 2018 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.3.1-1
- Update to NVML version 1.3.1 (RHBZ #1480578)

* Thu Aug 03 2017 Fedora Release Engineering <releng@fedoraproject.org> - 1.3-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_27_Binutils_Mass_Rebuild

* Thu Jul 27 2017 Fedora Release Engineering <releng@fedoraproject.org> - 1.3-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_27_Mass_Rebuild

* Mon Jul 17 2017 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.3-1
- Update to NVML version 1.3 (RHBZ #1451741, RHBZ #1455216)
- Add librpmem and rpmemd sub-packages
- Force file system to appear as PMEM for make check

* Fri Jun 16 2017 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.2.3-2
- Update to NVML version 1.2.3 (RHBZ #1451741)

* Sat Apr 15 2017 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.2.2-1
- Update to NVML version 1.2.2 (RHBZ #1436820, RHBZ #1425038)

* Thu Mar 16 2017 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.2.1-1
- Update to NVML version 1.2.1 (RHBZ #1425038)

* Tue Feb 21 2017 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.2-3
- Fix compilation under gcc 7.0.x (RHBZ #1424004)

* Sat Feb 11 2017 Fedora Release Engineering <releng@fedoraproject.org> - 1.2-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_26_Mass_Rebuild

* Fri Dec 30 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.2-1
- Update to NVML version 1.2 (RHBZ #1383467)
- Add libpmemobj C++ bindings

* Thu Jul 14 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.1-3
- Add missing package version requirements

* Mon Jul 11 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.1-2
- Move debug variants of the libraries to -debug subpackages

* Sun Jun 26 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.1-1
- NVML 1.1 release
- Update link to source tarball
- Add libpmempool subpackage
- Remove obsolete patches

* Wed Jun 01 2016 Dan Horák <dan[at]danny.cz> - 1.0-3
- switch to ExclusiveArch

* Sun May 29 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.0-2
- Exclude PPC architecture
- Add bug numbers for excluded architectures

* Tue May 24 2016 Krzysztof Czurylo <krzysztof.czurylo@intel.com> - 1.0-1
- Initial RPM release
