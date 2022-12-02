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
    MainWindow backend;
    const QUrl url(u"/home/murph/Documents/GitHub/otus-cpp/project/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext() -> setContextProperty("connectedDeviceModel", &backend.listOfCameras);
    engine.load(url);

    QObject* item = (QObject*)engine.rootObjects().at(0);
    //Сигнал с кнопки поиска
    QObject::connect(item, SIGNAL(btnSearchClicked()),
                     &backend, SLOT(on_bnSearchClicked()));
    //Сигнал с лайнэдита
    QObject::connect(item, SIGNAL(textFieldEditingFinished(QString)),
                     &backend.listOfCameras, SLOT(addElement(QString)));
    //Сигнал с комбобокса
    QObject::connect(item, SIGNAL(cboxAccepted(int)),
                     &backend, SLOT(on_cboxAccepted(int)));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
