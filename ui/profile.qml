import QtQuick 2.15
import QtQuick.Controls 2.15

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    visible: true
    width: 1500
    height: 750

    color: "#15191E"

    ProfileButton {
        anchors.top: parent.top
        anchors.topMargin: 10

        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}