#********************************************************************
# Copyright (C) 2017 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = lzma

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

DEFINES += \
    _7ZIP_ST \
    _7ZIP_PPMD_SUPPPORT

SOURCES += \
    7zAlloc.c \
    7zArcIn.c \
    7zBuf.c \
    7zBuf2.c \
    7zCrc.c \
    7zCrcOpt.c \
    7zDec.c \
    7zFile.c \
    7zStream.c \
    Alloc.c \
    Bcj2.c \
    Bra.c \
    Bra86.c \
    BraIA64.c \
    CpuArch.c \
    Delta.c \
    LzFind.c \
    Lzma2Dec.c \
    Lzma2Enc.c \
    Lzma86Dec.c \
    Lzma86Enc.c \
    LzmaDec.c \
    LzmaEnc.c \
    LzmaLib.c \
    Ppmd7.c \
    Ppmd7Dec.c \
    Ppmd7Enc.c \
    Ppmd8.c \
    Ppmd8Dec.c \
    Sha256.c \
    Xz.c \
    XzCrc64.c \
    XzCrc64Opt.c \
    XzDec.c \
    XzEnc.c \
    XzIn.c

HEADERS += \
    7z.h \
    7zAlloc.h \
    7zBuf.h \
    7zCrc.h \
    7zFile.h \
    7zVersion.h \
    Alloc.h \
    Bcj2.h \
    Bra.h \
    CpuArch.h \
    Delta.h \
    LzFind.h \
    LzFindMt.h \
    LzHash.h \
    Lzma2Dec.h \
    Lzma2Enc.h \
    Lzma86.h \
    LzmaDec.h \
    LzmaEnc.h \
    LzmaLib.h \
    Ppmd.h \
    Ppmd7.h \
    Ppmd8.h \
    RotateDefs.h \
    Sha256.h \
    Types.h \
    Xz.h \
    XzCrc64.h \
    XzEnc.h

OTHER_FILES += \
    README.md
