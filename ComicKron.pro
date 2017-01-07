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
!CONFIG(USE_SYSTEM_LMDB): SUBDIRS += lmdb

SUBDIRS += \
    gtest \
    HippoMocks \
    KronAcceptanceTests \
    KronCore \
    KronCoreUnitTests \
    KronContractTests \
    KronDI \
    KronInfrastructure \
    KronMain \
    KronUI

# Subproject paths
gtest.subdir = third_party/gtest
HippoMocks.subdir = third_party/HippoMocks
KronAcceptanceTests.subdir = test/KronAcceptanceTests
KronCore.subdir = src/KronCore
KronCoreUnitTests.subdir = test/KronCoreUnitTests
KronContractTests.subdir = test/KronContractTests
KronDI.subdir = src/KronDI
KronInfrastructure.subdir = src/KronInfrastructure
KronMain.subdir = src/KronMain
KronUI.subdir = src/KronUI
libarchive.subdir = third_party/libarchive
lmdb.subdir = third_party/lmdb
podofo.subdir = third_party/podofo
zlib.subdir = third_party/zlib

include(build/common.pri)

# Generate dependencies automatically (if subproject dependencies are not manually defined)
include(build/autodepends.pri)

# distrib target
contains(QMAKE_HOST.os, Windows):win32: include(build/distrib.pri)
contains(QMAKE_HOST.os, Linux):linux: include(build/distrib.pri)

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
    build/staticlib.pri \
    build/targets.pri \
    build/test.pri \
    build/unit_test.pri \
    cfg/qtquickcontrol2.conf \
    platform/android/AndroidManifest.xml \
    README.md
