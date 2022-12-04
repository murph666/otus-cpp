#ifndef OBJECTCAMVIDEO_H
#define OBJECTCAMVIDEO_H

#include <QObject>
#include <QThread>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class ObjectCamVideo : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCamVideo(QObject *parent = nullptr);

    QThread* threadStreamer = new QThread();
    void catchFrame(cv::Mat emittedFrame);

public slots:
    void openCamera();
    void streamerThreadSlot();

private:
    cv::Mat frame;
    cv::VideoCapture *cap = new cv::VideoCapture;

signals:
    void newImage(QImage &);
    void emitThreadImage(cv::Mat frameThread);
};

#endif // OBJECTCAMVIDEO_H
