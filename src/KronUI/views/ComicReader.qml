/*********************************************************************
 * Copyright (C) 2015 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import ComicKron 1.0

Item {
    id: root

    ImageShowcase {
        id: imageShowcase
        anchors.fill: parent
        image: readerVM.page
    }

    MouseArea {
        width: parent.width / 4
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top

        onClicked: {
            console.log("Next Page")
            readerVM.goForward()
        }
    }

    MouseArea {
        width: parent.width / 4
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            console.log("Previous Page")
            readerVM.goBackward()
        }
    }

    MouseArea {
        width: parent.width / 2
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        onClicked: {
            console.log("Middle mouse area")
            drawer.position = 1 - drawer.position
        }
    }
}
