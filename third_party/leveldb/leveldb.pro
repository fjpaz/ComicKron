#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = leveldb

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

CONFIG += warn_off

DEFINES += SNAPPY

posix {
    CONFIG -= qt
    CONFIG += leveldb_posix

    DEFINES += \
        LEVELDB_PLATFORM_POSIX \
        LEVELDB_ATOMIC_PRESENT
} else {
    QT = core
    CONFIG += leveldb_qt
    DEFINES += LEVELDB_PLATFORM_QT
}

win: DEFINES += OS_WIN
mac: DEFINES += OS_MACOSX
linux: DEFINES += OS_LINUX
android: DEFINES += OS_ANDROID
freebsd*: DEFINES += OS_FREEBSD
netbsd*: DEFINES += OS_NETBSD
openbsd*: DEFINES += OS_OPENBSD
hpux*: DEFINES += OS_HPUX

!msvc {
    QMAKE_CXXFLAGS -= -pedantic-errors
    QMAKE_CXXFLAGS -= -Werror
    QMAKE_CXXFLAGS += -fno-builtin-memcmp
    QMAKE_CXXFLAGS += -Wno-variadic-macros
}

INCLUDEPATH += .

LIBS += \
    -lsnappy

mac: LIBS += -lc++

SOURCES += \
    db/builder.cc \
    db/c.cc \
    db/db_impl.cc \
    db/db_iter.cc \
    db/dbformat.cc \
    db/dumpfile.cc \
    db/filename.cc \
    db/log_reader.cc \
    db/log_writer.cc \
    db/memtable.cc \
    db/repair.cc \
    db/table_cache.cc \
    db/version_edit.cc \
    db/version_set.cc \
    db/write_batch.cc \
    table/block.cc \
    table/block_builder.cc \
    table/filter_block.cc \
    table/format.cc \
    table/iterator.cc \
    table/merger.cc \
    table/table.cc \
    table/table_builder.cc \
    table/two_level_iterator.cc \
    util/arena.cc \
    util/bloom.cc \
    util/cache.cc \
    util/coding.cc \
    util/comparator.cc \
    util/crc32c.cc \
    util/env.cc \
    util/filter_policy.cc \
    util/hash.cc \
    util/histogram.cc \
    util/logging.cc \
    util/options.cc \
    util/status.cc

leveldb_posix: SOURCES += \
    port/port_posix.cc \
    util/env_posix.cc

leveldb_qt: SOURCES += \
    util/env_qt.cc

HEADERS += \
    db/builder.h \
    db/db_impl.h \
    db/db_iter.h \
    db/dbformat.h \
    db/filename.h \
    db/log_format.h \
    db/log_reader.h \
    db/log_writer.h \
    db/memtable.h \
    db/skiplist.h \
    db/snapshot.h \
    db/table_cache.h \
    db/version_edit.h \
    db/version_set.h \
    db/write_batch_internal.h \
    include/leveldb/c.h \
    include/leveldb/cache.h \
    include/leveldb/comparator.h \
    include/leveldb/db.h \
    include/leveldb/dumpfile.h \
    include/leveldb/env.h \
    include/leveldb/filter_policy.h \
    include/leveldb/iterator.h \
    include/leveldb/options.h \
    include/leveldb/slice.h \
    include/leveldb/status.h \
    include/leveldb/table.h \
    include/leveldb/table_builder.h \
    include/leveldb/write_batch.h \
    port/win/stdint.h \
    port/port.h \
    port/port_example.h \
    port/thread_annotations.h \
    table/block.h \
    table/block_builder.h \
    table/filter_block.h \
    table/format.h \
    table/iterator_wrapper.h \
    table/merger.h \
    table/two_level_iterator.h \
    util/arena.h \
    util/coding.h \
    util/crc32c.h \
    util/hash.h \
    util/histogram.h \
    util/logging.h \
    util/mutexlock.h \
    util/random.h
    
leveldb_posix: HEADERS += \
    port/atomic_pointer.h \
    port/port_posix.h \
    util/posix_logger.h

leveldb_qt: HEADERS += \
    port/port_qt.h \
    util/qt_logger.h

OTHER_FILES += \
    README.md
