import QtQuick 1.0

FocusScope {
    id:container
    height: 32
    BorderImage { source: "../../images/lineedit.sci"; anchors.fill: parent }
    signal accepted
    property alias text: input.text
    property alias item: input


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

        Keys.onPressed: {
            if ((event.key === Qt.Key_Return) && (event.modifiers & Qt.ShiftModifier))
            {
                expandInput();

            }

            else if (event.key === Qt.Key_Return)
            {
                container.accepted();
                input.height = 32
                event.accepted = true;
            }

        }

        function expandInput()
        {
            if(input.height < (generalRec.height/3))
            {
                input.height += 32;
                container.height += 32;
            }
        }

    }
}
