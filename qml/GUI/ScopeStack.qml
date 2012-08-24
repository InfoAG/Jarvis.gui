// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property alias userwidth: userlist.width;
    property string name;

    //width: 550
    //height: 380
    id: container
    color: "transparent"
    border.width: 2
    border.color: "mediumseagreen"

    Rectangle
    {
        id: output
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        anchors.right: userlist.left
    }

    Rectangle
    {
        id: userlist
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5
    }
}
