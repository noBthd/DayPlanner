import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 6.5
import todo 0.1

Rectangle {
    id: addPhoto
    objectName: "addPhoto"

    width: profileWidth
    height: profileHeight

    color: "white"

    property real profileWidth: 100  
    property real profileHeight: 100

    radius: Math.min(width, height) / 4

    property int task_id: -1

    //TODO: fix photo path error
    //TODO: add func that takes task id and uploads photo into a db
    //! qrc:/ui/components/AddPhoto.qml:25: Error: Cannot assign [undefined] to QString
    FileDialog {
        id: fileDialog
        title: "Select a file"
        nameFilters: ["Images (*.png *.jpg *.jpeg *.bmp)", "All files (*)"]
        onAccepted: {
            console.log("Selected file:", fileDialog.selectedFile)
            selectedFilePath = fileDialog.selectedFile
            taskHandler.addPhoto(selectedFile, task_id)
        }
    }

    property string selectedFilePath: ""

    MouseArea {
        anchors.fill: parent

        onClicked: {
            fileDialog.open()
        } 
    }

    Image {
        width: parent.width
        height: parent.height

        fillMode: Image.PreserveAspectFit
        source: "qrc:/ui/assets/images/note.png"
    }
}