import QtQuick 2.0

Rectangle {
    property var studentid
    property var myColor
    property var url
    width: 200; height: 250
    
    Image{
        id: images
        visible: true
        width: 200
        height: 200                                                                                                                                                                                                            
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        source: url
        Rectangle{
            id: background
            color: myColor
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            width: 200; height: 50
            Text {
                id: text
                anchors.centerIn: parent
                font.pointSize: 24; text: studentid
            }
        }
    }
}
