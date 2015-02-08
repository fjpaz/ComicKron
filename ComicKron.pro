#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TEMPLATE = subdirs

ROOTDIR = .

android|ios: CONFIG += USE_SYSTEM_ZLIB

# Subprojects
!CONFIG(USE_SYSTEM_ZLIB): SUBDIRS += zlib
!CONFIG(USE_SYSTEM_LIBARCHIVE): SUBDIRS += libarchive
!CONFIG(USE_SYSTEM_PODOFO): SUBDIRS += podofo
!CONFIG(USE_SYSTEM_LEVELDB): SUBDIRS += leveldb
!CONFIG(USE_SYSTEM_SNAPPY): SUBDIRS += snappy

SUBDIRS += \
    boost \
    gtest \
    HippoMocks \
    KronAcceptanceTests \
    KronApplication \
    KronApplicationUnitTests \
    KronContractTests \
    KronDI \
    KronDomainUnitTests \
    KronInfrastructure \
    KronMain \
    KronUI

# Subproject paths
boost.subdir = third_party/boost
gtest.subdir = third_party/gtest
HippoMocks.subdir = third_party/HippoMocks
KronAcceptanceTests.subdir = test/KronAcceptanceTests
KronApplication.subdir = src/KronApplication
KronApplicationUnitTests.subdir = test/KronApplicationUnitTests
KronContractTests.subdir = test/KronContractTests
KronDI.subdir = src/KronDI
KronDomainUnitTests.subdir = test/KronDomainUnitTests
KronInfrastructure.subdir = src/KronInfrastructure
KronMain.subdir = src/KronMain
KronUI.subdir = src/KronUI
leveldb.subdir = third_party/leveldb
libarchive.subdir = third_party/libarchive
podofo.subdir = third_party/podofo
snappy.subdir = third_party/snappy
zlib.subdir = third_party/zlib

include(build/common.pri)

# Generate dependencies automatically (if subproject dependencies are not manually defined)
include(build/autodepends.pri)

# distrib target
contains(QMAKE_HOST.os, Windows):win32: include(build/distrib.pri)
contains(QMAKE_HOST.os, Linux):linux: include(build/distrib.pri)

# output target
include(build/output.pri)

# Other editable files
OTHER_FILES += \
    build/acceptance_test.pri \
    build/autodepends.pri \
    build/bin.pri \
    build/contract_test.pri \
    build/common.pri \
    build/deployment.pri \
    build/distrib.pri \
    build/lib.pri \
    build/output.pri \
    build/staticlib.pri \
    build/targets.pri \
    build/test.pri \
    build/unit_test.pri \
    README.md
