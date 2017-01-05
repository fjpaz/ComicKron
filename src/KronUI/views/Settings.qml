/*********************************************************************
 * Copyright (C) 2017 Francisco Javier Paz Menendez
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Flickable {
    id: root
    property bool darkTheme: darkThemeSwitch.checked

    Pane {
        anchors.fill: parent

        ColumnLayout {
            id: content
            anchors.right: parent.right
            anchors.left: parent.left

            Switch {
                id: darkThemeSwitch
                text: qsTr("Dark Theme")
                font.pixelSize: 14
                checked: window.Material.theme
                onClicked: {
                    window.Material.theme = darkTheme ? Material.Dark : Material.Light
                }
            }

            ComboBox {
                model: ["0.5", "1"]
                onActivated: device.setScaleFactor(currentText)
            }
        }
    }
}
