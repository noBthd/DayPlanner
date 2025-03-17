import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 150
    height: 50

    radius: 10

    color: "#2f3842"

    Row {
        anchors.centerIn: parent
        spacing: 10

        Image {
            width: 40
            height: 40

            visible: true

            source: "qrc:/ui/assets/icons/profile.png"
        }
    }
}