#include "mainwindow.h"
#include "ui_mainwindow.h"
static int tmp=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mf = new Kaoqin();
    mff = new teacher();
    ma = new info();
        connect(mf,SIGNAL(mysig()),this,SLOT(show()));
        connect(mff,SIGNAL(mysig()),this,SLOT(show()));
        connect(ma,SIGNAL(mysig()),this,SLOT(show()));
        m_BaiduFace = new JasonQt_Face("qqnMw0WtZXAagB5F0Bojcecq", "zmr2zGUURpWFYHexS4LMIoDGoH0BuLqp");
        m_BaiduFace->refreshToken();
        m_camera = new QCamera(this);//系统摄像头设备
        m_cameraViewFinder = new QCameraViewfinder(this);//摄像头取景器部件
        m_cameraImageCapture = new QCameraImageCapture(m_camera);//截图部件
        ui->tupian->addWidget(m_cameraViewFinder);
        connect(m_cameraImageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(cameraImageCaptured(int,QImage)));
        m_cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        m_camera->setCaptureMode(QCamera::CaptureStillImage);
        m_camera->setViewfinder(m_cameraViewFinder);
        m_camera->start();//启动摄像头
        m_ControlType = LOGIN_TYPE;
        QTimer *timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
        timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::cameraImageCaptured(int index, QImage image)
{
    if(index>=0)
    {
        QByteArray ba;
        QBuffer buf(&ba);
        image.save(&buf, "png");
        QString imgData = QString(ba.toBase64());
        buf.close();
        if (m_ControlType==REGISTER_TYPE)   //注册人脸的情况
        {
            //QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
           // QString str = time.toString("yyyyMMddhhmmss"); //设置显示格式
            bool ok;
                QString text = QInputDialog::getText(this, tr("User_Id"),tr("请输入学号"), QLineEdit::Password,0, &ok);
                while(text.isEmpty())
                {
                    QMessageBox::information(NULL, "错误", "请输入正确的学号！",
                                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    text = QInputDialog::getText(this, tr("User_Id"),tr("请输入学号"), QLineEdit::Password,0, &ok);

                }
            if(m_BaiduFace->RegisterMember(imgData, text))
            {
                qDebug() << "人脸信息录入成功";
                QMessageBox::information(NULL, "完成", "您的人脸信息已经录入！请录入其他信息！",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

                this->hide();
                ma->show();

            }
            else
            {
                qDebug() << "人脸信息录入失败";
                QMessageBox::information(NULL, "错误", "请检查您的网络或与管理员联系！",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);


            }

        }
        else if(m_ControlType==LOGIN_TYPE)
        {
            int success = m_BaiduFace->Identifyface(imgData);
            tmp=success;
            if (!success)
            {
                qDebug() << "比对失败";
                QMessageBox::information(NULL, "错误", "打卡失败，人脸信息不匹配或人脸库中查无此人，请重新打卡！",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);


             }
            else
            {

                //打开数据库
                QSqlDatabase database;
                if (QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    database = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    database = QSqlDatabase::addDatabase("QSQLITE");
                    database.setDatabaseName("MyDataBase.db");
                    database.setUserName("123456");
                    database.setPassword("123456");
                }

                    if (!database.open())
                    {
                        qDebug() << "Error: Failed to connect database..." << database.lastError();

                    }
                    else
                    {
                        qDebug() << "Succeed to connect database..." ;

                    }
                QSqlQuery query;
                QString sql = QString("SELECT * FROM student WHERE id='%1'").arg(success);
                query.exec(sql);
                while(query.next())
                    {
                        QString id = query.value(0).toString();
                        QString name = query.value(1).toString();
                        QString class_2 = query.value(2).toString();
                        QString school = query.value(3).toString();
                        QString time = query.value(4).toString();
                        qDebug()<<id<<name<<class_2<<school<<time;
                        ui->number->setText(id);
                        ui->name->setText(name);
                        ui->class_2->setText(class_2);
                        ui->school->setText(school);
                        ui->time->setText(time);
                    }
                qDebug() << "比对成功";
                QMessageBox::information(NULL, "完成", "打卡成功！",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

                database.close();
                m_camera->stop();
            }
        }
    }
}

void MainWindow::on_sure_clicked()
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("123456");
        database.setPassword("123456");
    }

        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database..." << database.lastError();

        }
        else
        {
            qDebug() << "Succeed to connect database..." ;

        }
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm");
    QSqlQuery query;
    QString sql = QString( "UPDATE student SET time = '%1' WHERE id = '%2'" ).arg(str).arg(tmp);
    query.prepare(sql);
     if( !query.exec() )
       qDebug() << "打卡时间更新失败！"<<query.lastError();
     else
       qDebug( "打卡时间更新成功" );
     database.close();
    m_ControlType=LOGIN_TYPE;
    m_cameraImageCapture->capture();
    qDebug() << "正在进行人脸比对.";
}

void MainWindow::on_pushButton_clicked()
{
    m_ControlType=REGISTER_TYPE;
    m_cameraImageCapture->capture();
    //开始注册人脸信息
    qDebug() << "开始注册人脸信息库！.";
}
void MainWindow::on_kaoqin_clicked()
{
    this->hide();
    mf->show();
}

void MainWindow::on_teacher_clicked()
{
    this->hide();
    login = new LoginWidget(nullptr);
        login->exec();
        int result = login->GetLoginInfo();
           while(result!=LOGIN_SUCCEED){
               QMessageBox::information(NULL, "错误", "管理员密码错误，请重新输入",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
               login->exec();
               result = login->GetLoginInfo();
           }
           mff->show();
}

void MainWindow::on_open_clicked()
{
    m_camera = new QCamera(this);//系统摄像头设备
    m_cameraViewFinder = new QCameraViewfinder(this);//摄像头取景器部件
    m_cameraImageCapture = new QCameraImageCapture(m_camera);//截图部件
    ui->tupian->addWidget(m_cameraViewFinder);
    connect(m_cameraImageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(cameraImageCaptured(int,QImage)));
    m_cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    m_camera->setViewfinder(m_cameraViewFinder);
    m_camera->start();//启动摄像头
    m_ControlType = LOGIN_TYPE;

}



void MainWindow::on_quit_clicked()
{
    this->close();

}

void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->datalable->setText(str);
}

