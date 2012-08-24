// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item
{
    anchors.fill: parent
    property alias hideBar: scrollbar.hideScrollBarsWhenStopped
    property alias number: listview.count
    property alias currentIndex: listview.currentIndex
    property alias currentItem: listview.currentItem
    property alias model: scopeModel
    signal focusChanged(string name)

    id: parentitem

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
                id: content
                text: name;
            }

            MouseArea
            {
                anchors.fill: parent

                onClicked:
                {
                    listview.currentIndex = index;
                    parentitem.focusChanged(name);
                }
            }
        }
    }

    ListView
    {
        id: listview
        anchors.fill: parent
        model: scopeModel
        delegate: scopeDelegate
        highlight: highrec
        highlightFollowsCurrentItem: false
        focus: true
    }


    ScrollBar
    {
        id: scrollbar
        flickable: listview
        vertical: true
    }


    Component {
              id: highrec
              Rectangle {
                  width: listview.width-9
                  height:15
                  radius: 5
                  color: "mediumseagreen"
                  y: listview.currentItem.y;
                  x: listview.currentItem.x-3;
                  Behavior on y { PropertyAnimation {} }
              }
          }


    function append(name)
    {
        var elements = listview.count

        if(elements == 0)
            scopeModel.append({"name":name});
        else
        {
            for(var i = 0; i < elements; i++)
            {


                if(scopeModel.get(i).name > name)
                {
                    scopeModel.insert(i,{"name":name});
                    break;

                }

                if(i === elements-1)
                {
                    scopeModel.append({"name":name});
                }

            }
        }
    }


}
