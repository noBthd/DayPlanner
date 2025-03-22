import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    id: task
    objectName: "task"

    width: taskWidth
    height: taskHeight

    property real taskWidth: 100  
    property real taskHeight: 100

    radius: 12.5
    color: "#c2c2c2"

    property string taskName: "Name"
    property string taskText: "Test textoviwy delo adasdasdasdjksl"

    GridLayout {
        anchors.fill: parent  
        anchors.margins: 10

        rows: 2
        columns: 2

        // task name
        Text {
            Layout.row: 0
            Layout.column: 0

            Layout.preferredWidth: 50
            Layout.preferredHeight: 12

            text: taskName

            font.pixelSize: 12
            font.bold: true
        } // task name

        // task text
        Text {
            Layout.row: 1
            Layout.column: 0

            Layout.preferredWidth: 50
            Layout.fillHeight: true

            text: taskText
            

            font.pixelSize: 12
        } // task text
    }
}