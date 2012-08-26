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
    signal itemDeleted(string name)

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
                z:10
                anchors.fill: parent
                id: content
                text: name;
            }

            Rectangle
            {
                z:9
                id:hoverrec
                width: listview.width-9
                height:15
                x:-3
                radius: 5
                color: "#9BED00"
                opacity:0
                Behavior on opacity{ PropertyAnimation{duration: 500}}

                Image
                {
                    source: "../../images/close.png";
                    z:10
                    anchors.right: parent.right
                    height: hoverrec.height
                    width: hoverrec.height

                    Rectangle
                    {
                        z:11
                        id:imagerec
                        anchors.fill: parent
                        color: "black"
                        opacity:0
                    }

                    MouseArea
                    {
                        anchors.fill: parent

                        onClicked:
                        {
                            imagerec.opacity = 0.5;
                            parentitem.itemDeleted(content.text);
                            scopeModel.remove(index);
                        }

                    }

                }
            }

            MouseArea
            {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                hoverEnabled: true

                onClicked:
                {
                        listview.currentIndex = index;
                        parentitem.focusChanged(name);
                }

                onEntered:
                {
                    hoverrec.opacity = 1;
                }

                onExited:
                {
                    hoverrec.opacity = 0;
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
        z:5
        id: scrollbar
        flickable: listview
        vertical: true
    }


    Component {
              id: highrec
              Rectangle {
                  id:iamarec
                  width: listview.width-9
                  height:15
                  radius: 5
                  color: "mediumseagreen"
                  y: y = listview.currentItem.y;
                  x: x = listview.currentItem.x-3;
                  Behavior on y { PropertyAnimation {} }
              }
          }


    function append(name)
    {
        var elements = listview.count

        if(elements == 0)
        {
            scopeModel.append({"name":name});
        }
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
