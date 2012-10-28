import QtQuick 1.1
import QMLJarvisClient 0.1
import "../../map.js" as StackMap

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

    Rectangle
    {
        id: header
        height: 30
        anchors.left:  parent.left
        anchors.right: parent.right
        anchors.margins: 5
        color: "transparent"
        z:4

        MouseArea
        {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: quit.left
            width:30
            z:5

            Rectangle
            {
                z:4
                anchors.fill: parent
                color:"grey"

            }

            onClicked:
            {
                console.log("current state is:" + generalRec.state)
                generalRec.state = "showInformation"
                console.log("current state is:" + generalRec.state)
            }
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
                onClicked:
                {

                    for(var i in StackMap.map)
                    {
                        StackMap.map[i].destroy();
                    }
                    client.disconnect();
                    generalRec.state = "connecting";
                    generalRec.state = "";
                }
            }
        }

    }



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
            id: informationbg
            color: "#909090"
            opacity: 0
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

    }

    //Object of JarvisClient
    QMLJarvisClient
    {
        id: client
        onReceivedInitInfoQML: {
            generalRec.state = "connected";
            for(var i in pkgs)
            {

                for(var j = 0; j < pkgs[i].operators.length; j++)
                {
                    console.log(pkgs[i].operators[j].name);
                    //operators.append(pkgs[i].operators[j].name)
                }

//                for(var j = 0; j < pkgs[i].terminals.length; j++)
//                {
//                    console.log(pkgs[i].terminals[j].name);
//                }

                for(var j = 0; j < pkgs[i].functions.length; j++)
                {
                    console.log(pkgs[i].functions[j].name);
                }


            }
            //terminals.append()

        }
        onEnteredRoomQML:
        {
            //create objects of RoomStack, append items to ListItem
            listitem.append(name);

            var roomname = name;
            var component = Qt.createComponent("RoomStack.qml");
            var stack


            if(listitem.number == 1)
            {
                stack = component.createObject(dynamicRec, {"name":roomname, "anchors.fill": dynamicRec, "userwidth": generalRec.width/6, "visible": true});
                StackMap.map[roomname] = stack;
                StackMap.lastFocusedObject = stack;

            }

            else
            {
                stack = component.createObject(dynamicRec, {"name":roomname, "anchors.fill": dynamicRec, "userwidth": generalRec.width/6, "visible": false});
                StackMap.map[roomname] = stack;
            }



            if (component.status == Component.Error) {
                     console.log("Error loading component:", component.errorString());
            }


            stack.writeInfo(info);

        }

        onNewClient:
        {
            var roomname = room;
            var component = StackMap.map[roomname];
            component.addUser(nick)

        }

        onClientLeft:
        {
            var roomname = room;
            var component = StackMap.map[roomname];
            component.removeUser(nick)
        }

        onMsgInRoom:
        {
            var roomname = room;
            var component = StackMap.map[roomname];
            component.writeMsg(room,sender,msg);

        }


        onNewFunction:
        {
            var roomname = room;
            var component = StackMap.map[roomname];
            console.log(arguments.length);
            component.addFunction(identifier,arguments,def);

            //void newFunction(const QString &room, const QString &identifier, const QStringList &arguments, const QString &def);

        }

        onNewVariable:
        {
            var roomname = room;
            var component = StackMap.map[roomname];
            component.addVariable(identifier,definition)
        }

        onError:
        {
            console.log("error");
        }



    }


    Rectangle
    {
        id: dynamicRec
        anchors.margins: 5
        anchors.right: parent.right
        anchors.left: roomrec.right
        anchors.top: header.bottom
        anchors.bottom: input.top
        color: "transparent"
        visible: true
        z:1

    }

    //Backgroundimage
    Rectangle {
            id: background
            anchors.fill: parent; color: "#343434";

            Image { source: "../../images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }
           }

    //first Rectangle = rooms, second = Userlist
    Rectangle
    {
        id: roomrec
        width: generalRec.width/6
        visible: false
        anchors.margins: 5
        anchors.bottom: input.top
        anchors.top: header.bottom
        anchors.left: parent.left
        color: "white"
        border.width: 2
        border.color: "mediumseagreen"

        ListItem
        {
            id: listitem
            anchors.margins: 5
            anchors.fill: parent
            onFocusChanged:
            {
                var roomname = name;
                var component = StackMap.map[roomname];
                StackMap.lastFocusedObject.visible = false;
                component.visible = true;
                StackMap.lastFocusedObject = component;

            }

            onItemDeleted:
            {
                var roomname = name;
                var component = StackMap.map[roomname];
                component.destroy();
                client.leaveRoom(name)
            }
        }

        TextInput
        {
            id: nstext
            y: 5+listitem.number*15
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height:15
            text: "new room"

//            MouseArea
//            {
//                preventStealing: true
//                anchors.fill: parent
//                onClicked:
//                {
//                    nstext.selectAll();
//                }
//            }

            onAccepted:
            {
                client.enterRoom(text)
                text = "new room"
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

            var room = StackMap.lastFocusedObject.name;
            client.msgToRoom(room,text);
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


    Rectangle {
        color: "transparent"
        width: 300
        height: 190
        anchors.centerIn: parent
        id: loginwindow
        z:2

        Loading
        {
            id: loading
            z:3
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
            anchors.leftMargin: 1
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
            text:"176.198.129.70";
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
            text: "Nick";
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
            PropertyChanges { target: roomrec; visible: true}
        },

        State {
            name: "connecting";
            PropertyChanges{ target: staterec; opacity: 0.500; z:3}
            PropertyChanges{ target: loading; visible: true;}
            PropertyChanges{target: server.item; readOnly: true}
            PropertyChanges{target: port.item; readOnly: true}
            PropertyChanges{target: nick.item; readOnly: true}
            PropertyChanges{target: pwd.item; readOnly: true}
        },

        State {
            name: "disconnected";
            PropertyChanges{}


        },

        State {
            name: "showInformation";
            PropertyChanges{ target: information; opacity: 1; x: parent.width/2-information.width/2; y: parent.height/2-information.height/2}
            PropertyChanges{ target: informationbg; opacity:0.5}
            PropertyChanges { target: staterec; opacity:0}
            PropertyChanges { target: loginwindow; opacity:0}
            AnchorChanges { target: sendbutton; anchors.right: parent.right; anchors.bottom: parent.bottom;}
            AnchorChanges { target: input; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: sendbutton.left;}
            AnchorChanges { target: quit; anchors.top: parent.top; anchors.right: parent.right}
            PropertyChanges { target: input; focus: true; visible: true}
            PropertyChanges{ target: sendbutton; visible: true}
            PropertyChanges { target: quit; visible: true}
            PropertyChanges { target: roomrec; visible: true}
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
        },

        Transition {
            from: "connected"; to: "showInformation"; reversible: true
            ParallelAnimation
            {
                NumberAnimation{properties: "x,y,opacity"; duration: 300}

            }
        }
    ]


}

