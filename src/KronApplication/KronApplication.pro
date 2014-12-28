#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronApplication

ROOTDIR = ../..

include($$ROOTDIR/lib.pri)

QT       = core gui quick

DEFINES += KRONAPPLICATION_LIBRARY
DEFINES += USING_SHARED_PODOFO

SOURCES += \
    ComicViewerViewModel.cpp \
    ComicImageProvider.cpp

HEADERS += \
    ComicViewerViewModel.h\
    ComicImageProvider.h \
    kronapplication_global.h

LIBS += \
    -larchive \
    -lpodofo

mac: LIBS += -lc++

unix {
    target.path = /usr/lib
    INSTALLS += target
}
