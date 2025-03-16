import QtQuick 2.15
import QtQuick.Controls 2.15

import "components"

ApplicationWindow {
    id: win
    title: "TEST"

    visible: true
    width: 750
    height: 750

    color: "#ffffff"

    Reg {
        anchors.centerIn: parent
    }
}