import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15 

ApplicationWindow {
    id: win
    title: qsTr("Admin Panel") 

    width: 250
    height: 500

    minimumWidth: 230
    minimumHeight: 250

    visible: true
    color: "#0C121D"

    GridLayout {
        anchors.fill: parent

        rows: 3
        columns: 2

        rowSpacing: 10
        columnSpacing: 10

        anchors.margins: 20

        TextField { 
            id: textField

            Layout.maximumWidth: 100 
            Layout.maximumHeight: 40

            Layout.row: 0
            Layout.column: 0

            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            placeholderText: qsTr("Enter text") 
        }

        Rectangle {
            id: rect

            Layout.row: 0
            Layout.column: 1 

            width: 100 
            height: 40

            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            color: "#222B3B" 
            radius: 12

            Text {
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("delete user")
                color: "#ffffff"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Rectangle clicked!")  
                    console.log("TEXT: ", textField.text)                 
                }
            }
        }
    }
}