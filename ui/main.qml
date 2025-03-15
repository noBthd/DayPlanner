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

    Loader {
        id: pl
        source: "qrc:/ui/main.qml"
        anchors.fill: parent
    }

    Connections {
        target: regHandler
        function onChangePage(url) {
            pl.source = url;
        }
    }

    Reg {
        anchors.centerIn: parent
    }
}