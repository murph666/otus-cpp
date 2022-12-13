import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: mainWindow
    visible: true
    title: "Otus C++ CV project"
    width: 600
    height: 400

    color: "#C2A83E"
    //    flags: Qt.FramelessWindowHint

    //Объявляем сигналы
    signal btnSearchClicked()
    signal btnConnectClicked()
//    signal textFieldEditingFinished(msg: string)
//    signal cboxAccepted(count: int)

    //Расположить Окно по центру
    //    screen: Qt.application.screens[2]
    Component.onCompleted: {
        mainWindow.x = Screen.virtualX + (Screen.width - this.width) / 2
        mainWindow.y = Screen.virtualY + (Screen.height - this.height) / 2
    }

    Rectangle{
        id: mainLayout
        visible: true
        color: "#E0EEC6"
        radius: 20

        anchors.fill: parent
        anchors.margins: 10
        anchors.topMargin: 60

        Image{
            id: opencvImage

            anchors.fill: parent
            anchors.margins: 10
            anchors.bottomMargin: buttonCameraSearch.height + 10
            fillMode: Image.PreserveAspectFit
            visible: true
            source: "image://stream/image"
            cache: false

        }

        Row {
            id: row
            width: mainLayout.width - 300
            spacing: row.width - 2 * buttonCameraSearch.width

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
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

            Button {
                id: buttonCameraConnect
                text: "Connect"
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
                onClicked: mainWindow.btnConnectClicked()
            }
        }
    }
}

