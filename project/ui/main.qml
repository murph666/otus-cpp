import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtQuick.Controls.Material 2.15

Window {
    id: mainWindow
    visible: true
    title: "Otus C++ CV project"
    color: "#C2A83E"
    width: 1920
    height: 1080
    //    flags: Qt.FramelessWindowHint

    //Объявляем сигналы
    signal btnSearchClicked()
    signal btnConnectClicked()
    signal btnGrabbingClicked()
    signal swchViewToggled(value: bool)
    //    signal textFieldEditingFinished(msg: string)
    signal cboxAccepted(count: int)
    signal firstHandleOfThresholdSliderChanged(value: int)
    signal secondHandleOfThresholdSliderChanged(value: int)

    //Расположить Окно по центру
    //    screen: Qt.application.screens[2]
    //    visibility: "FullScreen"
    Component.onCompleted: {
        mainWindow.x = Screen.virtualX + (Screen.width - this.width) / 2
        mainWindow.y = Screen.virtualY + (Screen.height - this.height) / 2
    }



    SwipeView {
        id: swipeView
        anchors.fill: parent
        anchors.bottomMargin: tabBar.height

        currentIndex: tabBar.currentIndex

        MainPage{

        }
        CameraPage {

        }
        DrawPage {
        }



    }

    TabBar {
        id: tabBar
        width: mainWindow.width
        anchors.bottom: parent.bottom
        contentHeight: 60
        contentWidth: parent.width
        currentIndex: swipeView.currentIndex

        TabButton {
            id: tabButtonMain
            text: "Main"
            height: parent.height
            background: Rectangle {
                color: parent.active ? "#7CA982" :
                                       (tabBar.currentIndex === 0 ? "#243E36" : "#7CA982")
            }

        }

        TabButton {
            id: tabButtonConnection
            text: "Connection"
            height: parent.height
            background: Rectangle {
                color: parent.active ? "#7CA982" :
                                       (tabBar.currentIndex === 1 ? "#243E36" : "#7CA982")
            }
        }

        TabButton {
            id: tabButtonDraw
            text: "Draw"
            height: parent.height
            background: Rectangle {
                color: parent.active ? "#7CA982" :
                                       (tabBar.currentIndex === 2 ? "#243E36" : "#7CA982")
            }
        }

    }

    //    Rectangle{
    //        id: mainLayout
    //        visible: true
    //        color: "#E0EEC6"
    //        radius: 20
    //        property bool counter: false
    //        anchors.fill: parent
    //        anchors.margins: 10
    //        anchors.bottomMargin: 74


    //        Image{
    //            id: opencvImage
    //            readonly property string providerSource: "image://stream/";

    //            anchors.fill: parent
    //            anchors.margins: 10
    //            anchors.bottomMargin: row.height * 2 + 40
    //            visible: true
    //            fillMode: Image.PreserveAspectFit
    //            asynchronous: false
    //            cache: false

    //            function reload() {
    //                var oldSource = providerSource;
    //                source = "";
    //                source = oldSource;
    //            }

    //        }

    //        Row {
    //            id: row
    //            width: parent.width - 20
    //            spacing: 20
    //            anchors.bottom: parent.bottom

    //            anchors.bottomMargin: row.height + 20
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            Button {
    //                id: buttonCameraSearch
    //                text: "Search"
    //                width: 100
    //                height: 50
    //                contentItem: Text {
    //                    text: parent.text
    //                    font: parent.font
    //                    color: "#F1F7ED"
    //                    horizontalAlignment: Text.AlignHCenter
    //                    verticalAlignment: Text.AlignVCenter
    //                }
    //                background: Rectangle {
    //                    radius: 5
    //                    color: parent.down ? "#7CA982" :
    //                                         (parent.hovered ? "#243E36" : "#7CA982")
    //                }
    //                onClicked: mainWindow.btnSearchClicked()
    //            }

    //            ComboBox {
    //                id: comboConnectedDevice
    //                width: parent.width - 360
    //                height: parent.height
    //                Layout.alignment: Qt.AlignHCenter
    //                Layout.fillWidth: true
    //                model: connectedDeviceModel.comboList

    //                contentItem: Text {
    //                    leftPadding: 0
    //                    rightPadding: parent.indicator.width + parent.spacing

    //                    text: parent.displayText
    //                    font: parent.font
    //                    color: "#F1F7ED"//parent.pressed ? "#7CA982" : "#7CA982"
    //                    horizontalAlignment: Text.AlignHCenter
    //                    verticalAlignment: Text.AlignVCenter
    //                }

    //                background: Rectangle {
    //                    radius: 5
    //                    color: parent.down ? "#7CA982" :
    //                                         (parent.hovered ? "#243E36" : "#7CA982")
    //                }
    //                onActivated: mainWindow.cboxAccepted(this.currentIndex)
    //            }

    //            Button {
    //                id: buttonCameraConnect
    //                text: "Connect"
    //                width: 100
    //                height: 50
    //                contentItem: Text {
    //                    font: parent.font
    //                    color: "#F1F7ED"
    //                    text: parent.text
    //                    horizontalAlignment: Text.AlignHCenter
    //                    verticalAlignment: Text.AlignVCenter
    //                }
    //                background: Rectangle {
    //                    radius: 5
    //                    color: parent.down ? "#7CA982" :
    //                                         (parent.hovered ? "#243E36" : "#7CA982")
    //                }
    //                onClicked: mainWindow.btnConnectClicked()
    //            }

    //            Button {
    //                id: buttonCameraGrabbing
    //                text: "Start"
    //                width: 100
    //                height: 50
    //                contentItem: Text {
    //                    font: parent.font
    //                    color: "#F1F7ED"
    //                    text: parent.text
    //                    horizontalAlignment: Text.AlignHCenter
    //                    verticalAlignment: Text.AlignVCenter
    //                }
    //                background: Rectangle {
    //                    radius: 5
    //                    color: parent.down ? "#7CA982" :
    //                                         (parent.hovered ? "#243E36" : "#7CA982")
    //                }
    //                onClicked: mainWindow.btnGrabbingClicked()
    //            }



    //        }

    //        Row {
    //            id: row1
    //            width: parent.width - 20
    //            height: row.height
    //            spacing: 20
    //            anchors.bottom: parent.bottom
    //            anchors.bottomMargin: 10
    //            anchors.horizontalCenter: parent.horizontalCenter

    //            Row {
    //                id: doubleLabelSwitch
    //                anchors.verticalCenter: parent.verticalCenter
    ////                width: 200
    //                height: row1.height

    //                Label{
    //                    id:labelOriginal
    //                    text: qsTr("Original")
    //                    color: "#7CA982"
    //                    anchors.verticalCenter: parent.verticalCenter
    //                    font.pointSize: 16

    //                }

    //                Switch {
    //                    id: switchView
    //                    anchors.verticalCenter: parent.verticalCenter
    ////                    width: 100
    //                    indicator: Rectangle {
    //                        implicitWidth: 48
    //                        implicitHeight: 26
    //                        x: switchView.leftPadding
    //                        y: parent.height / 2 - height / 2
    //                        radius: 13
    //                        color: switchView.checked ? "#7CA982" : "#ffffff"
    //                        border.color: switchView.checked ? "#7CA982" : "#cccccc"

    //                        Rectangle {
    //                            x: switchView.checked ? parent.width - width : 0
    //                            width: 26
    //                            height: 26
    //                            radius: 13
    //                            color: switchView.down ? "#cccccc" : "#ffffff"
    //                            border.color: switchView.checked ? "#7CA982": "#999999"
    //                        }
    //                    }
    //                    onToggled: mainWindow.swchViewToggled(this.checked)
    //                }

    //                Label{
    //                    id:labelThresh
    //                    text: qsTr("Binary")
    //                    anchors.verticalCenter: parent.verticalCenter
    //                    font.pointSize: 16
    //                    color: "#7CA982"
    //                }

    //            }

    //            RangeSlider {
    //                id: control
    //                width: comboConnectedDevice.width
    //                from: 0
    //                to: 255
    //                first.value: 25
    //                second.value: 235
    //                anchors.verticalCenter: parent.verticalCenter

    //                background: Rectangle {
    //                    x: control.leftPadding
    //                    y: control.topPadding + control.availableHeight / 2 - height / 2
    //                    width: control.availableWidth
    //                    height: 4
    //                    radius: 2
    //                    color: "#F1F7ED"

    //                    Rectangle {
    //                        x: control.first.visualPosition * parent.width
    //                        width: control.second.visualPosition * parent.width - x
    //                        height: parent.height
    //                        color: "#7CA982"
    //                        radius: 2
    //                    }
    //                }

    //                first.handle: Rectangle {
    //                    x: control.leftPadding + control.first.visualPosition * (control.availableWidth - width)
    //                    y: control.topPadding + control.availableHeight / 2 - height / 2
    //                    implicitWidth: 26
    //                    implicitHeight: 26
    //                    radius: 13
    //                    color: control.first.pressed ? "#F1F7ED" : "#f6f6f6"
    //                    border.color: "#bdbebf"

    //                }

    //                second.handle: Rectangle {
    //                    x: control.leftPadding + control.second.visualPosition * (control.availableWidth - width)
    //                    y: control.topPadding + control.availableHeight / 2 - height / 2
    //                    implicitWidth: 26
    //                    implicitHeight: 26
    //                    radius: 13
    //                    color: control.second.pressed ? "#F1F7ED" : "#f6f6f6"
    //                    border.color: "#bdbebf"
    //                }

    //                first.onValueChanged: mainWindow.firstHandleOfThresholdSliderChanged(first.value)
    //                second.onValueChanged: mainWindow.secondHandleOfThresholdSliderChanged(second.value)
    //            }
    //            CheckBox {
    //                id: checkBox
    //                text: qsTr("Contour")
    //                anchors.verticalCenter: parent.verticalCenter
    //                contentItem: Text {
    //                    font: parent.font

    //                    color: "#7CA982"
    //                    text: parent.text
    //                    horizontalAlignment: Text.AlignHCenter
    //                    verticalAlignment: Text.AlignVCenter
    //                }
    //            }
    //        }
    //    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
