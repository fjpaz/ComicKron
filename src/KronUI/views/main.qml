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

ApplicationWindow {
    id: window
    visible: true
    visibility: Qt.platform.os == "android" ? Window.FullScreen : Window.Windowed
    width: 600
    height: 1000

    Material.theme: Material.Light
    Material.primary: Material.BlueGrey
    Material.accent: Material.DeepOrange

    header: ToolBar {
        id: toolbar
        height: device.dp(56)
        font.pixelSize: device.sp(20)

        RowLayout {
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/drawer.png"
                }
                onClicked: drawer.open()
            }

            Label {
                text: qsTr(Qt.application.name)
            }

            Item { Layout.fillWidth: true }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
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
        width: Math.min(parent.width, parent.height) / 3
        height: window.height

        Rectangle {
            id: drawerHeader
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            width: parent.width
            height: device.dp(192)
            color: Material.primary
        }

        ListView {
            id: destinations
            anchors.top: drawerHeader.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            model: ListModel {
                id: destinationsModel

                ListElement {
                    name: qsTr("Browser")
                    source: "qrc:/views/FileBrowser.qml"
                    showToolbar: true
                }

                ListElement {
                    name: qsTr("Reader")
                    source: "qrc:/views/ComicReader.qml"
                    showToolbar: false
                }
            }

            delegate: ItemDelegate {
                width: parent.width
                highlighted: ListView.isCurrentItem
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
