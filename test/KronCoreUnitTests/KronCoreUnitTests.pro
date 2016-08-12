#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronApplicationUnitTests

ROOTDIR = ../..

include($$ROOTDIR/build/unit_test.pri)

QT = core gui quick

LIBS += -lKronApplication
mac: LIBS += -lc++

HEADERS +=  

SOURCES += \ 
    KronApplicationUnitTests.cpp \
    TestComicReaderViewModel.cpp