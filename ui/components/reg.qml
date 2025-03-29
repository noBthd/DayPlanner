import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: regBack

    height: 250
    width: 300
    radius: 30
    color: "#222B3B"

    Column {
        anchors.centerIn: parent
        spacing: 20 

        Text {
            text: "Registration"
            anchors.horizontalCenter: parent.horizontalCenter
            y: -10  

            font {
                pixelSize: 24
                bold: true
            }
            color: "#ffffff"
        }
    
        // login
        Rectangle {
            id: loginBack
            height: 30
            width: 250
            radius: 5
            color: "#ffffff"

            TextInput {
                clip: true
                id: loginInput
                objectName: "loginInput"
                anchors.centerIn: parent

                height: 20
                width: 230 

                property string placeholderText: "login"
                Text {
                    text: loginInput.placeholderText
                    visible: !loginInput.text
                    color: "#484f54"
                }
            }
        }

        // password
        Rectangle {
            id: passwordBack
            height: 30
            width: 250
            radius: 5
            color: "#ffffff"

            TextInput {
                clip: true
                id: passwordInput
                objectName: "passwordInput"
                anchors.centerIn: parent

                height: 20
                width: 230

                echoMode: TextInput.Password

                property string placeholderText: "password"
                Text {
                    text: passwordInput.placeholderText
                    visible: !passwordInput.text
                    color: "#484f54"
                }
            }
        }

        // registration and login buttons
        Row {
            spacing: 10

            Button {
                id: regBtn
                text: "Registrate"

                height: 50
                width: 120

                onClicked: {
                    regHandler.regUser(loginInput.text, passwordInput.text)
                }
            }
            Button {
                id: logBtn
                text: "Login"

                height: 50
                width: 120

                onClicked: {
                    regHandler.loginUser(loginInput.text, passwordInput.text)
                }
            }
        }
    }
}
