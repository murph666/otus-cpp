#include "objectcamvideo.h"
#include "qregularexpression.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <QDebug>

ObjectCamVideo::ObjectCamVideo(QObject *parent)
    : QObject{parent}
{
    std::cout <<"ObjectCamVideo constructor: "<< this << std::endl;
    this -> moveToThread(threadStreamer);
    QObject::connect(threadStreamer, SIGNAL(started()), this, SLOT(streamerThread()));
}



void ObjectCamVideo::openCamera(int *cameraNumber){
    int nIndex = *cameraNumber;

    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);
    if (MV_OK != nRet)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        //        ShowErrorMsg("Open Fail", nRet);
        std::cout << "Open Fail" << std::endl;
        return;
    }
    else{
        std::cout << "Open Succes" << std::endl;
    }

    if (m_stDevList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
    {
        unsigned int nPacketSize = 0;
        nRet = m_pcMyCamera->GetOptimalPacketSize(&nPacketSize);
        if (nRet == MV_OK)
        {
            nRet = m_pcMyCamera->SetIntValue("GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK)
            {
                //                ShowErrorMsg("Warning: Set Packet Size fail!", nRet);
                std::cout << "Warning: Set Packet Size fail!" << std::endl;
            }
        }
        else
        {
            //            ShowErrorMsg("Warning: Get Packet Size fail!", nRet);
            std::cout << "Get Packet Size fail!" << std::endl;

        }
    }

    m_pcMyCamera->SetEnumValue("AcquisitionMode", MV_ACQ_MODE_CONTINUOUS);
    m_pcMyCamera->SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);

    //    MVCC_INTVALUE_EX stParam;
    //    memset(&stParam, 0, sizeof(MVCC_INTVALUE_EX));
    //    nRet = m_pcMyCamera -> GetIntValue("PayloadSize", &stParam);
    //    std::cout <<"streamerThread 1"<<std::endl;
    //    if (MV_OK != nRet)
    //    {
    //        std::cout <<"Get PayloadSize fail"<<std::endl;
    //        //            printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
    //        return;
    //    }
    //    else {std::cout <<"Get PayloadSize succes"<<std::endl;}

}

void ObjectCamVideo::startGrabbing(){
    int nRet = m_pcMyCamera->StartGrabbing();
    if (MV_OK != nRet)
    {
        std::cout << "Start grabbing fail" << std::endl;
        //            ShowErrorMsg("Start grabbing fail", nRet);
        return;
    }
    else{
        std::cout << "Start grabbing succes" << std::endl;
        m_bGrabbing = true;
        this->threadStreamer->start();
    }

}

void ObjectCamVideo::stopGrabbing(){

    int nRet = m_pcMyCamera->StopGrabbing();
    if (MV_OK != nRet)
    {
        std::cout << "Stop grabbing fail" << std::endl;
        //        ShowErrorMsg("Stop grabbing fail", nRet);
        return;
    }
    else{
        std::cout << "Stop grabbing succes" << std::endl;
        m_bGrabbing = false;
        this -> threadStreamer->exit();
    }

}


void ObjectCamVideo::streamerThread()
{
    std::cout <<"streamerThread 0"<<std::endl;

    int nRet = MV_OK;
    MV_FRAME_OUT stImageInfo;
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT));
    QImage emitedFrame;
    while(1)
    {
        if (m_bGrabbing){
            auto start = std::chrono::high_resolution_clock::now();
            nRet = m_pcMyCamera ->GetImageBuffer(&stImageInfo, 10);
            if (nRet == MV_OK)
            {
                frame.pBufAddr = (unsigned char*) std::malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
                std::memcpy(frame.pBufAddr, stImageInfo.pBufAddr, (size_t) sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
                frame.stFrameInfo = stImageInfo.stFrameInfo;

                threshold();
                if (m_bView == 1){
                    emitedFrame = QImage(frame.pBufAddr, frame.stFrameInfo.nWidth, frame.stFrameInfo.nHeight, QImage::Format::Format_Grayscale8);
                }
                else {
                    emitedFrame = QImage(stImageInfo.pBufAddr,stImageInfo.stFrameInfo.nWidth,stImageInfo.stFrameInfo.nHeight, QImage::Format::Format_Grayscale8);
                }

                emit emitImage(emitedFrame);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                std::cout << "Time taken by GetImageBuffer: " <<(float) duration.count() / 1000000 << " seconds" << std::endl;

                if(NULL != stImageInfo.pBufAddr)
                {
                    nRet = m_pcMyCamera ->FreeImageBuffer(&stImageInfo);
                    if(nRet != MV_OK)
                    {
                        std::cout << "Free Image Buffer fail!" << nRet << std::endl;
                    }
                }
            }
        }
    }
    return;
}

void ObjectCamVideo::threshold()
{
    for (auto pixel = 0; pixel <= frame.stFrameInfo.nFrameLen ; pixel++){
        frame.pBufAddr[pixel] = (frame.pBufAddr[pixel] > m_lowLvlOfThreshold && frame.pBufAddr[pixel] < m_highLvlOfThreshold) ? 255 : 0;
    }
}

void ObjectCamVideo::imgBufToArray()
{

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
                    else                std::string temp = strMsg.toStdString();

                    {
                        QString qstrUserDefinedName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName));
                        QString qstrModelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName));
                        QString qstrSerialNumber = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber));
                        strMsg = QString("[%0]UsbV3:  %1").arg(QString::number(i),
                                                               qstrModelName);

                    }
                }
                else
                {
                    std::cout << "Unknown device enumerated" << std::endl;
                    //                    ShowErrorMsg("Unknown device enumerated", 0);
                }
                list.append(strMsg);
            }
        }
    }

    return list;
}


