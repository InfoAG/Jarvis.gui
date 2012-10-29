// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property alias userwidth: userlist.width;
    property string name;

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
        height:parent.height/3
        anchors.right: parent.right
        anchors.margins: 5



        UserListItem
        {
            id: users
            anchors.margins: 5
            anchors.fill: parent
        }

    }


    Rectangle
    {
        id:variables
        anchors.top: userlist.bottom
        height:parent.height/3-10
        anchors.right: parent.right
        anchors.left: output.right
        anchors.margins: 5

        UserListItem
        {
            id: vars
            anchors.margins: 5
            anchors.fill: parent

        }
    }


    Rectangle
    {
        id:functions
        anchors.top: variables.bottom
        height:parent.height/3-10
        anchors.right: parent.right
        anchors.left: output.right
        anchors.margins: 5

        UserListItem
        {
            id:func
            anchors.margins: 5
            anchors.fill: parent

        }

    }




    function writeMsg(scope,sender,msg)
    {
        outputtext.text += sender + ": " + msg + "\n";
    }

    function writeInfo(info)
    {
        //1. user
        for(var i in info.clients)
        {
            users.append(info.clients[i]);
        }

        //2.variables
        for(var i = 0; i < info.variables.length; i++)
        {
            vars.append(info.variables[i].identifier + "=" + info.variables[i].definition);

            //vars.append(key + "=" +  info.variables[key])
        }

        //3.funcions
        for(var i = 0; i < info.functions.length; i++)
        {
            var string = info.functions[i].identifier + "(";

            for(var j = 0; j < info.functions[i].arguments.length; j++)
            {
                string += info.functions[i].arguments[j];
                if(j != info.functions[i].arguments.length-1)
                    string += ",";
            }

            string += ")=" + info.functions[i].definition;
            func.append(string);

        }

    }

    function addUser(user)
    {
        users.append(user);
    }

    function removeUser(user)
    {
        users.remove(user);
    }

    function addVariableDef(id,def)
    {
        for(var i = 0; i < vars.number; i++)
        {

            var tempstring = vars.model.get(i).name
            if(tempstring.indexOf("=") !== -1)
            {
                tempstring = tempstring.substring(0,tempstring.indexOf("="));
                if(id == tempstring)
                {
                    vars.removeWithIndex(i);

                }
            }

            else
            {
                tempstring = tempstring.substring(0,tempstring.indexOf("("));
                if(id == tempstring)
                {
                    vars.removeWithIndex(i);

                }
            }

        }
        vars.append(id + "=" + def);
    }

    function addVariableDec(id,type)
    {
        vars.append(id + "(" + type + ")");
    }


    function addFunction(id,args,def)
    {
        var string = id + "(";

        for(var i = 0; i < args.length; i++)
        {
            string += args[i];
            if(i != args.length-1)
                string += ",";
        }

        string += ")=" + def;
        func.append(string);

    }







}






















