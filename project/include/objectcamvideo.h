#ifndef OBJECTCAMVIDEO_H
#define OBJECTCAMVIDEO_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "MvCamera.h"

class ObjectCamVideo : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCamVideo(QObject *parent = nullptr);

    void __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo);
    void ImageCallBackInner(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInf);

    QStringList             searchConnectedCameras();
    void                    openCamera(int *cameraNumber);
    void                    startGrabbing();
    void                    stopGrabbing();

    bool                    m_bGrabbing = false;

private:
    //    cv::Mat frame;
    //    cv::VideoCapture *cap       = new cv::VideoCapture;
    QThread                 *threadStreamer = new QThread();
    void                    *m_hWnd;

    MV_CC_DEVICE_INFO_LIST  m_stDevList;
    CMvCamera               *m_pcMyCamera = new CMvCamera();



private slots:
    void streamerThread();

signals:
    void emitImage(const QImage &image);
};

#endif // OBJECTCAMVIDEO_H
