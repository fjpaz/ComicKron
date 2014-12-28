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
    KronMain \

OTHER_FILES += \
    autodepends.pri \
    bin.pri \
    common.pri \
    deployment.pri \
    distrib.pri \
    lib.pri \
    staticlib.pri \
    test.pri

# Subprojects path
gmock.subdir = 3rdparty/gmock
gtest.subdir = 3rdparty/gtest
Infectorpp.subdir = 3rdparty/Infectorpp
KronApplication.subdir = src/KronApplication
KronApplicationUnitTests.subdir = test/KronApplicationUnitTests
KronMain.subdir = src/KronMain
libarchive.subdir = 3rdparty/libarchive
podofo.subdir = 3rdparty/podofo
zlib.subdir = 3rdparty/zlib

# Generate dependencies automatically (if subproject dependencies are not manually set)
include(autodepends.pri)

contains(QMAKE_HOST.os, Windows):win32: include(distrib.pri)
contains(QMAKE_HOST.os, Linux):linux: include(distrib.pri)
