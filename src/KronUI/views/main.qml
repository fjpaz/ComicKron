/* *******************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * ******************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.0
import ComicKron.Device 1.0

ApplicationWindow {
    id: window
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.Windowed
    minimumWidth: device.dp(320)
    minimumHeight: device.dp(480)
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto/Roboto-Regular.ttf" }

    Material.theme: Material.Light
    Material.primary: Material.BlueGrey
    Material.accent: Material.DeepOrange

    header: ToolBar {
        id: toolbar
        height: device.dp(56)
        font.pixelSize: device.sp(20)

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: device.dp(16)
            anchors.rightMargin: device.dp(16)

            ToolButton {
                contentItem: Image {
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: device.dp(48)
                    sourceSize.height: device.dp(48)
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/drawer.png"
                }
                onClicked: drawer.open()
            }

            Label {
                leftPadding: device.dp(8)
                text: qsTr(Qt.application.name)
                font.pixelSize: device.sp(20)
            }

            Item { Layout.fillWidth: true }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: device.dp(48)
                    sourceSize.height: device.dp(48)
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: console.debug("Settings clicked")
            }
        }
    }

    Drawer {
        id: drawer
        width: (device.layout === Device.SMALL) ? device.dp(280) : device.dp(320)
        height: window.height

        Rectangle {
            id: drawerHeader
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            width: parent.width
            height: device.dp(192)
            color: Material.primary
            z: 1
        }

        Image {
            id: drawerIcon
            anchors.centerIn: drawerHeader
            fillMode: Image.PreserveAspectFit
            sourceSize.width: device.dp(72)
            sourceSize.height: device.dp(72)
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "qrc:/images/comickron.png"
            z: 1
        }

        ListView {
            id: destinations
            anchors.top: drawerHeader.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            boundsBehavior: Flickable.StopAtBounds
            model: ListModel {
                id: destinationsModel

                ListElement {
                    name: qsTr("Browser")
                    source: "qrc:/views/FileBrowser.qml"
                    icon: "qrc:/images/browser.png"
                    showToolbar: true
                }

                ListElement {
                    name: qsTr("Reader")
                    source: "qrc:/views/ComicReader.qml"
                    icon: "qrc:/images/reader.png"
                    showToolbar: false
                }
            }

            delegate: ItemDelegate {
                width: parent.width
                height: device.dp(48)
                leftPadding: device.dp(72)
                rightPadding: device.dp(72)
                font.pixelSize: device.sp(16)
                font.bold: false
                highlighted: ListView.isCurrentItem
                indicator: Image {
                    id: itemIcon
                    anchors.left: parent.left
                    anchors.leftMargin: device.dp(16)
                    anchors.verticalCenter: parent.verticalCenter
                    source: model.icon
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: device.dp(24)
                    sourceSize.height: device.dp(24)
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                }
                text: model.name
                onClicked: {
                    if (destinations.currentIndex != index)
                        destinations.currentIndex = index
                }
            }

            onCurrentIndexChanged: {
                var currentDestination = model.get(currentIndex)
                console.log("Navigate to " + currentDestination.name)

                if (currentDestination.showToolbar)
                    window.header = toolbar
                else
                    window.header = null

                stack.replace(currentDestination.source)
                drawer.close()
            }

            function navigateToReader() {
                destinations.currentIndex = 1
            }
        }
    }

    StackView {
        id: stack
        focus: true
        initialItem: Qt.resolvedUrl("qrc:/views/FileBrowser.qml")
        anchors.fill: parent
    }

    Connections {
        target: fileBrowserVM
        onFileOpened: {
            console.log("File " + fileUrl + " opened")
            destinations.navigateToReader()
            readerVM.openComic(fileUrl)
        }
    }

    Component.onCompleted: device.setWindow(window)
}
