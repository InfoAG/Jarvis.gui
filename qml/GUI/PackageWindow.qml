// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle
{
    id: information
    color: "transparent"
    opacity: 0
    border.width: 2
    border.color: "mediumseagreen"
    width: 400
    height: 300
    x: parent.width/2-information.width/2+500
    y: parent.height/2-information.height/2
    z:10

    Rectangle
    {
        id: bg
        color: "#909090"
        opacity: 0.5
        anchors.fill: parent
    }

    Button
    {
        text: "close"
        width: 100; height: 32
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5
        onClicked: generalRec.state = "connected"
    }






    DropDownMenu
    {
        width: 400
        height: 30
    }


}
