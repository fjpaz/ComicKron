#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = gmock

ROOTDIR = ../..

include($$ROOTDIR/build/staticlib.pri)

CONFIG -= qt
CONFIG += warn_off

LIBS += -lgtest

SOURCES += \
    src/gmock-all.cc \
    src/gmock-cardinalities.cc \
    src/gmock-internal-utils.cc \
    src/gmock-matchers.cc \
    src/gmock-spec-builders.cc \
    src/gmock.cc
    
HEADERS += \
    include/gmock/internal/gmock-generated-internal-utils.h \
    include/gmock/internal/gmock-internal-utils.h \
    include/gmock/internal/gmock-port.h \
    include/gmock/gmock-actions.h \
    include/gmock/gmock-cardinalities.h \
    include/gmock/gmock-generated-actions.h \
    include/gmock/gmock-generated-function-mockers.h \
    include/gmock/gmock-generated-matchers.h \
    include/gmock/gmock-generated-nice-strict.h \
    include/gmock/gmock-matchers.h \
    include/gmock/gmock-more-actions.h \
    include/gmock/gmock-more-matchers.h \
    include/gmock/gmock-spec-builders.h \
    include/gmock/gmock.h
