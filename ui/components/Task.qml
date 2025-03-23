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
    color: ma.containsMouse ? "#ffffff" : "#c2c2c2"

    property string taskName: "Name"
    property string taskText: "Test textoviwy delo adasdasdasdjksl"

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing: Easing.In
        }
    }

    SequentialAnimation {
        id: scaleAnimation
        NumberAnimation {
            target: task
            property: "scale"
            to: 0.995
            duration: 100
            easing: Easing.In
        }
        NumberAnimation {
            target: task
            property: "scale"
            to: 1.005
            duration: 100
            easing: Easing.In
        }
    }

    MouseArea {
        id: ma
        anchors.fill: parent

        hoverEnabled: true
        onEntered: {
            parent.scale = 1.005
        }
        onExited: {
            parent.scale = 1.0
        }

        onClicked: {
            scaleAnimation.start()
        }
    }

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