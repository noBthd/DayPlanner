import QtQuick 2.15
import QtQuick.Controls 2.15
import todo 0.1

ApplicationWindow {
    id: imageViewer

    width: 600
    height: 400

    title: "File"
    visible: false

    property string imagePath: ""

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: imageViewer.imagePath
    }
}