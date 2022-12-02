import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Window {
    id: mainWindow
    visible: true
    title: "Otus C++ CV project"
    width: 600
    height: 350
//    color: Material.Purple
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    //Объявляем сигналы
    signal btnSearchClicked()
    signal textFieldEditingFinished(msg: string)
    signal cboxAccepted(count: int)

    //Расположить Окно по центру
//    screen: Qt.application.screens[2]
    Component.onCompleted: {
        mainWindow.x = Screen.virtualX + (Screen.width - this.width) / 2
        mainWindow.y = Screen.virtualY + (Screen.height - this.height) / 2
    }

    
}

