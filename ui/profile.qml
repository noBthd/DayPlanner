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
        anchors.fill: parent  
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

            // radius: Math.min(width, height) / 25
            radius: 12.5
            color: "#2f3842"
        }        

        ProfileButton {
            Layout.row: 0
            Layout.column: 1

            Layout.alignment: Qt.AlignTop
        }

        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.fillWidth: true
            Layout.preferredHeight: 50 

            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 10

                AddTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
                }

                RemTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
                }
            }
        }
    }
}
