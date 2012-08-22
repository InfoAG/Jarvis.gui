// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item
{
    anchors.fill: parent
    property alias model: scopeModel
    property alias number: listview.count
    property alias hideBar: scrollbar.hideScrollBarsWhenStopped

    ListModel
    {
        id: scopeModel
    }

    Component
    {
        id: scopeDelegate

        Item
        {
            anchors.margins: 5
            anchors.right: parent.right
            anchors.left: parent.left
            height:15

            Text
            {
                text: name;
            }
        }
    }

    ListView
    {
        id: listview
        anchors.fill: parent
        model: scopeModel
        delegate: scopeDelegate
        highlight: Rectangle { id: highlightrec; color: "mediumseagreen"; radius: 5 }
        focus: true
    }


    ScrollBar
    {
        id: scrollbar
        flickable: listview
        vertical: true
    }


}
