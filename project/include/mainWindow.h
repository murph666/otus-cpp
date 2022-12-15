#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QQmlApplicationEngine>
#include <QMessageBox>
#include <iostream>

#include "comboboxmodel.h"
#include "objectcamvideo.h"
#include "opencvimageprovider.h"


class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QQmlApplicationEngine *engine = nullptr,
                        ObjectCamVideo *camera = nullptr,
                        OpencvImageProvider *liveImageProvider = nullptr,
                        ComboBoxModel *listOfCameras = nullptr);



    //слоты для QML
private slots:
    void on_btnSearchClicked();
    void on_btnConnectClicked();
    void on_cboxAccepted(int count);

private:
    QQmlApplicationEngine   *engine;
    ObjectCamVideo          *camera;
    OpencvImageProvider     *liveImageProvider;
    ComboBoxModel           *listOfCameras;

    //для всплывающего окна с ошибкой/предупреждением
    void ShowErrorMsg(QString csMessage, int nErrorNum);
    void ConnectSignals();

};

#endif // MAINWINDOW_H
