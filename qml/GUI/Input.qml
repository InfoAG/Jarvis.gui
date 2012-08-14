import QtQuick 1.0

FocusScope {
    id:container
    height: 32
    BorderImage { source: "../../images/lineedit.sci"; anchors.fill: parent }
    signal accepted
    property alias text: input.text
    property alias item: input
    TextInput{
        id: input
        width: parent.width - 12
        height: parent.height-10
        anchors.centerIn: parent
        maximumLength:21
        font.pixelSize: 16;
        font.bold: true
        color: "#151515"; text: qsTr(""); horizontalAlignment: TextInput.AlignHCenter; selectionColor: "mediumseagreen"
        focus: true
        onAccepted:{container.accepted()}
        selectByMouse: true

        Keys.onPressed: {
                 if ((event.key === Qt.Key_Return) && (event.modifiers & Qt.ShiftModifier))
                     expandInput();
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
