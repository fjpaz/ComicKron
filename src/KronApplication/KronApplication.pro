#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronApplication

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

QT = core

DEFINES += KRONAPPLICATION_LIBRARY

mac: LIBS += -lc++

SOURCES += \
    viewmodels/ComicReaderVM.cpp \
    App.cpp \
    services/AppPageNavigator.cpp \
    exceptions/ArchiveNotFoundException.cpp \
    exceptions/ArchiveFormatNotSupportedException.cpp \
    exceptions/ArchiveReadErrorException.cpp

HEADERS += \
    KronApplicationExport.h \
    services/ComicArchiveReader.h \
    services/ImageContainer.h \
    exceptions/ArchiveNotFoundException.h \
    AppFactory.h \
    viewmodels/ComicReaderVM.h \
    App.h \
    services/AppPageNavigator.h \
    PageId.h \
    services/ViewModelRegistrar.h \
    services/AppContext.h \
    exceptions/ArchiveReadErrorException.h \
    exceptions/ArchiveFormatNotSupportedException.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
