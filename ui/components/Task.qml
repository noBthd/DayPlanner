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
    property string taskStatus: "def"

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing.type: Easing.OutQuad
        }
    }
    

    SequentialAnimation {
        id: scaleAnimation
        NumberAnimation {
            target: task
            property: "scale"
            to: 0.995
            duration: 100
            easing.type: Easing.OutQuad
        }
        NumberAnimation {
            target: task
            property: "scale"
            to: 1.005
            duration: 100
            easing.type: Easing.OutQuad
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

        columnSpacing: 10

        // task name
        Text {
            Layout.row: 0
            Layout.column: 0

            Layout.preferredWidth: 20
            Layout.preferredHeight: 16

            text: taskName
            color: "#333333"

            font.pixelSize: 16
            font.bold: true
        } // task name

        //! fix grid layout error
        // status indicator
        Status {
            Layout.row: 0
            Layout.column: 0

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            sHeight: 16
            sStatus: taskStatus
        } // status indicator
    
        // splitter
        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 1
            color: "#999999"
        } // splitter

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