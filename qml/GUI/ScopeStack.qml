// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property alias userwidth: userlist.width;
    property string name;

    width: 550
    height: 380
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

        Text
        {
            id:outputtext
            anchors.fill: parent
            anchors.margins: 5

        }



        Text
        {
            text: name
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 5
            color: "black"
            Rectangle
            {
                anchors.centerIn: parent
                width: parent.width+10
                height: parent.height+10
                color: "mediumseagreen"
                opacity: 0.1
            }
        }

    }

    Rectangle
    {
        id: userlist
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5

    }








    function writeMsg(scope,sender,msg)
    {
        outputtext.text += sender + ": " + msg + "\n";
    }

    function writeInfo(clients,variables,functions)
    {
        console.log("writeInfo called");
    }







}






















