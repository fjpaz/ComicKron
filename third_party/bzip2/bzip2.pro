#********************************************************************
# Copyright (C) 2017 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = bzip2

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

SOURCES += \
    bz_internal_error.c \
    bzlib.c \
    compress.c \
    huffman.c \
    crctable.c \
    decompress.c \
    bzip_all.c \
    blocksort.c \
    randtable.c

HEADERS += \
    bzlib.h \
    bzlib_private.h

OTHER_FILES += \
    README.md
