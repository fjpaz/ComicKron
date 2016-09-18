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
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 1000
    color: "black"

    // Method to compute component size using device independent pixels
    function dp(number) {
        console.log(number + ", dp: " + Math.round(number*((Screen.pixelDensity*25.4)/160)))
        return Math.round(number*((Screen.pixelDensity*25.4)/160));
    }

    Material.theme: Material.Light
    Material.primary: Material.BlueGrey
    Material.accent: Material.DeepOrange
//    Material.background: Material.BlueGrey
//    Material.foreground: Material.Amber

    Settings {
        id: settings
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

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
                    name: qsTr("Library")
                    source: "qrc:/views/Library.qml"
                }

                ListElement {
                    name: qsTr("Browser")
                    source: "qrc:/views/FileBrowser.qml"
                }
            }

            delegate: ItemDelegate {
                width: parent.width
                highlighted: ListView.isCurrentItem
                text: model.name
                onClicked: {
                    if (destinations.currentIndex != index) {
                        destinations.currentIndex = index
                        stack.replace(model.source)
                    }
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stack
        initialItem: Qt.resolvedUrl("qrc:/views/FileBrowser.qml")
        anchors.fill: parent
    }

    ComicReader {
        id: reader
        visible: false
        anchors.fill: parent
    }

    Component.onCompleted: device.setWindow(window)
}
