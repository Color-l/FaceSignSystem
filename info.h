#ifndef INFO_H
#define INFO_H

#include <QWidget>

#include <QMessageBox>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include "jasonqt_face.h"

namespace Ui {
class info;
}

class info : public QWidget
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
    ~info();

signals:
    void mysig();

private slots:

    void on_exit_clicked();

    void on_ok_clicked();

private:
    Ui::info *ui;
    QCamera *m_camera;//系统摄像头设备
    QCameraViewfinder *m_cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *m_cameraImageCapture;//截图部件
    JasonQt_Face *m_BaiduFace; //百度人脸接口

    int   m_ControlType;

};

#endif // INFO_H
