#ifndef OBJECTCAMVIDEO_H
#define OBJECTCAMVIDEO_H

#include <QObject>
#include <QThread>
#include <opencv2/core/core.hpp>

class ObjectCamVideo : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCamVideo(QObject *parent = nullptr);

public:


    void streamVideo();
    QThread* threadStreamer = new QThread();
    void catchFrame(cv::Mat emittedFrame);

public slots:
    void openVideoCamera(QString path);
    void streamerThreadSlot();

private:
    cv::Mat frame;

signals:
    void newImage(QImage &);
    void emitThreadImage(cv::Mat frameThread);
};

#endif // OBJECTCAMVIDEO_H
