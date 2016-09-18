#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronDI

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

QT = core gui quick

DEFINES += KRONDI_LIBRARY

QMAKE_CXXFLAGS += -Wno-unknown-warning-option # No warn about unknown warning options
QMAKE_CXXFLAGS += -Wno-deprecated-declarations # No warn about deprecated declarations
QMAKE_CXXFLAGS += -Wno-placement-new # No warn about placement new

LIBS += \
    -lKronCore \
    -lKronInfrastructure \
    -lKronUI

mac: LIBS += -lc++

SOURCES += \
    KronAppFactory.cpp \
    CommonAppFactory.cpp

HEADERS += \
    KronDIExport.h \
    KronAppFactory.h \
    CommonAppFactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
