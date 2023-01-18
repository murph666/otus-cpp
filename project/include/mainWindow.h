#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QQmlApplicationEngine>
#include <QMessageBox>
#include <iostream>

#include "modelforlistofcameras.h"
//#include "comboboxmodel.h"
//#include "objectcamvideo.h"
#include "opencvimageprovider.h"
#include "MvCamera.h"


class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QQmlApplicationEngine *engine = nullptr,
                        OpencvImageProvider *liveImageProvider = nullptr,
                        ModelForListOfCameras *modelForListOfCameras = nullptr
            );



    //слоты для QML
private slots:
    void on_btnSearchClicked();
    void on_btnConnectClicked();
//    void on_btnGrabbingClicked();
//    void on_swchViewToggled(bool);
//    void on_cboxAccepted(int count);
//    void on_firstHandleOfThresholdSliderChanged(int value);
//    void on_secondHandleOfThresholdSliderChanged(int value);

private:
    QQmlApplicationEngine   *engine;
    OpencvImageProvider     *liveImageProvider;
    ModelForListOfCameras   *modelForListOfCameras;

    MV_CC_DEVICE_INFO_LIST  m_stDevList;

    //для всплывающего окна с ошибкой/предупреждением
    void ShowErrorMsg(QString csMessage, int nErrorNum);
    void ConnectSignals();
};

#endif // MAINWINDOW_H
