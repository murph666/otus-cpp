#include "mainWindow.h"
//QMessageBox::information(NULL, "Error", errorMsg);

MainWindow::MainWindow(QQmlApplicationEngine *engine,
                       ObjectCamVideo *camera,
                       OpencvImageProvider *liveImageProvider,
                       ComboBoxModel *listOfCameras,
                       ModelForListOfCameras *listOfCameras1){
    this -> engine = engine;
    this -> camera = camera;
    this -> liveImageProvider = liveImageProvider;
    this -> listOfCameras = listOfCameras;
    this -> listOfCameras1 = listOfCameras1;


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

    QObject::connect(item, SIGNAL(swchViewToggled(bool)),
                     this, SLOT(on_swchViewToggled(bool)));

    QObject::connect(item, SIGNAL(cboxAccepted(int)),
                     this, SLOT(on_cboxAccepted(int)));

    QObject::connect(item, SIGNAL(firstHandleOfThresholdSliderChanged(int)),
                     this, SLOT(on_firstHandleOfThresholdSliderChanged(int)));

    QObject::connect(item, SIGNAL(secondHandleOfThresholdSliderChanged(int)),
                     this, SLOT(on_secondHandleOfThresholdSliderChanged(int)));


}

void MainWindow::on_btnSearchClicked(){
    QStringList comboList = camera->searchConnectedCameras();
    listOfCameras->setComboList(comboList);
//    listOfCameras1->setComboList(comboList);

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
    currentIndexOfComboBox = count;
}

void MainWindow::on_swchViewToggled(bool value){
    std::cout << "on_swchViewToggled:"<< value << std::endl;
    camera -> m_bView = value;
}

void MainWindow::on_firstHandleOfThresholdSliderChanged(int value){
    std::cout << "on_firstHandleOfThresholdSliderChanged:"<< value << std::endl;
    camera -> m_lowLvlOfThreshold = value;
}
void MainWindow::on_secondHandleOfThresholdSliderChanged(int value){
    std::cout << "on_secondHandleOfThresholdSliderChanged:"<< value << std::endl;
    camera -> m_highLvlOfThreshold = value;
}

