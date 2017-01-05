/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import ComicKron.FsItem 1.0

Item {
    id: root

    ListView {
        id: files
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        model: fileBrowserVM.items

        delegate: ItemDelegate {
            text: model.modelData.name
            width: parent.width
            height: 48
            leftPadding: 16
            rightPadding: 16
            anchors.topMargin: 8
            font.pixelSize: 16
            font.bold: model.modelData.type

            onClicked: {
                if (model.modelData.type === FsItem.FOLDER) {
                    fileBrowserVM.navigateToFolder(model.modelData.name)
                }
                else {
                    fileBrowserVM.openFile(model.modelData.name)
                }
            }
        }
    }
}
