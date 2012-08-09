// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

    Rectangle {
            id: background
            anchors.fill: parent; color: "#343434";

            Image { source: "/Users/Lars/Documents/Jarvis/GUI/images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }
           }


    Input{
            id: input
           //onAccepted:searchbutton.doSearch();
           focus: true
           x:500
           y:500
           anchors.bottomMargin: 5; anchors.leftMargin: 5; anchors.rightMargin: 5
           onAccepted: sendbutton.state = "Entered"
        }

    Button {
        id: sendbutton
        text: "Send"
        x:500
        y:500
        //anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 100; height: 32; anchors.bottom: parent.bottom; anchors.bottomMargin: 5
        anchors.rightMargin: 5; width: 100; height: 32; anchors.bottomMargin: 5

    }

    Rectangle
    {
        id: staterec
        anchors.fill: parent
        color: "#909090"
        opacity: 0.5
    }

    Image
    {
        id: quit
        source: "/Users/Lars/Documents/Jarvis/GUI/images/quit.png"

        x:500; y:500
        MouseArea
        {
            anchors.fill: parent
            onClicked: generalRec.state = ""
        }
    }


    Rectangle {
        color: "transparent"
        width: 300
        height: 190
        anchors.centerIn: parent
        id: loginwindow

        Text
        {
            id: stext
            text: "Server:"
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: parent.top
            height: 32
            anchors.topMargin: 7
        }
        Input
        {
            width: parent.width-pwtext.width-20
            id: server
            focus: true
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
        }

        Text
        {
            id: ptext
            text: "Port:"
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: stext.bottom
            height: 32
            anchors.topMargin: 7
        }
        Input
        {
            id: port
            width: parent.width-pwtext.width-20
            anchors.right: parent.right
            anchors.top: server.bottom
            anchors.topMargin: 5
        }

        Text
        {
            id: ntext
            text: "Nick:"
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: ptext.bottom
            height: 32
            anchors.topMargin: 6
        }
        Input
        {
            id: nick
            width: parent.width-pwtext.width-20
            anchors.right: parent.right
            anchors.top: port.bottom
            anchors.topMargin: 5
        }

        Text
        {
            id: pwtext
            text: "Password:"
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: ntext.bottom
            height: 32
            anchors.topMargin: 6
        }
        Input
        {
            id: pwd
            width: parent.width-pwtext.width-20
            anchors.right: parent.right
            anchors.top: nick.bottom
            anchors.topMargin: 5
        }

        Button
        {
            id: login
            text: "Login"
            anchors.right: parent.right; width: 100; height: 32; anchors.bottom: parent.bottom; anchors.bottomMargin: 5
            onClicked: generalRec.state = "login"
        }

    }




    states: [
        State {
            name: "login";
            PropertyChanges { target: staterec; opacity:0}
            PropertyChanges { target: loginwindow; opacity:0}
            AnchorChanges { target: sendbutton; anchors.right: parent.right; anchors.bottom: parent.bottom;}
            AnchorChanges { target: input; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: sendbutton.left;}
            AnchorChanges { target: quit; anchors.top: parent.top; anchors.right: parent.right}
        }
    ]


    transitions: [
        Transition {
            from: ""; to: "login"; reversible: true
            NumberAnimation { properties: "x,y,opacity"; duration: 600; easing.type: Easing.InOutQuad }
            AnchorAnimation { duration: 600; easing.type: Easing.InOutQuad}
        }
    ]



}

