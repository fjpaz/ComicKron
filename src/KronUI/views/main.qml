/* *******************************************************************
 * Copyright (C) 2014 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * ******************************************************************/

import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 600
    height: 1000
    color: "black"

    ComicReader {
        id: viewer
        anchors.fill: parent
    }
}
