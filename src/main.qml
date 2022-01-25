import QtQuick 2.4
import QtQml 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.2


Window {
    property var teacherid
    property var classinfo
    id: mainwindow
    width: 640
    height: 480
    visible: true
    visibility: "FullScreen"
    title: qsTr("Hello World")
    StackView{
        id: stack
        visible: true
        initialItem: login
        anchors.fill: parent
    }

    

    LoginScreenForm{
        id: login
	    visible: false
        anchors.fill: stack
        // videoOutput.onCompleted _faceregco.operate(textField.text)
        button.onClicked: function (){
            animatedImage.visible="true"
            _faceregco.operate(textField.text)
        }
        button2.onClicked: function (){
            animatedImage.visible="true"
            // API login request
            stack.replace(login,menu)
        }
        text1.text: _faceregco.number
        text1.onTextChanged: function() {
            if(text1.text == "hoang"){
                messageDialog.open()
                messageDialog.text = "Bạn có phải là " + text1.text
            }if (text1.text == "1") {
                image.source = "file:/home/hoang/workspace/faceregconition/mtcnn_facenet_cpp_tensorRT/src/Images/a.jpeg"    
            }if (text1.text == "2"){
                image.source = "file:/home/hoang/workspace/faceregconition/mtcnn_facenet_cpp_tensorRT/src/Images/b.jpeg"
            }
        }
        messageDialog.onYes: {
            stack.replace(login,menu)
        }
        messageDialog.onNo: {
            messageDialog.close()
        }
    }

    MenuScreenForm{
        id: menu
        anchors.fill: stack
        visible: false
        text2.text: _eventLoop.number
        text2.onTextChanged: function(){
            for(var i = column.children.length; i > 0 ; i--) {
                column.children[i-1].destroy()
            } 
            _request.operate("https://192.168.1.102:5001/home/studentslist")           
            var studentslist = _request.response
            _request.operate("https://192.168.1.102:5001/home/allstudentsofstudy")
            var allstudentsofstudy = _request.response
            var numOn = 0
            var numOff = 0
            var component;
            var sprite;
            var jsonstudentslist = JSON.parse(studentslist)
            var jsonallstudentsofstudy = JSON.parse(allstudentsofstudy)
            total.text="Total students: " + jsonallstudentsofstudy.length
            jsonallstudentsofstudy.forEach(function callback(i,idx,jsonallstudentsofstudy){
                                        component = Qt.createComponent("newitem.qml")                                   
                                    if (component.status === Component.Ready){
                                        sprite = component.createObject(column);
                                        jsonstudentslist.forEach(function callback(j,jdx,jsonstudentslist){
                                            if(i.idstudent == j.id){
                                                if(i.absent == "Offline"){
                                                    numOff += 1
                                                    sprite.myColor = "red"
                                                    sprite.studentid = j.lastname
                                                    sprite.url = "qrc:/Images/noimage.png"
                                                } else{
                                                    numOn += 1
                                                    sprite.myColor = "green"
                                                    sprite.studentid = j.lastname
                                                    if(j.lastname == "Ngoc Ninh"){
						                                sprite.url = "qrc:/Images/ninh.jpeg"
                                                    } else{
                                                        sprite.url = "qrc:/Images/hoang.jpeg"
                                                    }
                                                }
                                            }
                                            
                                        })
                                        //pane.height = pane.height + sprite.height
                                    }
                                })
            online.text = "Attendance: " + numOn
            offline.text = "Absent: " + numOff
        }
        Component.onCompleted: function(){
                    // _request.operate("https://30f48210adf5.ngrok.io/home/download")
                    // _present.operate("hello")
                    _request.operate("https://192.168.1.102:5001/home/slideslist")
                    var component;
                    var sprite;
                    var slideslist = _request.response
                    var jsonslideslist = JSON.parse(slideslist)
                    jsonslideslist.forEach(function callback(i,idx,jsonslideslist){
                                                component = Qt.createComponent("newitem2.qml")
                                                if (component.status === Component.Ready){
                                                    sprite = component.createObject(column2);
                                                    sprite.name = i.pathfile
                                                    console.log(i.pathfile)
                                                }
                                            })
                    _eventLoop.operate("");   
                }
    //     button1.onPressed: function(){
    //         for(var i = column.children.length; i > 0 ; i--) {
    //             column.children[i-1].destroy()
    //         } 
    //         _request.operate("https://192.168.1.102:5001//home/studentslist")           
    //         var studentslist = _request.response
    //         _request.operate("https://192.168.1.102:5001//home/allstudentsofstudy")
    //         var allstudentsofstudy = _request.response
    //         var numOn = 0
    //         var numOff = 0vum
    //         var component;
    //         var sprite;
    //         var jsonstudentslist = JSON.parse(studentslist)
    //         var jsonallstudentsofstudy = JSON.parse(allstudentsofstudy)
    //         total.text="Total students: " + jsonallstudentsofstudy.length
    //         jsonallstudentsofstudy.forEach(function callback(i,idx,jsonallstudentsofstudy){
    //                                     component = Qt.createComponent("newitem.qml")                                   
    //                                 if (component.status === Component.Ready){
    //                                     sprite = component.createObject(column);
    //                                     jsonstudentslist.forEach(function callback(j,jdx,jsonstudentslist){
    //                                         if(i.idstudent == j.id){
    //                                             if(i.absent == "Offline"){
    //                                                 numOff += 1
    //                                                 sprite.myColor = "red"
    //                                                 sprite.studentid = j.lastname
    //                                             } else{
    //                                                 numOn += 1
    //                                                 sprite.myColor = "green"
    //                                                 sprite.studentid = j.lastname
	// 					                            sprite.url = "qrc:/Images/ninh.jpeg"
    //                                             }
    //                                         }
                                            
    //                                     })
    //                                     //pane.height = pane.height + sprite.height
    //                                 }
    //                             })
    //         online.text = "Attendance: " + numOn
    //         offline.text = "Absent: " + numOff
    //     }
    }

//    Item{
//        id: login
//        visible: true
//        //anchors.fill: parent
//        Button{
//            id: button
//            onClicked: function toMain(){
//                stack.replace(login,mainmenu)
//            }
//            anchors.centerIn: parent
//        }
//        Text{
//            text: "Login"
//            anchors.centerIn: parent
//        }
//        Text{
//            id: hiddentext
//            visible: false
//            text: _faceregco.number
//        }

//        Button{
//            id: couter
//            text: _faceregco.number
//            onClicked: _faceregco.operate("hoang")
//            anchors.alignWhenCentered: button
//            onTextChanged: function update(){
//                                if(hiddentext.text == "hoang"){
//                                    stack.replace(login,menu)
//                                }
//                           }
//        }
//    }
}

