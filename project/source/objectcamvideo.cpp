#include "objectcamvideo.h"
#include <iostream>

ObjectCamVideo::ObjectCamVideo(QObject *parent)
    : QObject{parent}
{
    std::cout <<"ObjectCamVideo constructor" << std::endl;
}

void ObjectCamVideo::openCamera(){
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;
    this->cap->open(deviceID, apiID);
    if (!cap->isOpened()) {
        std::cout << "ERROR! Unable to open camera\n" << std::endl;
    }
    this -> moveToThread(this->threadStreamer);
    QObject::connect(threadStreamer,SIGNAL(started()),this,SLOT(streamerThreadSlot()));
    QObject::connect(this,&ObjectCamVideo::emitThreadImage,this,&ObjectCamVideo::catchFrame);
    this->threadStreamer->start();
}

void ObjectCamVideo::catchFrame(cv::Mat emittedFrame)
{
    frame = emittedFrame;
}

void ObjectCamVideo::streamerThreadSlot()
{
    while (true) {
        cap->read(frame);

        if(frame.data)
            emit emitThreadImage(frame);

        if(QThread::currentThread()->isInterruptionRequested())
        {
            cap->release();
            return;
        }

    }
}
