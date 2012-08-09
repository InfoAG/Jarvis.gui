// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: generalRec
    width: 700
    height: 400
    color: "#ffffff"
    radius: 0

    Rectangle {
        id: rectangle1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 0.340
                color: "#4de423"
            }

            GradientStop {
                position: 0.750
                color: "#4de423"
            }

            GradientStop {
                position: 1
                color: "#ffffff"
            }
        }
        anchors.right: parent.right
        anchors.rightMargin: 155
        anchors.left: parent.left
        anchors.leftMargin: 155
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 100

        Button {
            text: "Login"
            id: button1
            x: 0
            y: 200
            width: rectangle1.width
            height: 27
        }
    }

    Grid {
        id: grid1
        x: 241
        y: 136
        width: 219
        height: 128

        Text {
            id: texthost
            color: "#FFFFFF"
            text: qsTr("Server:")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            verticalAlignment: Text.AlignTop
            font.bold: true
            style: Text.Normal
            font.pixelSize: 15
            height: grid1.height/4
            width: grid1.width/2
        }

        TextInput {
            id: host
            horizontalAlignment: TextInput.AlignHCenter
            anchors.left: texthost.right
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            font.bold: true
            z: 2
            font.pixelSize: 15
            height: grid1.height/4
            color: "#FFFFFF"
            text: "Server"
            width: grid1.width/2
        }

        Text {
            id: textport
            color: "#FFFFFF"
            text: qsTr("Port: ")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: texthost.bottom
            anchors.topMargin: 0
            verticalAlignment: Text.AlignTop
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            width: grid1.width/2
        }

        TextInput {
            id: port
            text: qsTr("Port")
            horizontalAlignment: TextInput.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: host.bottom
            anchors.topMargin: 0
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            color: "#ffffff"
            width: grid1.width/2
        }

        Text {
            id: textnick
            color: "#FFFFFF"
            text: qsTr("Nick: ")
            anchors.top: textport.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignTop
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            width: grid1.width/2
        }

        TextInput {
            id: nick
            text: qsTr("Derp")
            opacity: 1
            horizontalAlignment: TextInput.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: port.bottom
            anchors.topMargin: 0
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            color: "#ffffff"
            width: grid1.width/2
        }

        Text {
            id: textpdw
            color: "#FFFFFF"
            text: qsTr("Password: ")
            anchors.top: textnick.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignTop
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            width: grid1.width/2
        }

        TextInput {
            id: password
            text: qsTr("supersecret")
            horizontalAlignment: TextInput.AlignHCenter
            echoMode: TextInput.Normal
            readOnly: true
            anchors.top: nick.bottom
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.bold: true
            font.pixelSize: 15
            height: grid1.height/4
            color: "#ffffff"
            width: grid1.width/2
        }

    }
}


//server port nick passwd
