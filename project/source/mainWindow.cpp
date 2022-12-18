#include "mainWindow.h"
//QMessageBox::information(NULL, "Error", errorMsg);

MainWindow::MainWindow(QQmlApplicationEngine *engine,
                       ObjectCamVideo *camera,
                       OpencvImageProvider *liveImageProvider,
                       ComboBoxModel *listOfCameras){
    this -> engine = engine;
    this -> camera = camera;
    this -> liveImageProvider = liveImageProvider;
    this -> listOfCameras = listOfCameras;

    this -> ConnectSignals();
}

void MainWindow::ConnectSignals(){
    // создаю поинтер на список объектов с QML для подключение сигнала к слоту
    QObject* item = (QObject*)this -> engine -> rootObjects().at(0);

    QObject::connect(camera, &ObjectCamVideo::emitImage,
                     liveImageProvider, &OpencvImageProvider::updateImage);
    //Сигнал с private slots объекта MainWindow без параметров функции
    QObject::connect(item, SIGNAL(btnSearchClicked()),
                     this, SLOT(on_btnSearchClicked()));

    QObject::connect(item, SIGNAL(btnConnectClicked()),
                     this, SLOT(on_btnConnectClicked()));

    QObject::connect(item, SIGNAL(btnGrabbingClicked()),
                     this, SLOT(on_btnGrabbingClicked()));

    QObject::connect(item, SIGNAL(cboxAccepted(int)),
                     this, SLOT(on_cboxAccepted(int)));


}

void MainWindow::on_btnSearchClicked(){
    QStringList comboList = camera->searchConnectedCameras();
    listOfCameras->setComboList(comboList);

}

void MainWindow::on_btnConnectClicked(){
    camera->openCamera(&currentIndexOfComboBox);
}

void MainWindow::on_btnGrabbingClicked(){
    if (camera->m_bGrabbing == false){
        //start
        camera -> startGrabbing();
    }
    else{
        //stop
        camera -> stopGrabbing();
    }
}

void MainWindow::on_cboxAccepted(int count){
    std::cout << "on_cboxAccepted" << std::endl;
    currentIndexOfComboBox = count;
}

