import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: addTask
    objectName: "addTask"

    width: profileWidth
    height: profileHeight

    color: "white"

    property real profileWidth: 100  
    property real profileHeight: 100

    radius: Math.min(width, height) / 4

    MouseArea {
        anchors.fill: parent

        onClicked: {
            taskHandler.openAdditionWin()
        } 
    }

    Image {
        width: parent.width
        height: parent.height

        fillMode: Image.PreserveAspectFit
        source: "qrc:/ui/assets/images/note.png"
    }
}