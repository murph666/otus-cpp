import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtQuick.Controls.Material 2.15

Window {
    id: mainWindow
    visible: true
    title: "Otus C++ CV project"
    color: "#C2A83E"
    width: 1024
    height: 600
    //    flags: Qt.FramelessWindowHint

    //Объявляем сигналы
    signal btnSearchClicked()
    signal btnConnectClicked()
    signal btnGrabbingClicked()
    //    signal textFieldEditingFinished(msg: string)
    signal cboxAccepted(count: int)

    //Расположить Окно по центру
//    screen: Qt.application.screens[2]
//    visibility: "FullScreen"
    Component.onCompleted: {
        mainWindow.x = Screen.virtualX + (Screen.width - this.width) / 2
        mainWindow.y = Screen.virtualY + (Screen.height - this.height) / 2
    }

    Connections {
        target: liveImageProvider
        function onImageChanged() { opencvImage.reload() }
    }

    Rectangle{
        id: mainLayout
        visible: true
        color: "#E0EEC6"
        radius: 20
        property bool counter: false
        anchors.fill: parent
        anchors.margins: 10


        Image{
            id: opencvImage
            readonly property string providerSource: "image://stream/";

            anchors.fill: parent
            anchors.margins: 10
            anchors.bottomMargin: buttonCameraSearch.height + 10
            visible: true
            fillMode: Image.PreserveAspectFit
            asynchronous: false
            cache: false

            function reload() {
                var oldSource = providerSource;
                source = "";
                source = oldSource;
            }

        }

        Row {
            id: row
            width: parent.width - 20
            spacing: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: buttonCameraSearch
                text: "Search"
                width: 100
                height: 50
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "#F1F7ED"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    color: parent.down ? "#7CA982" :
                                         (parent.hovered ? "#243E36" : "#7CA982")
                }
                onClicked: mainWindow.btnSearchClicked()
            }

            ComboBox {
                id: comboConnectedDevice
                width: parent.width - 360
                height: parent.height
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                model: connectedDeviceModel.comboList

                contentItem: Text {
                    leftPadding: 0
                    rightPadding: parent.indicator.width + parent.spacing

                    text: parent.displayText
                    font: parent.font
                    color: "#F1F7ED"//parent.pressed ? "#7CA982" : "#7CA982"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 5
                    color: parent.down ? "#7CA982" :
                                         (parent.hovered ? "#243E36" : "#7CA982")
                }
                onActivated: mainWindow.cboxAccepted(this.currentIndex)
            }

            Button {
                id: buttonCameraConnect
                text: "Connect"
                width: 100
                height: 50
                contentItem: Text {
                    font: parent.font
                    color: "#F1F7ED"
                    text: parent.text
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    color: parent.down ? "#7CA982" :
                                         (parent.hovered ? "#243E36" : "#7CA982")
                }
                onClicked: mainWindow.btnConnectClicked()
            }

            Button {
                id: buttonCameraGrabbing
                text: "Start"
                width: 100
                height: 50
                contentItem: Text {
                    font: parent.font
                    color: "#F1F7ED"
                    text: parent.text
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    color: parent.down ? "#7CA982" :
                                         (parent.hovered ? "#243E36" : "#7CA982")
                }
                onClicked: mainWindow.btnGrabbingClicked()
            }



        }
    }

}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
