#include "objectcamvideo.h"
#include <iostream>
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
    if (!m_bGrabbing){
        int nRet = MV_OK;

        MVCC_INTVALUE stParam;
        memset(&stParam, 0, sizeof(MVCC_INTVALUE));
        nRet = MV_CC_GetIntValue(m_hWnd, "PayloadSize", &stParam);
        if (MV_OK != nRet)
        {
            printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
            return;
        }

        MV_FRAME_OUT stOutFrame = {0};
        memset(&stOutFrame, 0, sizeof(MV_FRAME_OUT));

        MV_FRAME_OUT_INFO_EX stImageInfo = {0};
        memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
        unsigned char * pData = (unsigned char *)malloc(sizeof(unsigned char) * stParam.nCurValue);
        if (NULL == pData)
        {
            return ;
        }
        unsigned int nDataSize = stParam.nCurValue;

        while(1)
        {
            nRet = MV_CC_GetOneFrameTimeout(m_hWnd, pData, nDataSize, &stImageInfo, 1000);
            if (nRet == MV_OK)
            {
                frame = QImage(pData,stImageInfo.nWidth, stImageInfo.nHeight,QImage::Format_RGB888).rgbSwapped();
                printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n",
                       stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
                emit emitImage(frame);
            }
            else{
                printf("No data[%x]\n", nRet);
            }
            if(NULL != stOutFrame.pBufAddr)
            {
                nRet = MV_CC_FreeImageBuffer(m_hWnd, &stOutFrame);
                if(nRet != MV_OK)
                {
                    printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
                }
            }
        }

        delete[] (pData);
        return;
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


