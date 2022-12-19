#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QtWidgets>
#include <QQmlContext>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "mainWindow.h"
#include "comboboxmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ObjectCamVideo camera;
    OpencvImageProvider liveImageProvider;
    ComboBoxModel listOfCameras; //объект модель для comboConnectedDevice

    const QUrl url(u"/home/murph/Documents/GitHub/otus-cpp/project/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //переопределяю qml на объекты cpp
    engine.rootContext() -> setContextProperty("connectedDeviceModel", &listOfCameras);
    engine.rootContext() -> setContextProperty("liveImageProvider", &liveImageProvider);
    engine.addImageProvider("stream", &liveImageProvider);

    engine.load(url);
    MainWindow backend(&engine, &camera, &liveImageProvider, &listOfCameras);

    if (engine.rootObjects().isEmpty())
        return -1;
    auto e = app.exec();

    return e;


}
