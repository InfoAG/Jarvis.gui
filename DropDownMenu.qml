import QtQuick 1.1

Rectangle {
    width:400;
    height: 400;

    Rectangle {
            id:comboBox
            property variant items: ["Item 1", "Item 2", "Item 3", "Item 4", "Item 5"]
            property string header: "header"
            signal comboClicked;
            width: 100;
            height: 30;
            z: 100;
            smooth:true;

            Rectangle {
                id:chosenItem
                radius:4;
                width:parent.width;
                height:comboBox.height;
                color: "lightsteelblue"
                smooth:true;
                Image
                {
                    id: triangle
                    smooth: true
                    source: "triangle.png"
                    fillMode: Image.PreserveAspectFit
                    height: comboBox.height-10
                    width: height
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter

                    Behavior on rotation
                    {
                        PropertyAnimation{duration: 500}
                    }

                    MouseArea
                    {
                        anchors.fill: parent;
                        onClicked: {
                            comboBox.state = comboBox.state==="dropDown"?"":"dropDown"
                            if(comboBox.state == "dropDown")
                            {
                                triangle.rotation = 90;
                            }
                            else
                            {
                                triangle.rotation = 0;
                            }
                        }
                    }

                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: triangle.right
                    anchors.leftMargin: 6
                    id:chosenItemText
                    text: comboBox.header
                    font.family: "Arial"
                    font.pointSize: 14;
                    smooth:true
                }

            }

            Rectangle {
                id:dropDown
                width:comboBox.width;
                height:0;
                clip:true;
                radius:4;
                anchors.top: chosenItem.bottom;
                anchors.margins: 2;
                color: "lightgray"

                ListView {
                    id:listView
                    height:500;
                    model: comboBox.items
                    currentIndex: 0
                    delegate: Item{
                        width:comboBox.width;
                        height: comboBox.height;

                        Text {
                            text: modelData
                            anchors.top: parent.top;
                            anchors.left: parent.left;
                            anchors.margins: 5;

                        }
                    }
                }
            }

            Component {
                id: highlight
                Rectangle {
                    width:comboBox.width;
                    height:comboBox.height;
                    color: "red";
                    radius: 4
                }
            }

            states: State {
                name: "dropDown";
                PropertyChanges { target: dropDown; height:40*comboBox.items.length }
            }

            transitions: Transition {
                NumberAnimation { target: dropDown; properties: "height"; easing.type: Easing.OutExpo; duration: 1000 }
            }
        }
    }
