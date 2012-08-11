import QtQuick 1.1

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

    Rectangle {
            id: background
            anchors.fill: parent; color: "#343434";

            Image { source: "../../images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }
           }


    Input{
            id: input
           //onAccepted:searchbutton.doSearch();
           focus: true
           x:generalRec.width+500
           y:generalRec.height+500
           visible: false
           anchors.bottomMargin: 5; anchors.leftMargin: 5; anchors.rightMargin: 5
           onAccepted: sendbutton.state = "Entered"
        }

    Button {
        id: sendbutton
        text: "Send"
        visible: false
        x:generalRec.width+500
        y:generalRec.height+500
        //anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 100; height: 32; anchors.bottom: parent.bottom; anchors.bottomMargin: 5
        anchors.rightMargin: 5; width: 100; height: 32; anchors.bottomMargin: 5

    }

    Rectangle
    {
        id: staterec
        x: 0
        y: 0
        anchors.fill: parent
        color: "#909090"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        opacity: 0.5
    }

    Image
    {
        id: quit
        source: "../../images/quit.png"
        visible: false

        x:generalRec.width+500; y:generalRec.height+500
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

        Image
        {
            id: loading
            source: "../../images/loading.png"
            z:101
            visible: false
            anchors.right: login.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.rightMargin: 5
            height: 32
            smooth: false
            opacity: 1
        }

        Text
        {
            id: stext
            x: 0
            y: 5
            text: "Server:"
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: parent.top
            height: 32
            anchors.topMargin: 5
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
            x: 1
            y: 42
            text: "Port:"
            anchors.leftMargin: 1
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: stext.bottom
            height: 32
            anchors.topMargin: 5
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
            x: 0
            y: 79
            text: "Nick:"
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: ptext.bottom
            height: 32
            anchors.topMargin: 5
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
            x: 1
            y: 116
            text: "Password:"
            anchors.leftMargin: 1
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16; font.bold: true; color: "white"; style: Text.Raised; styleColor: "black"
            horizontalAlignment: Qt.AlignCenter
            anchors.left: parent.left
            anchors.top: ntext.bottom
            height: 32
            anchors.topMargin: 5
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
            onClicked: generalRec.state = "connecting"
        }

    }




    states: [
        State {
            name: "connected";
            PropertyChanges { target: staterec; opacity:0}
            PropertyChanges { target: loginwindow; opacity:0}
            AnchorChanges { target: sendbutton; anchors.right: parent.right; anchors.bottom: parent.bottom;}
            AnchorChanges { target: input; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: sendbutton.left;}
            AnchorChanges { target: quit; anchors.top: parent.top; anchors.right: parent.right}
            PropertyChanges { target: input; focus: true; visible: true}
            PropertyChanges{ target: sendbutton; visible: true}
            PropertyChanges { target: quit; visible: true}
        },

        State {

            name: "connecting";
            PropertyChanges{ target: staterec; opacity: 0.500; z:3}
            PropertyChanges{ target: loading; z: 102; visible: true; rotation: 1500}
        }

    ]


    transitions: [
        Transition {
            from: "connecting"; to: "connected"; reversible: true
            NumberAnimation { properties: "visible"; duration: 100}
            ParallelAnimation
            {
                NumberAnimation { properties: "x,y,opacity"; duration: 600; easing.type: Easing.InOutQuad }
                AnchorAnimation { duration: 600; easing.type: Easing.InOutQuad}
            }

        },

        Transition {
            from: ""; to: "connecting";
            ParallelAnimation
            {
                NumberAnimation{properties: "z"; duration: 600}
                NumberAnimation{properties: "visible"; duration: 100}
                RotationAnimation { duration: 500; direction: RotationAnimation.Counterclockwise }
            }

        }
    ]



}

