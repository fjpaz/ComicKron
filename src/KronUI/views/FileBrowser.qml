/*********************************************************************
 * Copyright (C) 2016 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
    id: root

    ListView {
        id: files
        model: {
        }

        delegate: ItemDelegate {
            text: model.fileName
        }
    }

//    Connections {
//        target: fileBrowserVM
//        onPageUpdated: {
//            console.log("Comic Image Changed")
//            updateImage()
//    }
}
