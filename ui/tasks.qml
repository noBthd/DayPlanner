import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 
import todo 0.1

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    width: 1500
    height: 750
    minimumWidth: 500
    minimumHeight: 250

    visible: true
    color: "#0C121D"

    Component.onCompleted: {
        taskHandler.setUser()
    }

    GridLayout {
        anchors.fill: parent  
        anchors.margins: 10

        rows: 3
        columns: 2

        rowSpacing: 10
        columnSpacing: 10

        // tasks background
        Rectangle {
            id: tasksBackground

            Layout.row: 0
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            radius: 12.5
            color: "#222B3B"

            Item {
                id: ilv
                anchors.centerIn: parent

                width: parent.width
                height: parent.height - 20 

                clip: true
                ListView {
                    id: lv
                    objectName: "lv"
                    model: taskHandler.lvtask() 

                    anchors.fill: parent
                    anchors.bottomMargin: index == lv.model ? 0 : 10
                    spacing: 10

                    snapMode: ListView.SnapOneItem
                    property int tid: -1

                    delegate: Task {
                        taskName: name
                        taskText: text
                        taskStatus: status

                        width: ListView.view.width - 20
                        height: 100

                        anchors.horizontalCenter: parent.horizontalCenter

                        tqid: index

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                lv.tid = index
                            }
                        }
                    }
                }
            }
        } // tasks background   
        
        ColumnLayout {
            Layout.row: 0
            Layout.column: 1

            Layout.alignment: Qt.AlignTop
            spacing: 10

            ProfileButton {} 
            SortByComp {}
            OpenPhoto {
                id: root
                
                MouseArea {            
                    anchors.fill: parent

                    onClicked: {
                        if(taskHandler.hasPhoto(lv.tid)) {
                            console.log("button clicked")
                            taskHandler.writeFileData(lv.tid)

                            var component = Qt.createComponent("photoWin.qml")
                            if (component.status === Component.Ready) {
                                var win = component.createObject()
                                win.imagePath = taskHandler.getFilePath() + "?" + Date.now()
                                win.visible = true
                            } else {
                                console.error("Failed to load photoWin.qml")
                            }
                        }

                    }
                }
            }
        }

        // task managment buttons
        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.fillWidth: true
            Layout.preferredHeight: 50 

            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 10

                AddTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
                }

                RedTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            taskHandler.openEditorWin(lv.tid)
                        }
                    }
                }

                RemTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            taskHandler.delTask(lv.tid)
                            lv.tid = -1
                        } 
                    }
                }

                AddPhoto {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height

                    task_id: lv.tid
                }
            }
        } // task managment buttons

        AdminButton {
            Layout.row: 1
            Layout.column: 1

            visible: isAdmin

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    taskHandler.openAdminWin()
                }
            }
        }
    }
}
