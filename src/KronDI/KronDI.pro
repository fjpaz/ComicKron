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

LIBS += \
    -lKronApplication \
    -lKronInfrastructure \
    -lKronUI

mac: LIBS += -lc++

SOURCES += \
    KronAppFactory.cpp

HEADERS += \
    KronDIExport.h \
    CommonModule.h \
    KronAppFactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
