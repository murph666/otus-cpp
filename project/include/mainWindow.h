#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QQmlApplicationEngine>
#include <QMessageBox>
#include <iostream>

#include "modelforlistofcameras.h"
#include "comboboxmodel.h"
#include "objectcamvideo.h"
#include "opencvimageprovider.h"


struct CameraItem
{
    int number;
    QString partName;
    int status;

};

class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QQmlApplicationEngine *engine = nullptr,
                        ObjectCamVideo *camera = nullptr,
                        OpencvImageProvider *liveImageProvider = nullptr,
                        ComboBoxModel *listOfCameras = nullptr
                        );
    QVector<CameraItem> items();


    //слоты для QML
private slots:
    void on_btnSearchClicked();
    void on_btnConnectClicked();
    void on_btnGrabbingClicked();
    void on_swchViewToggled(bool);
    void on_cboxAccepted(int count);
    void on_firstHandleOfThresholdSliderChanged(int value);
    void on_secondHandleOfThresholdSliderChanged(int value);

private:
    QQmlApplicationEngine   *engine;
    ObjectCamVideo          *camera;
    OpencvImageProvider     *liveImageProvider;
    ComboBoxModel           *listOfCameras;
    QVector<CameraItem>     m_listOfCameras;

    int                     currentIndexOfComboBox = 0;

    //для всплывающего окна с ошибкой/предупреждением
    void ShowErrorMsg(QString csMessage, int nErrorNum);
    void ConnectSignals();

};

#endif // MAINWINDOW_H
