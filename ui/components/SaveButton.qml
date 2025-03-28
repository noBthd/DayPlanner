import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

//! fix errors with y: t.y - 5
Rectangle {
    width: sbWidth
    height: sbHeight

    property real sbWidth: 60
    property real sbHeight: 60

    color: "#D9D9D9"
    radius: 12.5

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Layout.fillWidth: true
        Layout.fillHeight: true

        // Save Image
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 3

            Layout.preferredWidth: 40
            Layout.preferredHeight: 40

            fillMode: Image.PreserveAspectFit
            source: "qrc:/ui/assets/images/saveTask.png"

        } // Save Image

        // Save Text
        Text {
            id: t
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
            y: t.y - 5

            text: "save"

            font.bold: true
            font.pixelSize: 12
            color: "#000000"
        } // Save Text
    }

    MouseArea {
        anchors.fill: parent
    }
}