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

    QStringList             searchConnectedCameras();
    void openCamera();

private:
    //    cv::Mat frame;
    //    cv::VideoCapture *cap       = new cv::VideoCapture;
    QThread                 *threadStreamer= new QThread();
    void                    *m_hWnd;

    MV_CC_DEVICE_INFO_LIST  m_stDevList;
    CMvCamera               *m_pcMyCamera;
    bool                    m_bGrabbing;



private slots:
    void streamerThread();

signals:
    void emitImage(const QImage &image);
};

#endif // OBJECTCAMVIDEO_H
