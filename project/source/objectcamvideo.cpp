#include "objectcamvideo.h"
#include <iostream>

ObjectCamVideo::ObjectCamVideo(QObject *parent)
    : QObject{parent}
{
    std::cout <<"ObjectCamVideo constructor: "<< this << std::endl;
}

void ObjectCamVideo::openCamera(){
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;
    this->cap->open(deviceID, apiID);
    if (!cap->isOpened()) {
        std::cout << "ERROR! Unable to open camera\n" << std::endl;
    }
    this -> moveToThread(threadStreamer);
    QObject::connect(threadStreamer, SIGNAL(started()), this, SLOT(streamerThread()));
    this->threadStreamer->start();
}

void ObjectCamVideo::streamerThread()
{
    while (true) {
        cap->read(frame);
        if(frame.data){
            std::cout <<"emit"<< std::endl;
            QImage img = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
            emit emitImage(img);
        }
        if(QThread::currentThread()->isInterruptionRequested())
        {
            cap->release();
            return;
        }

    }
}
