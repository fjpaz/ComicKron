#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronInfrastructure

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

QT = core gui quick
android: QT += androidextras

DEFINES += KRONINFRASTRUCTURE_LIBRARY
DEFINES += USING_SHARED_PODOFO

# No warn about deprecated declarations
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
!msvc: QMAKE_CXXFLAGS -= -pedantic-errors

# Include folders needed to use private class QHighDpiScaling
INCLUDEPATH += \
    $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION] \
    $$[QT_INSTALL_HEADERS]/QtGui/$$[QT_VERSION]

LIBS += \
    -lKronCore \
    -larchive \
    -lpodofo

mac: LIBS += -lc++

SOURCES += \
    services/FileComicArchiveReader.cpp \
    services/PdfComicArchiveReader.cpp \
    services/CompressedComicArchiveReader.cpp \
    services/RealDevice.cpp

HEADERS += \
    services/FileComicArchiveReader.h \
    services/PdfComicArchiveReader.h \
    services/CompressedComicArchiveReader.h \
    KronInfrastructureExport.h \
    services/RealDevice.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
