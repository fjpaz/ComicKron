/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

import QtQuick 2.2
import QtQuick.Dialogs 1.1

Item {
    id: root

    function updateImage() {
        console.log("Update Image")
        image.source = ""
        image.source = "image://comic/current"
    }

    Image {
        id: image
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        cache: false
    }

    MouseArea {
        width: parent.width / 4
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top

        onClicked: {
            console.log("Next Page")
            model.goForward()
        }
    }

    MouseArea {
        width: parent.width / 4
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            console.log("Previous Page")
            model.goBackward()
        }
    }

    MouseArea {
        width: parent.width / 2
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        onClicked: {
            console.log("Middle mouse area")
            fileDialog.visible = true
        }
    }

    FileDialog {
        id: fileDialog
        title: "Open comic ..."
        onAccepted: {
            console.log("File opened: " + fileDialog.fileUrl)
            model.openComic(fileDialog.fileUrl)
            fileDialog.close()
        }
        onRejected: {
            console.log("File opening canceled")
            fileDialog.close()
        }
        Component.onCompleted: {
            fileDialog.open()
        }
    }

    Connections {
        target: model
        onPageUpdated: {
            console.log("Comic Image Changed")
            updateImage()
        }
    }
}
