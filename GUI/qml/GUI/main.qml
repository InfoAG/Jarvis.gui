// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: generalRec
    width: 700
    height: 400
    radius: 0

   Rectangle {
       id: background
       anchors.fill: parent; color: "#343434";

       state:"searchquery"
       Image { source: "../../images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }
   }









   Input{
       id: input
       //onAccepted:searchbutton.doSearch();
       focus: true
       anchors.bottom: parent.bottom; anchors.bottomMargin: 5; anchors.left: parent.left; anchors.leftMargin: 5; anchors.right: sendbutton.left; anchors.rightMargin: 5
   }

    Button {
        id: sendbutton
        text: "Send"
        anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 100; height: 32; anchors.bottom: parent.bottom; anchors.bottomMargin: 5
    }


}
