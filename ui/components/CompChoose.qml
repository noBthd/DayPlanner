import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    width: ccWidth
    height: ccHeight

    property real ccWidth: ccText.paintedWidth + ccIcon.width + 20
    property real ccHeight: 29
    property string ccStatus: "status"
    property string ccColor: "#9c9c9c"

    color: "#2C2C2C"
    radius: 12.5

    Row {
        spacing: 5
        anchors.fill: parent
        anchors.margins: 10

        Text {
            id: ccText

            anchors.verticalCenter: parent.verticalCenter

            text: ccStatus

            font.bold: true
            font.pixelSize: 12
            color: "#ffffff"
        }

        Rectangle {
            id: ccIcon

            width: ccHeight - 10
            height: ccHeight - 10

            anchors.verticalCenter: parent.verticalCenter

            color: ccColor
            radius: ccHeight - 10 / 2
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            if (ccStatus === "not done") {
                ccStatus = "in progress"
                ccColor = "#da7d20"
            } else if (ccStatus === "in progress") {
                ccStatus = "done"
                ccColor = "green"
            } else {
                ccStatus = "not done"
                ccColor = "#9e0000" 
            }
        }
    }
}
