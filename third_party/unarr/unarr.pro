#********************************************************************
# Copyright (C) 2017 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = unarr

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

DEFINES += \
    _FILE_OFFSET_BITS=64 \
    HAVE_ZLIB \
    HAVE_BZIP2 \
    HAVE_7Z \
    USE_7Z_CRC32

QMAKE_CFLAGS_RELEASE += -fomit-frame-pointer

CONFIG(release, debug | release) {
    DEFINES += NDEBUG
}

LIBS += \
    -lz \
    -lbzip2 \
    -llzma

SOURCES += \
    zip/zip.c \
    zip/inflate.c \
    zip/uncompress-zip.c \
    zip/parse-zip.c \
    _7z/_7z.c \
    tar/parse-tar.c \
    tar/tar.c \
    common/stream.c \
    common/custalloc.c \
    common/crc32.c \
    common/unarr.c \
    common/conv.c \
    rar/rarvm.c \
    rar/huffman-rar.c \
    rar/uncompress-rar.c \
    rar/parse-rar.c \
    rar/filter-rar.c \
    rar/rar.c

HEADERS += \
    zip/zip.h \
    zip/inflate.h \
    _7z/_7z.h \
    unarr.h \
    tar/tar.h \
    lzmasdk/Ppmd.h \
    lzmasdk/CpuArch.h \
    lzmasdk/7zTypes.h \
    lzmasdk/Ppmd7.h \
    lzmasdk/Precomp.h \
    lzmasdk/Ppmd8.h \
    lzmasdk/LzmaDec.h \
    common/allocator.h \
    common/unarr-imp.h \
    rar/lzss.h \
    rar/rarvm.h \
    rar/rar.h

OTHER_FILES += \
    README.md
