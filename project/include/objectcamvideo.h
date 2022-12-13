#ifndef OBJECTCAMVIDEO_H
#define OBJECTCAMVIDEO_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class ObjectCamVideo : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCamVideo(QObject *parent = nullptr);

public slots:
    void openCamera();

private:
    cv::Mat frame;
    cv::VideoCapture *cap       = new cv::VideoCapture;
    QThread* threadStreamer     = new QThread();

private slots:
    void streamerThread();

signals:
    void emitImage(QImage &);
};

#endif // OBJECTCAMVIDEO_H
