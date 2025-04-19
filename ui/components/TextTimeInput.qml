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

    property string ttStatus: cc.ccStatus
    property string ttString: ti.text

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

            Layout.fillWidth: true

            text: "Text"
            font.bold: true
            font.pixelSize: 24

            color: "black"
        } // Header

        // Time Date
        TimeChoose {
            id: tc

            Layout.row: 0
            Layout.column: 1

            anchors.right: cc.left
            anchors.rightMargin: 10

            tcHeight: 29
        } // Time Date

        // Comp
        CompChoose {
            id: cc

            Layout.row: 0
            Layout.column: 2

            anchors.right: parent.right

            ccHeight: 29
        } // Comp

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

            clip: true
            color: "#ffffff"
            radius: 12.5

            // scroll area
            Flickable {
                id: flick

                anchors.fill: parent
                anchors.margins: 10

                contentWidth: width
                contentHeight: ti.implicitHeight

                // scrollbar
                ScrollBar.vertical: ScrollBar {
                    id: scrollBar
                    width: 10
                    policy: ScrollBar.AlwaysOn

                    background: Rectangle {
                        color: "transparent"
                    }

                    contentItem: Rectangle {
                        implicitWidth: 10

                        color: "#D9D9D9" 
                        radius: 5
                        opacity: 0.7

                        states: State {
                            name: "hovered"
                            when: scrollBar.hovered

                            PropertyChanges {
                                target: scrollBar.contentItem
                                opacity: 0.9
                            }
                        }

                        Behavior on opacity { NumberAnimation { duration: 150 } }
                    }
                } // scrollbar

                // input area
                TextArea { 
                    id: ti

                    width: flick.width - scrollBar.width
                    height: Math.max(implicitHeight, flick.height)

                    anchors.rightMargin: 15

                    color: "#484f54"
                    font.bold: true
                    font.pixelSize: 12

                    background: null
                    wrapMode: TextArea.Wrap

                    placeholderText: ". . ."
                    placeholderTextColor: "#484f54"
                } // input area
            } // scroll area
        } // text input
    }
}