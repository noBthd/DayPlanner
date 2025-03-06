import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: regWin
    title: "ToDo"

    visible: true
    height: 750
    width: 1500

    Rectangle {
        id: regWinBack
        anchors.fill: parent
        color: "#15191E"

        Column {
            anchors.centerIn: parent
            spacing: 10
        
            // inputs
            Rectangle {
                id: loginBack
                height: 30
                width: 250
                radius: 5
                color: "#ffffff"
    
                TextInput {
                    id: loginInput
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
            Rectangle {
                id: passwordBack
                height: 30
                width: 250
                radius: 5
                color: "#ffffff"
    
                TextInput {
                    id: passwordInput
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

            // regisration and login buttons
            Row {
                spacing: 10

                Button {
                    id: regBtn
                    text: "Registrate"
                    // onClicked: 

                    height: 30
                    width: 120
                }
                Button {
                    id: logBtn
                    text: "Login"
                    // onClicked: 
                
                    height: 30
                    width: 120
                }
            }
        }
    }
}