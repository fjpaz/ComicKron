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

QT = core gui quick qml quickcontrols2

DEFINES += KRONUI_LIBRARY

RESOURCES += resources.qrc

LIBS += -lKronCore

mac: LIBS += -lc++

ios: QTPLUGIN += qmldbg_tcp

SOURCES += \
    services/QmlAppContext.cpp \
    items/ImageShowcase.cpp \
    items/Comic.cpp

HEADERS += \
    KronUIExport.h \
    services/QmlAppContext.h \
    items/ImageShowcase.h \
    items/Comic.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
