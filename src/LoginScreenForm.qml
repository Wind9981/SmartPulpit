import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtMultimedia 5.9
import QtQuick.Dialogs 1.1

Item {
    id: item1
    width: 400
    height: 400
    //property alias videoOutput: videoOutput
    property alias item3: item3
    property alias item2: item2
    property alias text1: text1
    property alias animatedImage: animatedImage
    property alias textField: textField
    property alias button: button
    property alias button2: button2
    property alias messageDialog:messageDialog
    property alias image:image

    // Camera {
    //     id: camera

    //     imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

    //     exposure {
    //         exposureCompensation: -1.0
    //         exposureMode: Camera.ExposurePortrait
    //     }

    //     viewfinder.resolution: "640x480"

    //     flash.mode: Camera.FlashRedEyeReduction

    //     imageCapture {
    //         onImageCaptured: {
    //             photoPreview.source = preview // Show the preview in an Image
    //         }
    //     }
    // }

    Text {
        id: text1
        x: 189
        y: 72
        visible: false
        text: qsTr("")
        font.pixelSize: 12
    }
    

    // Text {
    //     anchors.verticalCenter: parent.verticalCenter
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     visible: true
    //     text: qsTr("Welcome Teacher")
    //     font.pixelSize: 30
    // }

    Item {
        id: item2
        x: 200
        y: 81
        width: item1.width / 2
        height: item1.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0

        TextField {
            id: textField
            x: 226
            y: 22
            width: 354
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenterOffset: 0
            placeholderText: qsTr("Username")
            anchors.verticalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: textField2
            x: 226
            y: 62
            width: 354
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenterOffset: 0
            placeholderText: qsTr("Password")
            anchors.verticalCenterOffset: -27
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button2
            x: 224
            y: 84
            width: 354
            height: 40
            text: qsTr("Login with password")
            anchors.verticalCenter: parent.verticalCenter
            property string property0: "none.none"
            anchors.verticalCenterOffset: 19
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button
            x: 224
            y: 106
            width: 354
            height: 40
            text: qsTr("Login with faceid")
            anchors.verticalCenter: parent.verticalCenter
            property string property0: "none.none"
            anchors.verticalCenterOffset: 61
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

        AnimatedImage {
            id: animatedImage
            x: 338
            y: 109
            width: 125
            height: 125
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Loading.gif"
            anchors.horizontalCenterOffset: 400
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: 86
        }
    }

    MessageDialog {
        id: messageDialog
        icon: StandardIcon.Question
        standardButtons: StandardButton.Yes | StandardButton.No
    }

    Item {
        id: item3
        y: 100
        width: item1.width / 2
        height: item1.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.verticalCenterOffset: 0
        anchors.leftMargin: 0

        // VideoOutput {
        //     id: videoOutput
        //     width: 100
        //     height: 100
        //     anchors.fill: parent
        //     source: camera
        //     focus: visible // to receive focus and capture key events when visible
        // }
        Image{
            id: image
            width: 500
            height: 500
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            visible: true
            source: "qrc:/Images/noimage.png"
            focus: visible // to receive focus and capture key events when visible

        }
    }
}
