import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

Rectangle {
    width: ccWidth
    height: ccHeight

    property real ccWidth: 104
    property real ccHeight: 29

    color: "#2C2C2C"
    radius: 12.5

    Text {
        anchors.margins: 10
        anchors.centerIn: parent

        text: "completeness"

        font.bold: true
        font.pixelSize: 12
        color: "#ffffff"
    }
}