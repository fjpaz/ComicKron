#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronContractTests

ROOTDIR = ../..

include($$ROOTDIR/build/contract_test.pri)

QT = core gui quick

LIBS += -lKronInfrastructure
mac: LIBS += -lc++

HEADERS += \
    ../common/TestData.h \
    ComicArchiveReaderContract.h
    
SOURCES += \ 
    KronContractTests.cpp \
    FileComicArchiveReaderTest.cpp
