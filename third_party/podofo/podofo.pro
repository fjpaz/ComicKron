#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = podofo

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

DEFINES += BUILDING_PODOFO COMPILING_SHARED_PODOFO

winrt: DEFINES += WINAPI_FAMILY=WINAPI_FAMILY_PC_APP
!winrt: DEFINES += PODOFO_MULTI_THREAD

win32: DEFINES += \
    PODOFO_HAVE_WINSOCK2_H \
    PODOFO_HAVE_BASETSD_H \
    SZ_LONG=4
else: DEFINES += \
    PODOFO_HAVE_ARPA_INET_H \
    PODOFO_HAVE_STRINGS_H \
    SZ_LONG=8

LIBS += -lz
win32: LIBS += -lWs2_32
mac: LIBS += -lc++

SOURCES += \
    base/PdfArray.cpp \
    base/PdfCanvas.cpp \
    base/PdfColor.cpp \
    base/PdfData.cpp \
    base/PdfDataType.cpp \
    base/PdfDate.cpp \
    base/PdfDictionary.cpp \
    base/PdfEncoding.cpp \
    base/PdfEncrypt.cpp \
    base/PdfError.cpp \
    base/PdfFilter.cpp \
    base/PdfFiltersPrivate.cpp \
    base/PdfInputDevice.cpp \
    base/PdfInputStream.cpp \
    base/PdfLocale.cpp \
    base/PdfMemoryManagement.cpp \
    base/PdfMemStream.cpp \
    base/PdfName.cpp \
    base/PdfObject.cpp \
    base/PdfObjectStreamParserObject.cpp \
    base/PdfOutputDevice.cpp \
    base/PdfOutputStream.cpp \
    base/PdfParser.cpp \
    base/PdfParserObject.cpp \
    base/PdfRect.cpp \
    base/PdfRefCountedBuffer.cpp \
    base/PdfRefCountedInputDevice.cpp \
    base/PdfReference.cpp \
    base/PdfStream.cpp \
    base/PdfString.cpp \
    base/PdfTokenizer.cpp \
    base/PdfVariant.cpp \
    base/PdfVecObjects.cpp \
    base/PdfXRef.cpp \
    base/PdfXRefStreamParserObject.cpp \
    doc/PdfAction.cpp \
    doc/PdfContents.cpp \
    doc/PdfDestination.cpp \
    doc/PdfDocument.cpp \
    doc/PdfElement.cpp \
    doc/PdfInfo.cpp \
    doc/PdfMemDocument.cpp \
    doc/PdfNamesTree.cpp \
    doc/PdfOutlines.cpp \
    doc/PdfPage.cpp \
    doc/PdfPagesTree.cpp \
    doc/PdfPagesTreeCache.cpp \
    doc/PdfXObject.cpp

HEADERS += \
    base/Pdf3rdPtyForwardDecl.h \
    base/PdfArray.h \
    base/PdfCanvas.h \
    base/PdfColor.h \
    base/PdfCompilerCompat.h \
    base/PdfCompilerCompatPrivate.h \
    base/PdfData.h \
    base/PdfDataType.h \
    base/PdfDate.h \
    base/PdfDefines.h \
    base/PdfDefinesPrivate.h \
    base/PdfDictionary.h \
    base/PdfEncoding.h \
    base/PdfEncrypt.h \
    base/PdfError.h \
    base/PdfExtension.h \
    base/PdfFilter.h \
    base/PdfFiltersPrivate.h \
    base/PdfInputDevice.h \
    base/PdfInputStream.h \
    base/PdfLocale.h \
    base/PdfMemoryManagement.h \
    base/PdfMemStream.h \
    base/PdfName.h \
    base/PdfObject.h \
    base/PdfObjectStreamParserObject.h \
    base/PdfOutputDevice.h \
    base/PdfOutputStream.h \
    base/PdfParser.h \
    base/PdfParserObject.h \
    base/PdfRect.h \
    base/PdfRefCountedBuffer.h \
    base/PdfRefCountedInputDevice.h \
    base/PdfReference.h \
    base/PdfStream.h \
    base/PdfString.h \
    base/PdfTokenizer.h \
    base/PdfVariant.h \
    base/PdfVecObjects.h \
    base/PdfVersion.h \
    base/PdfXRef.h \
    base/PdfXRefStreamParserObject.h \
    base/podofoapi.h \
    doc/PdfAction.h \
    doc/PdfContents.h \
    doc/PdfDestination.h \
    doc/PdfDocument.h \
    doc/PdfElement.h \
    doc/PdfInfo.h \
    doc/PdfMemDocument.h \
    doc/PdfNamesTree.h \
    doc/PdfOutlines.h \
    doc/PdfPage.h \
    doc/PdfPagesTree.h \
    doc/PdfPagesTreeCache.h \
    doc/PdfXObject.h \
    podofo-base.h \
    podofo.h \
    podofo_config.h \
    base/util/PdfMutex.h \
    base/util/PdfMutexImpl_noop.h \
    base/util/PdfMutexImpl_pthread.h \
    base/util/PdfMutexImpl_win32.h \
    base/util/PdfMutexWrapper.h

OTHER_FILES += \
    README.md
