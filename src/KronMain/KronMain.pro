#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = ComicKron

ROOTDIR = ../..

include($$ROOTDIR/build/bin.pri)

QT = core gui qml quick

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

LIBS += -lKronApplication

ANDROID_PACKAGE_SOURCE_DIR = $$_PRO_FILE_PWD_/$$ROOTDIR/platform/android
ANDROID_EXTRA_LIBS += \
    $$LIBDIR/libarchive.so \
    $$LIBDIR/libpodofo.so \
    $$LIBDIR/libKronApplication.so

#WINRT_MANIFEST.target = ComicKron.exe
#WINRT_MANIFEST.publisher = ComicKron

SOURCES += main.cpp

HEADERS +=

OTHER_FILES += \
    $$ROOTDIR/platform/android/AndroidManifest.xml
