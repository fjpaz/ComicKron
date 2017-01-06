#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronAcceptanceTests

ROOTDIR = ../..

include($$ROOTDIR/build/acceptance_test.pri)

QT = core testlib

!msvc {
    QMAKE_CXXFLAGS += -Wno-unknown-warning-option # No warn about unknown warning options
    QMAKE_CXXFLAGS += -Wno-deprecated-declarations # No warn about deprecated declarations
    QMAKE_CXXFLAGS += -Wno-placement-new # No warn about placement new
}

QMAKE_POST_LINK += $$QMAKE_COPY_FILE $$shell_path($$PWD/$$ROOTDIR/test/data/*) $$shell_path($$TESTDIR)

LIBS += \
    -lKronCore \
    -lKronDI \
    -lKronInfrastructure
mac: LIBS += -lc++

HEADERS += \
    test_doubles/SignalSpy.h \
    ../common/TestData.h \
    test_doubles/AcceptanceAppFactory.h \
    test_doubles/IsolatedAppContext.h
    
SOURCES += \ 
    KronAcceptanceTests.cpp \
    PageNavigationTest.cpp \
    test_doubles/SignalSpy.cpp \
    test_doubles/AcceptanceAppFactory.cpp \
    test_doubles/IsolatedAppContext.cpp
