import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    id: editTask
    objectName: "editTask"

    width: profileWidth
    height: profileHeight

    color: "white"

    property real profileWidth: 100  
    property real profileHeight: 100

    radius: Math.min(width, height) / 4

    MouseArea {
        anchors.fill: parent

        onClicked: {
            taskHandler.openEditorWin()
        } 
    }

    Image {
        anchors.fill: parent
        anchors.margins: 10

        fillMode: Image.PreserveAspectFit
        source: "qrc:/ui/assets/images/write.png"
    }
}