import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 


//! fix animation error
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
            easing: Easing.InQuad
        }
    }
    

    SequentialAnimation {
        id: scaleAnimation
        NumberAnimation {
            target: task
            property: "scale"
            to: 0.995
            duration: 100
            easing: Easing.InQuad
        }
        NumberAnimation {
            target: task
            property: "scale"
            to: 1.005
            duration: 100
            easing: Easing.InQuad
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

        rows: 3
        columns: 2

        // task name
        Text {
            Layout.row: 0
            Layout.column: 0

            Layout.preferredWidth: 50
            Layout.preferredHeight: 16

            text: taskName
            color: "#333333"

            font.pixelSize: 16
            font.bold: true
        } // task name

        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 1
            color: "#999999"
        }

        // task text
        Text {
            Layout.row: 2
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: taskText
            color: "#555555"
            wrapMode: Text.Wrap

            font.pixelSize: 14
        } // task text
    }
}