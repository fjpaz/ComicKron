#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TEMPLATE = subdirs

ROOTDIR = ../..

include($$ROOTDIR/build/common.pri)

HEADERS += \
    include/HippoMocks/hippomocks.h

OTHER_FILES += \
    README.md
