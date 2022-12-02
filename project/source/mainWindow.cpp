#include "mainWindow.h"
#include <QMessageBox>
#include <iostream>

//QMessageBox::information(NULL, "Error", errorMsg);



void MainWindow::on_bnSearchClicked(){
    std::cout << "on_bnEnumClicked" << std::endl;
}

void MainWindow::on_cboxAccepted(const int &value){
    std::cout << value << std::endl;
}

void MainWindow::on_tfEditingFinished(const QString &callback){
    std::cout << &callback << std::endl;
}
