import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

// Background
Rectangle { 
    width: tcWidth
    height: tcHeight

    property real tcWidth: tcDate.paintedWidth + 20
    property real tcHeight: 29

    property string tcDateText: "date: 12.12.2025"

    color: "#ffffff"
    radius: 12.5
 
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        // Date 
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height

            Text {
                id: tcDate
                anchors.centerIn: parent

                text: tcDateText
                font.bold: true
                font.pixelSize: 12
                color: "#000000"
            }
        } // Date 
    }
} // Background