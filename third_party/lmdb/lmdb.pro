#********************************************************************
# Copyright (C) 2017 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = lmdb

ROOTDIR = ../..

include($$ROOTDIR/build/staticlib.pri)

CONFIG -= qt
CONFIG += warn_off

DEFINES += 

!msvc {
    QMAKE_CXXFLAGS += \
        -Wno-unused-parameter \
        -Wbad-function-cast \
        -Wuninitialized
}

mac: LIBS += -lc++

SOURCES += \
    midl.c \
    mdb.c

HEADERS += \
    midl.h \
    lmdb.h
    
OTHER_FILES += \
    README.md
