import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Rectangle {
    id: sroot

    width: sText.paintedWidth + sIcon.width + 2 + 4 + 2 + 6
    // 2 (левый отступ) + 4 (зазор между текстом и кружком) + 2 (правый отступ) + (нехватает потому что заезжает)
    height: sHeight

    property int sHeight: 20

    property string sStatus: "def" //? default(gray)/done(green)/not(red)/in progress(orange)
    
    property string sColor: {
        switch (sStatus) {
        case "done":
            return "green"
        case "not done":
            return "#9e0000"
        case "in progress":
            return "#da7d20"
        default:
            return "#9c9c9c"
        }
    }

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

            color: sColor
            radius: width / 2
            
            anchors.right: parent.right
            anchors.rightMargin: 1
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
