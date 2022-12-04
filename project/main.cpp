#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QtWidgets>
#include <QQmlContext>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    std::cout <<"main engine: " << &engine << std::endl;

    const QUrl url(u"/home/murph/Documents/GitHub/otus-cpp/project/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //    переопределяю combobox на объект ComboBoxModel который объявляю в header MainWindow.
//    engine.rootContext() -> setContextProperty("connectedDeviceModel", &backend.listOfCameras);
    engine.load(url);

    MainWindow backend(&engine);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
