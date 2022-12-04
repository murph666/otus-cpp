#include "mainWindow.h"
#include "qqmlcontext.h"
//QMessageBox::information(NULL, "Error", errorMsg);

MainWindow::MainWindow(QQmlApplicationEngine *engine){
    std::cout <<"MainWindow constructor" << std::endl;
    this -> engine = engine;
    this -> ConnectSignals();
}

void MainWindow::ConnectSignals(){
    // создаю поинтер на список объектов с QML для подключение сигнала к слоту
    QObject* item = (QObject*)this -> engine -> rootObjects().at(0);

//    this -> engine -> rootContext() -> setContextProperty("VideoStreamer", camera);
//    this -> engine -> rootContext() -> setContextProperty("liveImageProvider", liveImageProvider);
//    this -> engine -> addImageProvider("live",liveImageProvider);

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
