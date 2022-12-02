#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "MvCamera.h"

#include <QtCore>
#include <QQmlApplicationEngine>

#include "comboboxmodel.h"


class MainWindow : public QObject
{
    Q_OBJECT

public:
//    void static __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
//    void ImageCallBackInner(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInf);

    ComboBoxModel listOfCameras; //модель для comboConnectedDevice
private:
    void ShowErrorMsg(QString csMessage, int nErrorNum);

    void OpenCamera();

private slots:
    void on_bnSearchClicked();

    void on_tfEditingFinished(const QString &msg);

    void on_cboxAccepted(const int &count);


private:
    void                    *m_hWnd;
//    MV_CC_DEVICE_INFO_LIST  m_stDevList;
//    CMvCamera*              m_pcMyCamera;
    bool                    m_bGrabbing;

    QQmlApplicationEngine*  engine;
};

#endif // MAINWINDOW_H
