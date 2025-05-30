import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    width: 130
    height: 40

    radius: 12
    color: "#222B3B"

    MouseArea {
        anchors.fill: parent

        onClicked: {
            console.log("button clicked")
            taskHandler.sortByTaksStatus()
        }
    }

    Row {
        anchors.fill: parent
        anchors.centerIn: parent

        Text {
            text: "sort by status"
            anchors.fill: parent
            anchors.centerIn: parent

            color: "#ffffff"
            
            font.pixelSize: 12
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
