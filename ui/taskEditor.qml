import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    width: 600
    height: 500
    minimumWidth: 500
    minimumHeight: 250

    visible: true
    color: "#0C121D"

    property int t_qid

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10

        rows: 4
        columns: 3

        rowSpacing: 10
        columnSpacing: 10

        // just text
        Text {
            Layout.fillWidth: true

            Layout.row: 0
            Layout.column: 0

            text: "EDIT"

            font.bold: true
            font.pixelSize: 24
            color: "#ffffff"
        } // just text

        SaveButton {
            Layout.row: 0
            Layout.column: 1

            Layout.rowSpan: 2

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    console.log("  NAME: ", ni.textInput.text) 
                    console.log("STATUS: ", tti.ttStatus)
                    console.log("  TEXT: ", tti.ttString)
                    taskHandler.editTask(ni.niText, tti.ttStatus, tti.ttString)
                    taskHandler.closeEditorWin()

                    ni.textInput.text = ""
                    tti.ttStatus.text = "status"
                    tti.textInput.text = ""
                }
            }
        }

        ExitButton {
            Layout.row: 0
            Layout.column: 2
            
            Layout.rowSpan: 2

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    taskHandler.closeEditorWin()
                }
            }
        }

        NameInput {
            id: ni

            Layout.row: 1
            Layout.column: 0
        }

        // splitter
        Rectangle {
            Layout.row: 2
            Layout.column: 0

            Layout.columnSpan: 3

            Layout.fillWidth: true
            Layout.preferredHeight: 1
        } // splitter

        TextTimeInput {
            id: tti

            Layout.row: 3
            Layout.column: 0

            Layout.columnSpan: 3

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}