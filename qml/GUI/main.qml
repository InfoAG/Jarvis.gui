import QtQuick 1.1
import QMLJarvisClient 0.1
import "../../map.js" as StackMap

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

    //Object of JarvisClient
    QMLJarvisClient
    {
        id: client
        onReceivedInitInfoQML: {
            generalRec.state = "connected"
            console.log(pkgs[0].operators[0].name);
        }
        onEnteredScopeQML:
        {
            //create objects of ScopeStack, append items to ListItem
            listitem.append(name);

            var scopename = name;
            var component = Qt.createComponent("ScopeStack.qml");
            var stack


            if(listitem.number == 1)
            {
                stack = component.createObject(generalRec, {"name":scopename, "anchors.margins": 5, "anchors.right": generalRec.right, "anchors.left": scoperec.right, "anchors.top": generalRec.top, "anchors.bottom": input.top, "userwidth": generalRec.width/6, "visible": true});
                StackMap.map[scopename] = stack;
                StackMap.lastFocusedObject = stack;

            }

            else
            {
                stack = component.createObject(generalRec, {"name":scopename, "anchors.margins": 5, "anchors.right": generalRec.right, "anchors.left": scoperec.right, "anchors.top": generalRec.top, "anchors.bottom": input.top, "userwidth": generalRec.width/6, "visible": false});
                StackMap.map[scopename] = stack;
            }



            if (component.status == Component.Error) {
                     console.log("Error loading component:", component.errorString());
            }


            //pass scopeinfos to new object using writeInfo()








        }

        onMsgInScope:
        {
            var scopename = scope;
            var component = StackMap.map[scopename];
            component.writeMsg(scope,sender,msg);

        }

        onError:
        {
            console.log("error");
        }

    }

    //Backgroundimage
    Rectangle {
            id: background
            anchors.fill: parent; color: "#343434";

            Image { source: "../../images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }
           }

    //first Rectangle = Scopes, second = Userlist
    Rectangle
    {
        id: scoperec
        width: generalRec.width/6
        visible: false
        anchors.margins: 5
        anchors.bottom: input.top
        anchors.top: parent.top
        anchors.left: parent.left
        color: "white"
        border.width: 2
        border.color: "mediumseagreen"

        ListItem
        {
            id: listitem
            anchors.margins: 5
            anchors.fill: parent
            hideBar: false
            onFocusChanged:
            {
                var scopename = name;
                var component = StackMap.map[scopename];
                StackMap.lastFocusedObject.visible = false;
                component.visible = true;
                StackMap.lastFocusedObject = component;

            }
        }

//        Rectangle
//        {}

        TextInput
        {
            id: nstext
            y: 5+listitem.number*15
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height:15
            text: "new Scope"


            onAccepted:
            {
                client.enterScope(text)
                text = "new Scope"
            }
        }
    }





    Input
    {
        id: input
        focus: true
        x:generalRec.width+500
        y:generalRec.height+500
        visible: false
        item.horizontalAlignment: Qt.AlignLeft
        anchors.bottomMargin: 5; anchors.leftMargin: 5; anchors.rightMargin: 5
        onAccepted:
        {
            sendbutton.state = "Pressed";
            sendbutton.state="";

            var scope = StackMap.lastFocusedObject.name;
            client.msgToScope(scope,text);
            input.text = "";
        }

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
        z:5
        source: "../../images/quit.png"
        visible: false
        width: 30
        height: 30
        x:generalRec.width+500; y:generalRec.height+500
        MouseArea
        {
            anchors.fill: parent
            onClicked: {generalRec.state = "connecting";generalRec.state = "";client.disconnect();}
        }
    }


    Rectangle {
        color: "transparent"
        width: 300
        height: 190
        anchors.centerIn: parent
        id: loginwindow

        Loading
        {
            id: loading
            z:101
            visible: false
            anchors.right: login.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.rightMargin: 5
            height: 32
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
            text:"localhost";
            KeyNavigation.tab: port;
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
            text: "4200";
            KeyNavigation.tab: nick
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
            text: "Herp";
            KeyNavigation.tab: pwd
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
            text: "";
            item.readOnly: false
            KeyNavigation.tab: login
        }

        Button
        {
            id: login
            text: "Login"
            anchors.right: parent.right; width: 100; height: 32; anchors.bottom: parent.bottom; anchors.bottomMargin: 5
            onClicked: {generalRec.state = "connecting"; client.connect(server.text,port.text,nick.text,pwd.text)}
            Keys.onEnterPressed: {generalRec.state = "connecting"; client.connect(server.text,port.text,nick.text,pwd.text)}
            KeyNavigation.tab: server
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
            PropertyChanges { target: scoperec; visible: true}
        },

        State {

            name: "connecting";
            PropertyChanges{ target: staterec; opacity: 0.500; z:3}
            PropertyChanges{ target: loading; visible: true;}
            PropertyChanges{target: server.item; readOnly: true}
            PropertyChanges{target: port.item; readOnly: true}
            PropertyChanges{target: nick.item; readOnly: true}
            PropertyChanges{target: pwd.item; readOnly: true}
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
            from: ""; to: "connecting"; reversible: true
            ParallelAnimation
            {
                NumberAnimation{properties:"visible";duration:100}
                NumberAnimation{properties:"opacity";duration:600}

            }
        }
    ]


}

