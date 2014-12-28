#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

INTERNAL_INCLUDEPATH += $$PWD/src
EXTERNAL_INCLUDEPATH += \
    $$PWD/3rdparty/gtest/include \
    $$PWD/3rdparty/gmock/include \
    $$PWD/3rdparty/Infectorpp/include

!CONFIG(USE_SYSTEM_ZLIB) {
    EXTERNAL_INCLUDEPATH += $$PWD/3rdparty/zlib
}

!CONFIG(USE_SYSTEM_LIBARCHIVE) {
    EXTERNAL_INCLUDEPATH += $$PWD/3rdparty/libarchive
}

!CONFIG(USE_SYSTEM_PODOFO) {
    EXTERNAL_INCLUDEPATH += $$PWD/3rdparty
}

mac: EXTERNAL_INCLUDEPATH += $$[QT_INSTALL_PREFIX]/lib/QtQuick.framework/Headers
else: EXTERNAL_INCLUDEPATH += \
    $$[QT_INSTALL_PREFIX]/include/QtCore \
    $$[QT_INSTALL_PREFIX]/include/QtGui \
    $$[QT_INSTALL_PREFIX]/include/QtQml \
    $$[QT_INSTALL_PREFIX]/include/QtQuick

INCLUDEPATH += $$INTERNAL_INCLUDEPATH $$EXTERNAL_INCLUDEPATH
DEPENDPATH += $$INTERNAL_INCLUDEPATH

OUTPUTDIR = $$OUT_PWD/$$ROOTDIR/output
BINDIR = $$OUTPUTDIR/bin
LIBDIR = $$OUTPUTDIR/lib
TESTDIR = $$OUTPUTDIR/test
STATICLIBDIR = $$OUTPUTDIR/staticlib

LIBS += -L$$LIBDIR -L$$STATICLIBDIR

msvc {
# TODO: Flags Visual C++
}
else {
    DEBUG_FLAGS = -g -O0
    RELEASE_FLAGS = -O3
    QMAKE_CFLAGS_DEBUG = $$DEBUG_FLAGS
    QMAKE_CFLAGS_RELEASE = $$RELEASE_FLAGS
    QMAKE_CXXFLAGS_DEBUG = $$DEBUG_FLAGS
    QMAKE_CXXFLAGS_RELEASE = $$RELEASE_FLAGS
    QMAKE_CXXFLAGS += -std=c++11

    mac {
        QMAKE_CXXFLAGS += -stdlib=libc++
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
    }

    linux:QMAKE_LFLAGS += -Wl,-rpath-link $$LIBDIR
    linux:QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/../lib' -Wl,-rpath,\'\$$ORIGIN'"
}

winrt: DEFINES += _CRT_SECURE_NO_WARNINGS

CONFIG(release, debug | release) {
    DEFINES += \
        QT_NO_DEBUG_OUTPUT \
        QT_NO_WARNING_OUTPUT
}
