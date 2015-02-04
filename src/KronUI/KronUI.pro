#********************************************************************
# Copyright (C) 2015 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = KronUI

ROOTDIR = ../..

include($$ROOTDIR/build/lib.pri)

QT = core gui quick qml

DEFINES += KRONUI_LIBRARY

RESOURCES += resources.qrc

LIBS += -lKronApplication

mac: LIBS += -lc++

SOURCES += \
    services/QmlViewModelRegistrar.cpp \
    services/QmlAppContext.cpp \
    services/PixmapImageProvider.cpp

HEADERS += \
    KronUIExport.h \
    services/QmlViewModelRegistrar.h \
    services/QmlAppContext.h \
    services/PixmapImageProvider.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
