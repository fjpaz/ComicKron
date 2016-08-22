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

#    # distrib target
    DISTRIB_FILES += \
        $$BINDIR \
        $$LIBDIR

    distrib.CONFIG += phony
    distrib.commands += if exist $$shell_path($$OUT_PWD/distrib) rmdir /s /q $$shell_path($$OUT_PWD/distrib) $$escape_expand(\n\t)
    distrib.commands += mkdir $$shell_path($$OUT_PWD/distrib) $$escape_expand(\n\t)

    for(file, DISTRIB_FILES) {
        distrib.commands += xcopy /y $$shell_path($$file $$OUT_PWD/distrib) $$escape_expand(\n\t)
    }

    distrib.commands += $$[QT_INSTALL_BINS]/windeployqt --qml --qmldir $$PWD/.. $$OUT_PWD/distrib

    # distrib_test target
    DISTRIB_TEST_FILES += \
        $$TESTDIR \
        $$[QT_INSTALL_BINS]/Qt5Test$${QTLIB_ENDING}.dll

    distrib_test.CONFIG += phony

    for(file, DISTRIB_TEST_FILES) {
        distrib_test.commands += xcopy /y $$shell_path($$file $$OUT_PWD/distrib) $$escape_expand(\n\t)
    }
}

# Linux build on Linux
contains(QMAKE_HOST.os, Linux):linux {
    # distrib target
    DISTRIB_FILES += \
        $$BINDIR/* \
        $$LIBDIR/* \
        $$[QT_INSTALL_LIBS]/libQt5Core.so* \
        $$[QT_INSTALL_LIBS]/libQt5Gui.so* \
        $$[QT_INSTALL_LIBS]/libQt5Qml.so* \
        $$[QT_INSTALL_LIBS]/libQt5Quick.so* \
        $$[QT_INSTALL_LIBS]/libQt5Network.so* \
        $$[QT_INSTALL_LIBS]/libicui18n.so* \
        $$[QT_INSTALL_LIBS]/libicuuc.so* \
        $$[QT_INSTALL_LIBS]/libicudata.so*

    distrib.CONFIG += phony
    distrib.commands += mkdir -p $$OUT_PWD/distrib; cp -af $$DISTRIB_FILES $$OUT_PWD/distrib

    # distrib_test target
    DISTRIB_TEST_FILES += \
        $$TESTDIR/* \
        $$[QT_INSTALL_LIBS]/libQt5Test.so*

    distrib_test.CONFIG += phony
    distrib_test.commands += cp -af $$DISTRIB_TEST_FILES $$OUT_PWD/distrib
}

QMAKE_EXTRA_TARGETS += distrib distrib_test
