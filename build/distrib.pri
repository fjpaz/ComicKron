#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

# Windows build on Windows
contains(QMAKE_HOST.os, Windows):win32 {
    CONFIG(debug, debug|release):QTLIB_ENDING = d

    DISTRIB_FILES += \
        $$BINDIR \
        $$LIBDIR\
        $$TESTDIR \
        $$[QT_INSTALL_BINS]/Qt5Core$${QTLIB_ENDING}.dll \
        $$[QT_INSTALL_BINS]/Qt5Gui$${QTLIB_ENDING}.dll \
        $$[QT_INSTALL_BINS]/Qt5Qml$${QTLIB_ENDING}.dll \
        $$[QT_INSTALL_BINS]/Qt5Quick$${QTLIB_ENDING}.dll \
        $$[QT_INSTALL_BINS]/Qt5Network$${QTLIB_ENDING}.dll \
        $$[QT_INSTALL_BINS]/libwinpthread-1.dll \
        $$[QT_INSTALL_BINS]/libstdc++-6.dll \
        $$[QT_INSTALL_BINS]/icuin52.dll \
        $$[QT_INSTALL_BINS]/icuuc52.dll \
        $$[QT_INSTALL_BINS]/icudt52.dll

    distrib.commands += del $$shell_path($$OUT_PWD/output/lib/*.a) $$escape_expand(\n\t)
    distrib.commands += if not exist $$shell_path($$OUT_PWD/distrib) mkdir $$shell_path($$OUT_PWD/dist) $$escape_expand(\n\t)

    for(file, DISTRIB_FILES) {
        distrib.commands += xcopy /y $$shell_path($$file $$OUT_PWD/distrib) $$escape_expand(\n\t)
    }
}

# Linux build on Linux
contains(QMAKE_HOST.os, Linux):linux {
    DISTRIB_FILES += \
        $$BINDIR/* \
        $$LIBDIR/* \
        $$TESTDIR/* \
        $$[QT_INSTALL_LIBS]/libQt5Core.so* \
        $$[QT_INSTALL_LIBS]/libQt5Gui.so* \
        $$[QT_INSTALL_LIBS]/libQt5Qml.so* \
        $$[QT_INSTALL_LIBS]/libQt5Quick.so* \
        $$[QT_INSTALL_LIBS]/libQt5Network.so* \
        $$[QT_INSTALL_LIBS]/libicui18n.so* \
        $$[QT_INSTALL_LIBS]/libicuuc.so* \
        $$[QT_INSTALL_LIBS]/libicudata.so*

    distrib.commands += mkdir -p $$OUT_PWD/dist; cp -f $$DISTRIB_FILES $$OUT_PWD/distrib
}

QMAKE_EXTRA_TARGETS += distrib
