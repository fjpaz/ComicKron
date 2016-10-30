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

    Comic {
        id: comic
        focus: true
        anchors.fill: parent
        image: readerVM.page
    }

    Connections {
        target: comic
        onNextRequested: {
            console.log("Go Forward")
            readerVM.goForward()
        }
        onPreviousRequested: {
            console.log("Go Backward")
            readerVM.goBackward()
        }
        onMoreActionsRequested: {
            console.log("More Actions")
            drawer.open()
        }
    }
}
