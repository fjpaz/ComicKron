#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronCore

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

QT = core

DEFINES += KRONCORE_LIBRARY

mac: LIBS += -lc++

SOURCES += \
    viewmodels/ComicReaderVM.cpp \
    App.cpp \
    exceptions/ArchiveNotFoundException.cpp \
    exceptions/ArchiveFormatNotSupportedException.cpp \
    exceptions/ArchiveReadErrorException.cpp \
    viewmodels/FileBrowserVM.cpp

HEADERS += \
    services/ComicArchiveReader.h \
    exceptions/ArchiveNotFoundException.h \
    AppFactory.h \
    viewmodels/ComicReaderVM.h \
    App.h \
    services/AppContext.h \
    exceptions/ArchiveReadErrorException.h \
    exceptions/ArchiveFormatNotSupportedException.h \
    KronCoreExport.h \
    services/Device.h \
    viewmodels/FileBrowserVM.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
