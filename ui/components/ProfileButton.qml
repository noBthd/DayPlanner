import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 130
    height: 50

    radius: 10

    color: "#2f3842"

    Row {
        width: parent.width
        height: parent.height 

        spacing: 5
        leftPadding: 5

        anchors.centerIn: parent

        Rectangle {
            width: 40
            height: 40

            radius: 40
            color: "#ffffff"

            anchors.verticalCenter: parent.verticalCenter

            Image {
                width: 40
                height: 40

                anchors.verticalCenter: parent.verticalCenter

                source: "qrc:/ui/assets/images/profile.png"
            }
        }

        Column {
            Item {
                width: 80
                height: 25

                Text {
                    anchors.centerIn: parent

                    text: "Username"

                    font: {
                        pixelSize: 12
                    }
                }
            }

            Item {
                width: 80
                height: 25

                Row {
                    height: parent.height 

                    spacing: 5
                    leftPadding: 5
                    rightPadding: 5

                    anchors.centerIn: parent

                    Text {
                        anchors.verticalCenter: parent.verticalCenter

                        text: "logout"
                        
                        font {
                            pixelSize: 12
                        }
                    }

                    Image {
                        width: 20
                        height: 20

                        anchors.verticalCenter: parent.verticalCenter

                        source: "qrc:/ui/assets/images/leave.png"
                    }
                }
            }
        }
    }
}