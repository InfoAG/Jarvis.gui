// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

    TextInput {
        id: input
        y: 336
        height: button.height
        text: qsTr("text")
        anchors.right: button.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.pixelSize: 12
        Rectangle
        {
            color: "#00000000"
            border.color: "#000000"
            anchors.fill: parent

        }
    }

    Button {
        text: "Send"
        id: button
        x: 667
        y: 366
        width: 90
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        Rectangle
        {
            color: "#00000000"
            border.color: "#000000"
            anchors.fill: parent

        }
    }

    Text {
        id: output
        width: generalRec.width-2*button.width
        text: qsTr("text")
        anchors.left: scopes.right
        anchors.leftMargin: 0
        anchors.bottom: input.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 12
        Rectangle
        {
            color: "#00000000"
            border.color: "#000000"
            anchors.fill: parent

        }
    }

    Text {
        id: scopes
        width: button.width
        text: qsTr("text")
        anchors.bottom: input.top
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 12
        Rectangle
        {
            color: "#00000000"
            border.color: "#000000"
            anchors.fill: parent

        }
    }

    Text {
        id: names
        x: 628
        y: 0
        width: button.width
        text: qsTr("text")
        anchors.left: output.right
        anchors.leftMargin: 0
        anchors.bottom: button.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 12
        Rectangle
        {
            color: "#00000000"
            border.color: "#000000"
            anchors.fill: parent

        }
    }
}
