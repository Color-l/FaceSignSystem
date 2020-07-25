#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QCamera>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include "jasonqt_face.h"
#include <QMainWindow>
//#include <QTcpSocket>
#include <QPixmap>
#include"kaoqin.h"
#include"teacher.h"
#include"loginwidget.h"
#include"info.h"
#include <QLineEdit>
#include<QPushButton>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include<QInputDialog>



namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
#define LOGIN_TYPE               1//登陆
#define REGISTER_TYPE            2//注册
#define LOGIN_SUCCEED       1//登录成功
#define LOGIN_ERROR_NAME    2//用户名错误
#define LOGIN_ERROR_PASSD   3//密码错误
#define LOGIN_ERROR         4//用户名和密码均错误
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_kaoqin_clicked();

    void on_teacher_clicked();

    void on_sure_clicked();

    void on_open_clicked();

    void on_quit_clicked();

    void timerUpdate(void);

    int cameraImageCaptured(int id, QImage image);


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Kaoqin* mf;
    teacher* mff;
    LoginWidget* login;
    info* ma;
    QCamera *m_camera;//系统摄像头设备
    QCameraViewfinder *m_cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *m_cameraImageCapture;//截图部件
    JasonQt_Face *m_BaiduFace; //百度人脸接口

    int   m_ControlType;


};

#endif // MAINWINDOW_H
