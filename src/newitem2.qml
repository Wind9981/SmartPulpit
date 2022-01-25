import QtQuick 2.0

Rectangle {
    property var name
    border.color: "black"
    border.width: 5
    width: 300; height: 50
    Text {
        id: text
        anchors.centerIn: parent
        font.pointSize: 12; text: name
    }
    MouseArea {
        anchors.fill: parent
        onClicked: function(){
            _present.operate(name)
        }
    }
}
