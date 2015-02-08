#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = snappy

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

unix: DEFINES += \
    HAVE_SYS_MMAN_H \
    HAVE_BUILTIN_EXPECT \
    HAVE_BUILTIN_CTZ

INCLUDEPATH += .

mac: LIBS += -lc++

SOURCES += \
    snappy.cc \
    snappy-c.cc \
    snappy-sinksource.cc \
    snappy-stubs-internal.cc

HEADERS += \
    snappy.h \
    snappy-c.h \
    snappy-internal.h \
    snappy-sinksource.h \
    snappy-stubs-internal.h \
    snappy-stubs-public.h
    
OTHER_FILES += \
    README.md
