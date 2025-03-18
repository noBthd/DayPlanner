import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    width: 1500
    height: 750
    minimumWidth: 500
    minimumHeight: 250

    visible: true
    color: "#15191E"

    GridLayout {
        anchors.fill: parent  // Автоматически заполняет весь экран
        anchors.margins: 10

        rows: 2
        columns: 2

        rowSpacing: 10
        columnSpacing: 10

        Rectangle {
            id: tasksBackground

            Layout.row: 0
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            radius: Math.min(width, height) / 25
            color: "#2f3842"
        }        

        ProfileButton {
            Layout.row: 0
            Layout.column: 1

            Layout.alignment: Qt.AlignTop
        }

        AddTask {
            Layout.row: 1
            Layout.column: 0

            Layout.preferredWidth: tasksBackground.width / 2
            Layout.preferredHeight: win.height * 0.1
        }
    }
}
