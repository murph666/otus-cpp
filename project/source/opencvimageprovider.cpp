#include "opencvimageprovider.h"
#include <iostream>

OpencvImageProvider::OpencvImageProvider(QObject *parent)
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    std::cout <<"OpencvImageProvider constructor: " << this << std::endl;
    image = QImage(500,200,QImage::Format_RGB32);
    image.fill(QColor("yellow"));
}

QImage OpencvImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);
    std::cout <<"OpencvImageProvider requestImage" << std::endl;
    if(size){
        *size = image.size();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }
    return image;
}

void OpencvImageProvider::updateImage(const QImage &image)
{
    std::cout << "image" << std::endl;
    if(!image.isNull() && this->image != image) {
        this->image = image;
        emit imageChanged();
    }
}
