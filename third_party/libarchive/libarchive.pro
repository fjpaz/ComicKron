#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = archive

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG -= qt
CONFIG += warn_off

DEFINES += HAVE_CONFIG_H

winrt: DEFINES += WINAPI_FAMILY=WINAPI_FAMILY_PC_APP

linux-* {
DEFINES += \
    HAVE_STATVFS \
    HAVE_SYS_STATVFS_H \
    HAVE_ICONV \
    HAVE_ICONV_H \
    HAVE_FUTIMENS
}

android-* {
DEFINES += HAVE_SYS_UTIME_H
}

macx: DEFINES += HAVE_LOCALCHARSET_H

LIBS += -lz
msvc: LIBS += -lAdvapi32 -lUser32
mac: LIBS += -liconv -lbz2

SOURCES += \
    archive_acl.c \
    archive_check_magic.c \
    archive_entry.c \
    archive_entry_copy_stat.c \
    archive_entry_link_resolver.c \
    archive_entry_sparse.c \
    archive_entry_stat.c \
    archive_entry_strmode.c \
    archive_entry_xattr.c \
    archive_getdate.c \
    archive_match.c \
    archive_options.c \
    archive_pathmatch.c \
    archive_ppmd7.c \
    archive_rb.c \
    archive_read.c \
    archive_read_append_filter.c \
    archive_read_open_memory.c \
    archive_read_set_format.c \
    archive_read_set_options.c \
    archive_read_support_filter_all.c \
    archive_read_support_filter_gzip.c \
    archive_read_support_filter_none.c \
    archive_read_support_format_7zip.c \
    archive_read_support_format_all.c \
    archive_read_support_format_by_code.c \
    archive_read_support_format_empty.c \
    archive_read_support_format_lha.c \
    archive_read_support_format_rar.c \
    archive_read_support_format_raw.c \
    archive_read_support_format_tar.c \
    archive_read_support_format_zip.c \
    archive_string.c \
    archive_string_sprintf.c \
    archive_util.c \
    archive_virtual.c

win32: SOURCES += \
    archive_windows.c

HEADERS += \
    archive.h \
    archive_acl_private.h \
    archive_crc32.h \
    archive_endian.h \
    archive_entry.h \
    archive_entry_locale.h \
    archive_entry_private.h \
    archive_options_private.h \
    archive_pathmatch.h \
    archive_platform.h \
    archive_ppmd7_private.h \
    archive_ppmd_private.h \
    archive_private.h \
    archive_rb.h \
    archive_read_private.h \
    archive_string.h \
    archive_string_composition.h \
    archive_windows.h \
    config_freebsd.h \
    config.h \
    config_mingw.h \
    config_msvc.h \
    config_unix.h \
    config_darwin.h

OTHER_FILES += \
    README.md
