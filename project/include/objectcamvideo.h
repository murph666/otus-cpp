#ifndef OBJECTCAMVIDEO_H
#define OBJECTCAMVIDEO_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "MvCamera.h"


typedef struct _FRAME_AS_ARRAY
{
    unsigned char*      pBufAddr;              ///< \~english  pointer of image
    MV_FRAME_OUT_INFO_EX    stFrameInfo;     ///< \~english information of the specific image
    std::vector<std::vector<int>> aFrame;

    unsigned int        nRes[16];                ///< \~english reserved
}FRAME_AS_ARRAY;

class ObjectCamVideo : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCamVideo(QObject *parent = nullptr);

    void                    openCamera(int *cameraNumber);
    void                    startGrabbing();
    void                    stopGrabbing();


    FRAME_AS_ARRAY            frame;
    QStringList             searchConnectedCameras();

    bool                    m_bGrabbing = false;
    bool                    m_bView = false;
    int                     m_lowLvlOfThreshold = 0;
    int                     m_highLvlOfThreshold = 255;

private:
    QThread                 *threadStreamer = new QThread();
    unsigned char           pData;
    void                    *m_hWnd;
    void                    threshold();
    void                    imgBufToArray();

    MV_CC_DEVICE_INFO_LIST  m_stDevList;
    CMvCamera               *m_pcMyCamera = new CMvCamera();




private slots:
    void streamerThread();

signals:
    void emitImage(const QImage &image);
};

#endif // OBJECTCAMVIDEO_H
