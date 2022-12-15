#include "objectcamvideo.h"
#include <iostream>
#include <QDebug>

ObjectCamVideo::ObjectCamVideo(QObject *parent)
    : QObject{parent}
{
    std::cout <<"ObjectCamVideo constructor: "<< this << std::endl;
}

void ObjectCamVideo::openCamera(){
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;

    this -> moveToThread(threadStreamer);
    QObject::connect(threadStreamer, SIGNAL(started()), this, SLOT(streamerThread()));
    this->threadStreamer->start();
}

void ObjectCamVideo::streamerThread()
{
    while (true) {
        //        cap->read(frame);
        //        if(frame.data){
        ////            std::cout << frame.data << std::endl;
        //            QImage img = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
        //            emit emitImage(img);
        //        }
        //        if(QThread::currentThread()->isInterruptionRequested())
        //        {
        //            cap->release();
        //            return;
        //        }

    }
}

QStringList ObjectCamVideo::searchConnectedCameras(){
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    QStringList list;
    if (MV_OK == nRet)
    {
        if (m_stDevList.nDeviceNum == 0){
            std::cout << "No connected cameras were detected" << std::endl;
//            ShowErrorMsg("No connected cameras were detected", 0);
        }
        else{
            for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++){
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
                        std::cout<< strMsg.toStdString() << std::endl;
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
                        std::cout<< strMsg.toStdString() << std::endl;
                        }
                }
                else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
                {
                    if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName));
                        strMsg = QString("[%0]UsbV3:  %1").arg(QString::number(i),
                                                               qstrUserDefinedName);
                        std::cout<< strMsg.toStdString() << std::endl;
                    }
                    else                std::string temp = strMsg.toStdString();

                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName));
                        QString qstrModelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName));
                        QString qstrSerialNumber = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber));
                        strMsg = QString("[%0]UsbV3:  %1").arg(QString::number(i),
                                                               qstrModelName);

                        std::cout<< strMsg.toStdString() << std::endl;
                    }
                }
                else
                {
                    std::cout << "Unknown device enumerated" << std::endl;
//                    ShowErrorMsg("Unknown device enumerated", 0);
                }
                std::cout << typeid(strMsg).name() << std::endl;
//                list.append(strMsg);
                }
            }
    }

    return list;
}


