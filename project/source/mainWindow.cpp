#include "mainWindow.h"
#include "qqmlcontext.h"
//QMessageBox::information(NULL, "Error", errorMsg);

MainWindow::MainWindow(QQmlApplicationEngine *engine,
                       ObjectCamVideo* camera,
                       OpencvImageProvider* liveImageProvider){
    std::cout <<"MainWindow constructor" << std::endl;
    this -> engine = engine;
    this -> camera = camera;
    this -> liveImageProvider = liveImageProvider;

    this -> ConnectSignals();
}

void MainWindow::ConnectSignals(){
    // создаю поинтер на список объектов с QML для подключение сигнала к слоту
    QObject* item = (QObject*)this -> engine -> rootObjects().at(0);



    //Сигнал с private slots объекта MainWindow без параметров функции
    QObject::connect(item, SIGNAL(btnSearchClicked()),
                     this, SLOT(on_btnSearchClicked()));

    QObject::connect(item, SIGNAL(btnConnectClicked()),
                     this, SLOT(on_btnConnectClicked()));


}

void MainWindow::on_btnSearchClicked(){
    std::cout << "on_btnSearchClicked" << std::endl;


}

void MainWindow::on_btnConnectClicked(){
    std::cout << "on_btnConnectClicked" << std::endl;
    camera->openCamera();
}
