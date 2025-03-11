import QtQuick 2.15
import QtQuick.Controls 2.15

import "components"

ApplicationWindow {
    id: win
    title: "ToDo"

    visible: true
    width: 1500
    height: 750

    color: "#15191E"

    Reg {
        anchors.centerIn: parent
    }
}