import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

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
        spacing: 0  

        // Exit Image
        Image {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 3  
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40

            fillMode: Image.PreserveAspectFit
            source: "qrc:/ui/assets/images/deleteTask.png"
        } // Exit Image

        // Exit Text
        Text {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: -5  
            Layout.bottomMargin: 5  

            text: "exit"
            font.bold: true
            font.pixelSize: 12
            color: "#000000"
        } // Exit Text
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            taskHandler.closeAdditionWin()
        }
    }
}