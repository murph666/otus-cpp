import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtQuick.Controls.Material 2.15


Item {
    width: 1900
    height: 1000
    Connections {
        target: liveImageProvider
        function onImageChanged() { opencvImage.reload() }
    }

    Rectangle{
        id: itemLayout
        visible: true
        color: "#E0EEC6"

        radius: 20
        property bool counter: false
        anchors.fill: parent
        anchors.margins: 10
        //        onHeightChanged: console.log(this.height)
        //        onWidthChanged: console.log(this.width)

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            Rectangle {
                color: '#E0EEC6'
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.minimumWidth: 50
                //Layout.maximumWidth: 300
                //Layout.minimumHeight: 150
                Layout.preferredHeight: rowLayout.height

                Image{
                    id: opencvImage
                    readonly property string providerSource: "image://stream/";

                    anchors.fill: parent
                    anchors.margins: 10

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
            }

            Rectangle {
                id: rectangle
                color: '#F1F7ED'
                radius: 20
                Layout.rightMargin: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: true
                //Layout.minimumWidth: 100
                //Layout.minimumHeight: 150
                Layout.maximumWidth: 400
                //Layout.maximumHeight: 150
                Layout.preferredWidth: 100
                Layout.preferredHeight: rowLayout.height - 2*itemLayout.radius

                ColumnLayout {
                    id: columnLayout
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    spacing: 20

                    ListView {
                        id: listView
                        height: listView.contentHeight
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10

                        spacing: 10
                        interactive: false

                        model: modelForListOfCameras.deviceList

                        delegate: Item {
                            x: 5
                            width: parent.width
                            height: 40
                            Row {
                                id: listViewRow
                                height: 40

                                Text {
                                    text: "[" + number + "]"
                                    anchors.verticalCenter: parent.verticalCenter
                                }


                                Text {
                                    text: partnumber
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                }
                                Text {
                                    text: addr
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                }

                                Rectangle {
                                    width:  20
                                    height: 20
                                    radius: 10
                                    color: (status === 0) ? "red" : (status === 1)? "blue" : "yellow"
                                    anchors.verticalCenter: parent.verticalCenter
                                }


                                spacing: 10
                            }
                        }
                    }

                    Rectangle {
                        id: span
                        color: "#7CA982"
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: columnLayout.width - 100
                        Layout.preferredHeight: 7
                        radius: 5
                    }

                    Rectangle {
                        id: controlRectangle
                        height: controlRectangle.contentHeight
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: columnLayout.width
                        Row {
                            id: controlButtonRow
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10

                            Button {
                                id: buttonCameraSearch
                                text: "Search"
                                width: (span.width - controlButtonRow.spacing) / 2
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
                                width: (span.width - controlButtonRow.spacing) / 2
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
                        }
                    }
                }
            }
        }
    }
}






/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
