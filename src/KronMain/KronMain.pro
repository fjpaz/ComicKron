#********************************************************************
# Copyright (C) 2014 Francisco Javier Paz Menendez
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#********************************************************************

TARGET = ComicKron

ROOTDIR = ../..

include($$ROOTDIR/build/bin.pri)

QT = core gui qml quick quickcontrols2

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

LIBS += \
    -lKronCore \
    -lKronDI \
    -lKronInfrastructure \
    -lKronUI

ANDROID_PACKAGE_SOURCE_DIR = $$_PRO_FILE_PWD_/$$ROOTDIR/platform/android
ANDROID_EXTRA_LIBS += \
    $$LIBDIR/libarchive.so \
    $$LIBDIR/libleveldb.so \
    $$LIBDIR/libpodofo.so \
    $$LIBDIR/libsnappy.so \
    $$LIBDIR/libKronCore.so \
    $$LIBDIR/libKronDI.so \
    $$LIBDIR/libKronInfrastructure.so \
    $$LIBDIR/libKronUI.so
ANDROID_DEPLOYMENT_DEPENDENCIES += \
    jar/QtAndroid-bundled.jar \
    lib/libQt5Core.so \
    lib/libQt5Gui.so \
    lib/libQt5Network.so \
    lib/libQt5Qml.so \
    lib/libQt5Quick.so \
    lib/libQt5QuickTemplates2.so \
    lib/libQt5QuickParticles.so \
    lib/libQt5QuickControls2.so \
    lib/libQt5AndroidExtras.so \
    plugins/bearer/libqandroidbearer.so \
    plugins/qmltooling/libqmldbg_debugger.so \
    plugins/qmltooling/libqmldbg_inspector.so \
    plugins/qmltooling/libqmldbg_local.so \
    plugins/qmltooling/libqmldbg_native.so \
    plugins/qmltooling/libqmldbg_profiler.so \
    plugins/qmltooling/libqmldbg_quickprofiler.so \
    plugins/qmltooling/libqmldbg_server.so \
    plugins/qmltooling/libqmldbg_tcp.so \
    plugins/platforms/android/libqtforandroid.so \
    plugins/platforms/libqeglfs.so \
    plugins/platforms/libqminimal.so \
    plugins/platforms/libqminimalegl.so \
    plugins/platforms/libqoffscreen.so \
    plugins/generic/libqevdevkeyboardplugin.so \
    plugins/generic/libqevdevmouseplugin.so \
    plugins/generic/libqevdevtabletplugin.so \
    plugins/generic/libqevdevtouchplugin.so \
    plugins/generic/libqtuiotouchplugin.so \
    plugins/iconengines/libqsvgicon.so \
    plugins/imageformats/libqdds.so \
    plugins/imageformats/libqgif.so \
    plugins/imageformats/libqicns.so \
    plugins/imageformats/libqico.so \
    plugins/imageformats/libqjpeg.so \
    plugins/imageformats/libqsvg.so \
    plugins/imageformats/libqtga.so \
    plugins/imageformats/libqtiff.so \
    plugins/imageformats/libqwbmp.so \
    plugins/imageformats/libqwebp.so \
    plugins/scenegraph/libsoftwarecontext.so \
    qml/QtQuick.2/qmldir \
    qml/QtQuick.2/libqtquick2plugin.so \
    qml/QtQuick.2/plugins.qmltypes \
    qml/QtQuick/Dialogs/libdialogplugin.so \
    qml/QtQuick/Dialogs/plugins.qmltypes \
    qml/QtQuick/Dialogs/Private/libdialogsprivateplugin.so \
    qml/QtQuick/Dialogs/Private/plugins.qmltypes \
    qml/QtQuick/Dialogs/Private/qmldir \
    qml/QtQuick/Dialogs/qmldir \
    qml/Qt/labs/folderlistmodel/libqmlfolderlistmodelplugin.so \
    qml/Qt/labs/folderlistmodel/plugins.qmltypes \
    qml/Qt/labs/folderlistmodel/qmldir \
    qml/QtQuick/Templates.2/libqtquicktemplates2plugin.so \
    qml/QtQuick/Templates.2/plugins.qmltypes \
    qml/QtQuick/Templates.2/qmldir \
    qml/QtQuick/Controls.2/qmldir \
    qml/QtQuick/Controls.2/libqtquickcontrols2plugin.so \
    qml/QtQuick/Controls.2/Material/qmldir \
    qml/QtQuick/Controls.2/Material/plugins.qmltypes \
    qml/QtQuick/Controls.2/Material/libqtquickcontrols2materialstyleplugin.so \
    qml/QtQuick/Controls.2/Menu.qml \
    qml/QtQuick/Controls.2/Slider.qml \
    qml/QtQuick/Controls.2/ToolButton.qml \
    qml/QtQuick/Controls.2/TextArea.qml \
    qml/QtQuick/Controls.2/Page.qml \
    qml/QtQuick/Controls.2/ScrollIndicator.qml \
    qml/QtQuick/Controls.2/Frame.qml \
    qml/QtQuick/Controls.2/Drawer.qml \
    qml/QtQuick/Controls.2/TabButton.qml \
    qml/QtQuick/Controls.2/Button.qml \
    qml/QtQuick/Controls.2/StackView.qml \
    qml/QtQuick/Controls.2/Switch.qml \
    qml/QtQuick/Controls.2/Label.qml \
    qml/QtQuick/Controls.2/RangeSlider.qml \
    qml/QtQuick/Controls.2/Dial.qml \
    qml/QtQuick/Controls.2/ProgressBar.qml \
    qml/QtQuick/Controls.2/CheckIndicator.qml \
    qml/QtQuick/Controls.2/Popup.qml \
    qml/QtQuick/Controls.2/ToolBar.qml \
    qml/QtQuick/Controls.2/SwitchDelegate.qml \
    qml/QtQuick/Controls.2/RadioIndicator.qml \
    qml/QtQuick/Controls.2/MenuItem.qml \
    qml/QtQuick/Controls.2/RadioButton.qml \
    qml/QtQuick/Controls.2/Tumbler.qml \
    qml/QtQuick/Controls.2/CheckBox.qml \
    qml/QtQuick/Controls.2/ApplicationWindow.qml \
    qml/QtQuick/Controls.2/ItemDelegate.qml \
    qml/QtQuick/Controls.2/TabBar.qml \
    qml/QtQuick/Controls.2/ComboBox.qml \
    qml/QtQuick/Controls.2/RadioDelegate.qml \
    qml/QtQuick/Controls.2/SpinBox.qml \
    qml/QtQuick/Controls.2/GroupBox.qml \
    qml/QtQuick/Controls.2/SwipeDelegate.qml \
    qml/QtQuick/Controls.2/CheckDelegate.qml \
    qml/QtQuick/Controls.2/SwipeView.qml \
    qml/QtQuick/Controls.2/BusyIndicator.qml \
    qml/QtQuick/Controls.2/TextField.qml \
    qml/QtQuick/Controls.2/Pane.qml \
    qml/QtQuick/Controls.2/ToolTip.qml \
    qml/QtQuick/Controls.2/ScrollBar.qml \
    qml/QtQuick/Controls.2/Material/Menu.qml \
    qml/QtQuick/Controls.2/Material/Slider.qml \
    qml/QtQuick/Controls.2/Material/ToolButton.qml \
    qml/QtQuick/Controls.2/Material/TextArea.qml \
    qml/QtQuick/Controls.2/Material/Page.qml \
    qml/QtQuick/Controls.2/Material/ScrollIndicator.qml \
    qml/QtQuick/Controls.2/Material/Frame.qml \
    qml/QtQuick/Controls.2/Material/Drawer.qml \
    qml/QtQuick/Controls.2/Material/Ripple.qml \
    qml/QtQuick/Controls.2/Material/ElevationEffect.qml \
    qml/QtQuick/Controls.2/Material/TabButton.qml \
    qml/QtQuick/Controls.2/Material/Button.qml \
    qml/QtQuick/Controls.2/Material/SliderHandle.qml \
    qml/QtQuick/Controls.2/Material/StackView.qml \
    qml/QtQuick/Controls.2/Material/Switch.qml \
    qml/QtQuick/Controls.2/Material/Label.qml \
    qml/QtQuick/Controls.2/Material/RangeSlider.qml \
    qml/QtQuick/Controls.2/Material/Dial.qml \
    qml/QtQuick/Controls.2/Material/ProgressBar.qml \
    qml/QtQuick/Controls.2/Material/CheckIndicator.qml \
    qml/QtQuick/Controls.2/Material/Popup.qml \
    qml/QtQuick/Controls.2/Material/ToolBar.qml \
    qml/QtQuick/Controls.2/Material/SwitchDelegate.qml \
    qml/QtQuick/Controls.2/Material/RadioIndicator.qml \
    qml/QtQuick/Controls.2/Material/MenuItem.qml \
    qml/QtQuick/Controls.2/Material/RadioButton.qml \
    qml/QtQuick/Controls.2/Material/Tumbler.qml \
    qml/QtQuick/Controls.2/Material/CheckBox.qml \
    qml/QtQuick/Controls.2/Material/ApplicationWindow.qml \
    qml/QtQuick/Controls.2/Material/ItemDelegate.qml \
    qml/QtQuick/Controls.2/Material/TabBar.qml \
    qml/QtQuick/Controls.2/Material/BoxShadow.qml \
    qml/QtQuick/Controls.2/Material/ComboBox.qml \
    qml/QtQuick/Controls.2/Material/RadioDelegate.qml \
    qml/QtQuick/Controls.2/Material/SpinBox.qml \
    qml/QtQuick/Controls.2/Material/GroupBox.qml \
    qml/QtQuick/Controls.2/Material/SwipeDelegate.qml \
    qml/QtQuick/Controls.2/Material/CheckDelegate.qml \
    qml/QtQuick/Controls.2/Material/SwipeView.qml \
    qml/QtQuick/Controls.2/Material/BusyIndicator.qml \
    qml/QtQuick/Controls.2/Material/TextField.qml \
    qml/QtQuick/Controls.2/Material/Pane.qml \
    qml/QtQuick/Controls.2/Material/ToolTip.qml \
    qml/QtQuick/Controls.2/Material/ScrollBar.qml \
    qml/QtQuick/Controls.2/Material/SwitchIndicator.qml \
    qml/QtQuick/Controls.2/Material/PageIndicator.qml \
    qml/QtQuick/Controls.2/SwitchIndicator.qml \
    qml/QtQuick/Controls.2/PageIndicator.qml \
    qml/QtQuick/Window.2/libwindowplugin.so \
    qml/QtQuick/Window.2/plugins.qmltypes \
    qml/QtQuick/Window.2/qmldir \
    qml/QtQuick/Layouts/libqquicklayoutsplugin.so \
    qml/QtQuick/Layouts/plugins.qmltypes \
    qml/QtQuick/Layouts/qmldir \
    qml/QtQml/Models.2/libmodelsplugin.so \
    qml/QtQml/Models.2/plugins.qmltypes \
    qml/QtQml/Models.2/qmldir \
    qml/QtQml/plugins.qmltypes \
    qml/QtQml/qmldir \
    qml/QtQml/StateMachine/libqtqmlstatemachine.so \
    qml/QtQml/StateMachine/plugins.qmltypes \
    qml/QtQml/StateMachine/qmldir \
    qml/QtQuick/Extras/Private/CircularButton.qml \
    qml/QtQuick/Extras/Private/CircularButtonStyleHelper.qml \
    qml/QtQuick/Extras/Private/CircularTickmarkLabel.qml \
    qml/QtQuick/Extras/Private/Handle.qml \
    qml/QtQuick/Extras/Private/PieMenuIcon.qml \
    qml/QtQuick/Extras/Private/qmldir \
    qml/QtQuick/Extras/Private/TextSingleton.qml \
    qml/QtGraphicalEffects/Blend.qml \
    qml/QtGraphicalEffects/BrightnessContrast.qml \
    qml/QtGraphicalEffects/Colorize.qml \
    qml/QtGraphicalEffects/ColorOverlay.qml \
    qml/QtGraphicalEffects/ConicalGradient.qml \
    qml/QtGraphicalEffects/Desaturate.qml \
    qml/QtGraphicalEffects/DirectionalBlur.qml \
    qml/QtGraphicalEffects/Displace.qml \
    qml/QtGraphicalEffects/DropShadow.qml \
    qml/QtGraphicalEffects/FastBlur.qml \
    qml/QtGraphicalEffects/GammaAdjust.qml \
    qml/QtGraphicalEffects/GaussianBlur.qml \
    qml/QtGraphicalEffects/Glow.qml \
    qml/QtGraphicalEffects/HueSaturation.qml \
    qml/QtGraphicalEffects/InnerShadow.qml \
    qml/QtGraphicalEffects/LevelAdjust.qml \
    qml/QtGraphicalEffects/libqtgraphicaleffectsplugin.so \
    qml/QtGraphicalEffects/LinearGradient.qml \
    qml/QtGraphicalEffects/MaskedBlur.qml \
    qml/QtGraphicalEffects/OpacityMask.qml \
    qml/QtGraphicalEffects/private/DropShadowBase.qml \
    qml/QtGraphicalEffects/private/FastGlow.qml \
    qml/QtGraphicalEffects/private/FastInnerShadow.qml \
    qml/QtGraphicalEffects/private/FastMaskedBlur.qml \
    qml/QtGraphicalEffects/private/GaussianDirectionalBlur.qml \
    qml/QtGraphicalEffects/private/GaussianGlow.qml \
    qml/QtGraphicalEffects/private/GaussianInnerShadow.qml \
    qml/QtGraphicalEffects/private/GaussianMaskedBlur.qml \
    qml/QtGraphicalEffects/private/libqtgraphicaleffectsprivate.so \
    qml/QtGraphicalEffects/private/qmldir \
    qml/QtGraphicalEffects/qmldir \
    qml/QtGraphicalEffects/RadialBlur.qml \
    qml/QtGraphicalEffects/RadialGradient.qml \
    qml/QtGraphicalEffects/RectangularGlow.qml \
    qml/QtGraphicalEffects/RecursiveBlur.qml \
    qml/QtGraphicalEffects/ThresholdMask.qml \
    qml/QtGraphicalEffects/ZoomBlur.qml \
    qml/QtQuick/Extras/libqtquickextrasplugin.so \
    qml/QtQuick/Extras/plugins.qmltypes \
    qml/QtQuick/Extras/qmldir
#WINRT_MANIFEST.target = ComicKron.exe
#WINRT_MANIFEST.publisher = ComicKron

SOURCES += main.cpp \
    SignalHandler.cpp

HEADERS += \
    SignalHandler.h

OTHER_FILES += \
    $$ROOTDIR/platform/android/AndroidManifest.xml

mac {
    dylibs.path = Contents/MacOS
    dylibs.files = $$files($$LIBDIR/*)
    QMAKE_BUNDLE_DATA += dylibs
}
