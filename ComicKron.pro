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
!CONFIG(USE_SYSTEM_ZLIB) {
    SUBDIRS += zlib
}

!CONFIG(USE_SYSTEM_LIBARCHIVE) {
    SUBDIRS += libarchive
}

!CONFIG(USE_SYSTEM_PODOFO) {
    SUBDIRS += podofo
}

SUBDIRS += \
    gmock \
    gtest \
    Infectorpp \
    KronApplication \
    KronApplicationUnitTests \
    KronMain

# Other editable files
OTHER_FILES += \
    build/autodepends.pri \
    build/bin.pri \
    build/common.pri \
    build/deployment.pri \
    build/distrib.pri \
    build/lib.pri \
    build/staticlib.pri \
    build/test.pri

# Subproject paths
gmock.subdir = third_party/gmock
gtest.subdir = third_party/gtest
Infectorpp.subdir = third_party/Infectorpp
KronApplication.subdir = src/KronApplication
KronApplicationUnitTests.subdir = test/KronApplicationUnitTests
KronMain.subdir = src/KronMain
libarchive.subdir = third_party/libarchive
podofo.subdir = third_party/podofo
zlib.subdir = third_party/zlib

# Generate dependencies automatically (if subproject dependencies are not manually defined)
include(build/autodepends.pri)

# Distrib target
contains(QMAKE_HOST.os, Windows):win32: include(build/distrib.pri)
contains(QMAKE_HOST.os, Linux):linux: include(build/distrib.pri)
