#include "mainWindow.h"
//QMessageBox::information(NULL, "Error", errorMsg);

MainWindow::MainWindow(QQmlApplicationEngine *engine,
                       OpencvImageProvider *liveImageProvider,
                       ModelForListOfCameras *modelForListOfCameras
                       ){
    this -> engine = engine;
    this -> liveImageProvider = liveImageProvider;
    this -> modelForListOfCameras = modelForListOfCameras;

    std::cout << "ModelForListOfCameras" << modelForListOfCameras << std::endl;


    this -> ConnectSignals();
}


void MainWindow::ConnectSignals(){
    // создаю поинтер на список объектов с QML для подключение сигнала к слоту
    QObject* item = (QObject*)this -> engine -> rootObjects().at(0);

    //    QObject::connect(camera, &ObjectCamVideo::emitImage,
    //                     liveImageProvider, &OpencvImageProvider::updateImage);
    //Сигнал с private slots объекта MainWindow без параметров функции
    QObject::connect(item, SIGNAL(btnSearchClicked()),
                     this, SLOT(on_btnSearchClicked()));

    QObject::connect(item, SIGNAL(btnConnectClicked()),
                     this, SLOT(on_btnConnectClicked()));

    //    QObject::connect(item, SIGNAL(btnGrabbingClicked()),
    //                     this, SLOT(on_btnGrabbingClicked()));

    //    QObject::connect(item, SIGNAL(swchViewToggled(bool)),
    //                     this, SLOT(on_swchViewToggled(bool)));

    //    QObject::connect(item, SIGNAL(cboxAccepted(int)),
    //                     this, SLOT(on_cboxAccepted(int)));

    //    QObject::connect(item, SIGNAL(firstHandleOfThresholdSliderChanged(int)),
    //                     this, SLOT(on_firstHandleOfThresholdSliderChanged(int)));

    //    QObject::connect(item, SIGNAL(secondHandleOfThresholdSliderChanged(int)),
    //                     this, SLOT(on_secondHandleOfThresholdSliderChanged(int)));


}

void MainWindow::on_btnSearchClicked(){
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    if (MV_OK == nRet)
    {
        if (m_stDevList.nDeviceNum == 0){
            std::cout << "No connected cameras were detected" << std::endl;
            //            list.append(QString("No connected cameras were detected"));
            //            ShowErrorMsg("No connected cameras were detected", 0);
        }
        else{
            for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++){
                CameraItem bufItem;
                QString strMsg;
                MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    std::cout << "NULL" << std::endl;
                    continue;
                }

                if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
                {
                    int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
                    int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
                    int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
                    int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

                    if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName) != 0)
                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));
                        strMsg = QString("[%0d]GigE:   %1d.%2d.%3d.%4d").arg(QString::number(i),
                                                                             QString::number(nIp1),
                                                                             QString::number(nIp2),
                                                                             QString::number(nIp3),
                                                                             QString::number(nIp4));
                    }
                    else
                    {

                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName));
                        QString qstrModelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
                        QString qstrSerialNumber = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber));
                        strMsg = QString("[%0]GigE:%1   %2.%3.%4.%5").arg(QString::number(i),
                                                                          qstrModelName,
                                                                          QString::number(nIp1),
                                                                          QString::number(nIp2),
                                                                          QString::number(nIp3),
                                                                          QString::number(nIp4));
                        std::cout << strMsg.toStdString() << std::endl;
                        bufItem.Number = i;
                        bufItem.Name = qstrModelName;
                        bufItem.Addr = QString("%2.%3.%4.%5").arg(QString::number(nIp1),
                                                                  QString::number(nIp2),
                                                                  QString::number(nIp3),
                                                                  QString::number(nIp4));

                    }
                }
                else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
                {
                    if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName));
                        strMsg = QString("[%0]UsbV3:  %1").arg(QString::number(i),
                                                               qstrUserDefinedName);
                    }
                    else
                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName));
                        QString qstrModelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName));
                        QString qstrSerialNumber = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber));
                        strMsg = QString("[%0]UsbV3:  %1").arg(QString::number(i),
                                                               qstrModelName);
                        std::cout << strMsg.toStdString() << std::endl;
                        bufItem.Number = i;
                        bufItem.Name = qstrModelName;
                    }
                }
                else
                {
                    std::cout << "Unknown device enumerated" << std::endl;
                    //                    ShowErrorMsg("Unknown device enumerated", 0);
                }
                CameraItem test = {0, QStringLiteral("name"),QStringLiteral("addr"), 1};
                this -> modelForListOfCameras->items().append(test);
            }
        }
    }

}

void MainWindow::on_btnConnectClicked(){
    std::cout << "on_btnConnectClicked:" << std::endl;
    //    camera->openCamera(&currentIndexOfComboBox);
}

//void MainWindow::on_btnGrabbingClicked(){
//    if (camera->m_bGrabbing == false){
//        //start
//        camera -> startGrabbing();
//    }
//    else{
//        //stop
//        camera -> stopGrabbing();
//    }
//}

//void MainWindow::on_cboxAccepted(int count){
//    currentIndexOfComboBox = count;
//}

//void MainWindow::on_swchViewToggled(bool value){
//    std::cout << "on_swchViewToggled:"<< value << std::endl;
//    camera -> m_bView = value;
//}

//void MainWindow::on_firstHandleOfThresholdSliderChanged(int value){
//    std::cout << "on_firstHandleOfThresholdSliderChanged:"<< value << std::endl;
//    camera -> m_lowLvlOfThreshold = value;
//}
//void MainWindow::on_secondHandleOfThresholdSliderChanged(int value){
//    std::cout << "on_secondHandleOfThresholdSliderChanged:"<< value << std::endl;
//    camera -> m_highLvlOfThreshold = value;
//}

