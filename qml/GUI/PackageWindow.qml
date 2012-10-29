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
        id: close_button
        text: "close"
        width: 100; height: 32
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5
        onClicked: generalRec.state = "connected"
    }





    Flickable
    {
        id: flick
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height-close_button.height
        flickableDirection: Flickable.VerticalFlick
        contentHeight: flickRec.height
        clip: true

        Rectangle
        {
            id: firstrec
            width: parent.width
            height: 30
            DropDownMenu
            {
                header: "Binary Operators (0)"
                id: binop
                width: parent.width
                height: 30

                onExtendedBox: {
                    parent.height += binop.count*30
                    flickRec.height += binop.count*30
                }

                onRetractedBox: {
                    parent.height -= binop.count*30
                    flickRec.height -= binop.count*30
                }
            }
        }



        Rectangle
        {
            id: secondrec
            width: parent.width
            height: 30
            anchors.top: firstrec.bottom
            DropDownMenu
            {
                header: "Unary Operators (0)"
                id: unop
                width: parent.width
                height: 30

                onExtendedBox: {
                    parent.height += unop.count*30
                    flickRec.height += unop.count*30
                }

                onRetractedBox: {
                    parent.height -= unop.count*30
                    flickRec.height -= unop.count*30
                }
            }
        }



        Rectangle
        {
            id: thirdrec
            width: parent.width
            height: 30
            anchors.top: secondrec.bottom
            DropDownMenu
            {
                header: "Terminals (0)"
                id: term
                width: parent.width
                height: 30

                onExtendedBox: {
                    parent.height += term.count*30
                    flickRec.height += term.count*30
                }

                onRetractedBox: {
                    parent.height -= term.count*30
                    flickRec.height -= term.count*30
                }
            }
        }

        Rectangle
        {
            id: fourthrec
            width: parent.width
            height: 30
            anchors.top: thirdrec.bottom
            DropDownMenu
            {
                header: "Functions (0)"
                id: func
                width: parent.width
                height: 30

                onExtendedBox: {
                    parent.height += func.count*30
                    flickRec.height += func.count*30
                }

                onRetractedBox: {
                    parent.height -= func.count*30
                    flickRec.height -= func.count*30
                }
            }
        }


        Rectangle
        {
            id: flickRec
            anchors.top: parent.top
            width: parent.width
            height: 4*30
            visible: false
        }

    }


    function addBinOps(op)
    {
        binop.model.append({"modelText":op});

        var string = binop.header
        string = string.substring(0,string.indexOf("("));
        binop.header = string + "(" + binop.count + ")"
    }


    function addUnOps(op)
    {
        unop.model.append({"modelText":op});

        var string = unop.header
        string = string.substring(0,string.indexOf("("));
        unop.header = string + "(" + unop.count + ")"

    }

    function addTerminals(op)
    {
        term.model.append({"modelText":op});

        var string = term.header
        string = string.substring(0,string.indexOf("("));
        term.header = string + "(" + term.count + ")"

    }

    function addFunctions(op)
    {
        func.model.append({"modelText":op});

        var string = func.header
        string = string.substring(0,string.indexOf("("));
        func.header = string + "(" + func.count + ")"
    }



























}
