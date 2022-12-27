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

    void                    openCamera(int *cameraNumber);
    void                    startGrabbing();
    void                    stopGrabbing();


    MV_FRAME_OUT            frame;
    QStringList             searchConnectedCameras();

    bool                    m_bGrabbing = false;
    int                     lowLvlOfThreshold = 0;
    int                     highLvlOfThreshold = 255;

private:
    QThread                 *threadStreamer = new QThread();
    unsigned char           pData;
    void                    *m_hWnd;
    void                    threshold();

    MV_CC_DEVICE_INFO_LIST  m_stDevList;
    CMvCamera               *m_pcMyCamera = new CMvCamera();




private slots:
    void streamerThread();

signals:
    void emitImage(const QImage &image);
};

#endif // OBJECTCAMVIDEO_H
