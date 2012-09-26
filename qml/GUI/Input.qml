import QtQuick 1.0

FocusScope {
    id:container
    height: 32
    BorderImage { source: "../../images/lineedit.sci"; anchors.fill: parent }
    signal accepted
    property alias text: input.text
    property alias item: input


    Flickable
    {
        id: flick
        width:  parent.width - 12;
        height: parent.height - 10;
        contentHeight: input.paintedHeight
        clip: true

        function ensureVisibilty(r)
        {
                 if (contentX >= r.x)
                     contentX = r.x;
                 else if (contentX+width <= r.x+r.width)
                     contentX = r.x+r.width-width;
                 if (contentY >= r.y)
                     contentY = r.y;
                 else if (contentY+height <= r.y+r.height)
                     contentY = r.y+r.height-height;
        }


    TextEdit{
        id: input
        width:  parent.width - 12;
        height: parent.height - 10;
        focus: true

        anchors.centerIn: parent
        font.pixelSize: 16;
        font.bold: true
        color: "#151515"; text: qsTr(""); horizontalAlignment: TextInput.AlignHCenter; selectionColor: "mediumseagreen"
        selectByMouse: true

        wrapMode: TextEdit.Wrap
        onCursorRectangleChanged: flick.ensureVisibilty(cursorRectangle)

        Keys.onPressed: {
            if ((event.key === Qt.Key_Return) && (event.modifiers & Qt.ShiftModifier))
            {
                expandInput();

            }

            else if (event.key === Qt.Key_Return)
            {
                container.accepted();
                input.height = 32
                flick.height = 32
                container.height = 32
                event.accepted = true;
            }

        }

        function expandInput()
        {
            if(flick.height < (generalRec.height/3))
            {
                flick.height += 32;
                container.height += 32;
            }
        }

    }
    }
}
