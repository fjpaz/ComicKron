#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = gtest

ROOTDIR = ../..

include($$ROOTDIR/build/staticlib.pri)

CONFIG -= qt
CONFIG += warn_off

SOURCES += \
    src/gtest-all.cc \
    src/gtest-death-test.cc \
    src/gtest-filepath.cc \
    src/gtest-port.cc \
    src/gtest-printers.cc \
    src/gtest-test-part.cc \
    src/gtest-typed-test.cc \
    src/gtest.cc
    
HEADERS += \
    include/gtest/internal/gtest-death-test-internal.h \
    include/gtest/internal/gtest-filepath.h \
    include/gtest/internal/gtest-internal.h \
    include/gtest/internal/gtest-linked_ptr.h \
    include/gtest/internal/gtest-param-util-generated.h \
    include/gtest/internal/gtest-param-util.h \
    include/gtest/internal/gtest-port.h \
    include/gtest/internal/gtest-string.h \
    include/gtest/internal/gtest-tuple.h \
    include/gtest/internal/gtest-type-util.h \
    include/gtest/gtest-death-test.h \
    include/gtest/gtest-message.h \
    include/gtest/gtest-param-test.h \
    include/gtest/gtest-printers.h \
    include/gtest/gtest-spi.h \
    include/gtest/gtest-test-part.h \
    include/gtest/gtest-typed-test.h \
    include/gtest/gtest.h \
    include/gtest/gtest_pred_impl.h \
    include/gtest/gtest_prod.h \
    src/gtest-internal-inl.h
    
