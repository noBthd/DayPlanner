import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 
import todo 0.1

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    width: 750
    height: 750
    minimumWidth: 500
    minimumHeight: 250

    visible: true
    color: "#0C121D"

    Component.onCompleted: {
        taskHandler.setDeletedTasks()
    }

    Component.onDestruction: {
        taskHandler.clearDeletedTasks()
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
                    model: taskHandler.lvdeltask() 

                    anchors.fill: parent
                    anchors.bottomMargin: index == lv.model ? 0 : 10
                    spacing: 10

                    snapMode: ListView.SnapOneItem

                    delegate: Task {
                        taskName: name
                        taskText: text
                        taskStatus: status

                        width: ListView.view.width - 20
                        height: 100

                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        } // taks background      
    }
}
