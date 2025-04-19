import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    width: niWidth
    height: niHeight

    property int niWidth: 160
    property int niHeight: 21 
    property string niText: ti.text

    color: "#ffffff"
    radius: 12.5

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        spacing: 1

        Text {
            Layout.preferredWidth: 49
            Layout.alignment: Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter

            text: "name:"

            font.bold: true
            font.pixelSize: 16
            color: "#000000"
        }


        TextInput {
            id: ti

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter

            verticalAlignment: Text.AlignVCenter
            clip: true
        }
    
    }
}