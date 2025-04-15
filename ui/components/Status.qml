import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Rectangle {
    id: sroot


    width: sText.paintedWidth + sIcon.width + 2 + 4 + 2 + 6
    // 2 (левый отступ) + 4 (зазор между текстом и кружком) + 2 (правый отступ) + (нехватает потому что заезжает)
    height: sHeight

    property int sHeight: 20

    property string sStatus: "in progress" //? done(green)/not(red)/in progress(blue)

    radius: sHeight / 2
    color: "#222B3B"

    Row {
        anchors.fill: parent
        anchors.margins: 2
        spacing: 4

        Text {
            id: sText

            text: sStatus
            color: "#ffffff"

            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
            font.bold: true

            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: sIcon
            width: sHeight - 4
            height: sHeight - 4

            color: "green"
            radius: width / 2
            
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
