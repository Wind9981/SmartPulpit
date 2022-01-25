import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtWebView 1.1
import QtWebEngine 1.0



Page {
    id: page
    property alias column: column
    property alias column2: column2
    property alias button1: button1
    property alias online: online
    property alias offline: offline
    property alias total: total
    property alias text2: text2


    Text {
        id: text2
        x: 189
        y: 72
        visible: false
        text: qsTr("")
        font.pixelSize: 12
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        
        Pane {
            width: swipeView.width
            height: swipeView.height

            ScrollView {
                contentWidth: -1
                anchors.fill: parent
                anchors.bottomMargin: 46
                ScrollBar.horizontal.interactive: true
                ScrollBar.vertical.interactive: false
                Column {
                    id: column2
                    anchors.fill: parent
                    spacing: 10
                }
            }

            // Button {
            //     id: button2
            //     x: 258
            //     text: qsTr("Trình chiếu")
            //     anchors.top: column.bottom
            //     anchors.bottom: parent.bottom
            //     anchors.bottomMargin: 0
            //     anchors.topMargin: 6
            //     anchors.horizontalCenter: parent.horizontalCenter
            // }

            
        }

        Pane {
            width: swipeView.width
            height: swipeView.height

            Text {
                id: button1
                x: 258
                text: qsTr("Điểm danh tự động")
                font.bold: true
                font.pointSize: 20
                anchors.top: column.bottom
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: 6
                anchors.horizontalCenter: parent.horizontalCenter
            }
            ScrollView {
                contentWidth: -1
                anchors.fill: parent
                anchors.bottomMargin: 46
                anchors.rightMargin: 300
                ScrollBar.horizontal.interactive: true
                ScrollBar.vertical.interactive: false
                Column {
                    id: column
                    anchors.fill: parent
                    spacing: 10
                }
            }
            
            Rectangle {
                anchors.leftMargin: 800
                anchors.fill: parent
                anchors.bottomMargin: 46
                border.color: "black"
                border.width: 5
                visible: true
                Text {
                    y: 17
                    visible: true
                    text: "Report"
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 20
                    
                }
                Text {
                    id: total
                    y: 50
                    visible: true
                    text: "Total students: "          
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 18
                    
                }
                Text {
                    id: online
                    y: 80
                    visible: true
                    text: "Attendance: "          
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 18
                    
                }
                Text {
                    id: offline
                    y: 110
                    visible: true
                    text: "Absent: "       
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 18    
                }
            }
            
        }
        Pane {
            width: swipeView.width
            height: swipeView.height
            
            WebEngineView{
                url: "http://47.241.108.186:1880/ui"
                anchors.fill: parent      
                visible: true       
            }
        }
        Pane {
            width: swipeView.width
            height: swipeView.height

            WebEngineView{
                url: "http://192.168.1.102/index.php"
                anchors.fill: parent      
                visible: true       
            }
        }
    }

    footer: TabBar {
        id: tabBar
        font.bold: true
        font.pointSize: 15
        currentIndex: swipeView.currentIndex

        TabButton {
            text: "Bài giảng"
        }
        TabButton {
            text: "Điểm danh"
        }
        TabButton {
            text: "Điều khiển"
        }
        TabButton {
            text: "Kiểm tra"
        }
    }
}
