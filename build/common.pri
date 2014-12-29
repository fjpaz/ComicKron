#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Include path
INTERNAL_INCLUDEPATH += $$ROOTDIR/src
EXTERNAL_INCLUDEPATH += \
    $$ROOTDIR/third_party/gtest/include \
    $$ROOTDIR/third_party/gmock/include \
    $$ROOTDIR/third_party/Infectorpp/include

!CONFIG(USE_SYSTEM_ZLIB) {
    EXTERNAL_INCLUDEPATH += $$ROOTDIR/third_party/zlib
}

!CONFIG(USE_SYSTEM_LIBARCHIVE) {
    EXTERNAL_INCLUDEPATH += $$ROOTDIR/third_party/libarchive
}

!CONFIG(USE_SYSTEM_PODOFO) {
    EXTERNAL_INCLUDEPATH += $$ROOTDIR/third_party
}

mac: EXTERNAL_INCLUDEPATH += $$[QT_INSTALL_PREFIX]/lib/QtQuick.framework/Headers
else: EXTERNAL_INCLUDEPATH += \
    $$[QT_INSTALL_PREFIX]/include/QtCore \
    $$[QT_INSTALL_PREFIX]/include/QtGui \
    $$[QT_INSTALL_PREFIX]/include/QtQml \
    $$[QT_INSTALL_PREFIX]/include/QtQuick

INCLUDEPATH += $$INTERNAL_INCLUDEPATH $$EXTERNAL_INCLUDEPATH
DEPENDPATH += $$INTERNAL_INCLUDEPATH

# Available destination directories
OUTPUTDIR = $$OUT_PWD/$$ROOTDIR/output
BINDIR = $$OUTPUTDIR/bin
LIBDIR = $$OUTPUTDIR/lib
TESTDIR = $$OUTPUTDIR/test
STATICLIBDIR = $$OUTPUTDIR/staticlib

# Link directories
LIBS += -L$$LIBDIR -L$$STATICLIBDIR

# Compiler flags
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

# Common defines
winrt: DEFINES += _CRT_SECURE_NO_WARNINGS

# Disable debug output on release builds
CONFIG(release, debug | release) {
    DEFINES += \
        QT_NO_DEBUG_OUTPUT \
        QT_NO_WARNING_OUTPUT
}

# Custom targets. Targets for specific subprojects have command defined in specific .pri file
unit_test.CONFIG = recursive
unit_test.depends = all

QMAKE_EXTRA_TARGETS += \
    unit_test
