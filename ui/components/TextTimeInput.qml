import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 

// import "components"

Rectangle {
    id: bg

    width: ttWidth
    height: ttHeight

    property real ttWidth: 580
    property real ttHeight: 400

    color: "#D9D9D9"
    radius: 12.5

    GridLayout {
        id: gl

        anchors.fill: parent  
        anchors.margins: 10

        rows: 3
        columns: 3

        rowSpacing: 10
        columnSpacing: 10

        // Header
        Text { 
            Layout.row: 0
            Layout.column: 0

            Layout.columnSpan: 3

            Layout.fillWidth: true

            text: "Text"
            font.bold: true
            font.pixelSize: 24

            color: black
        } // Header

        // Item { Layout.fillWidth: true } // spacer

        // Time Date
        TimeChoose {
            Layout.row: 0
            Layout.column: 1

            tcWidth: 193
            tcHeight: 29
        } // Time Date

        // Comp
        CompChoose {
            Layout.row: 0
            Layout.column: 2

            ccWidth: 104
            ccHeight: 29
        }

        // splitter
        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.columnSpan: 3

            Layout.fillWidth: true
            Layout.preferredHeight: 2

            color: "#000000"
        } // splitter

        // text input
        Rectangle { 
            Layout.row: 2
            Layout.column: 0

            Layout.columnSpan: 3

            Layout.fillWidth: true
            Layout.fillHeight: true

            color: "#ffffff"
            radius: 12.5

            // Text holder
            Text { 
                anchors.margins: 10
                anchors.top: parent.top
                anchors.left: parent.left

                text: "..."
                font.bold: true
                font.pixelSize: 12

                color: "#000000"
            } // Text holder

        } // text input
    }
}