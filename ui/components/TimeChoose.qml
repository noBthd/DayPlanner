import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

// Background
Rectangle { 
    width: tcWidth
    height: tcHeight

    property real tcWidth: 193
    property real tcHeight: 29

    property string tcDate: "date: 12.12.2025"
    property string tcTime: "time: 15:23"

    color: "#ffffff"
    radius: 12.5
 
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        // Date 
        Text {
            Layout.fillWidth: true

            anchors.verticalCenter: parent.verticalCenter

            text: tcDate
            font.bold: true
            font.pixelSize: 12

            color: "#000000"
        } // Date 

        // Time
        Text {
            Layout.fillWidth: true

            anchors.verticalCenter: parent.verticalCenter

            text: tcTime
            font.bold: true
            font.pixelSize: 12

            color: "#000000"
        } // Time
    }
    // date Text
} // Background