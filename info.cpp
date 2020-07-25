#include "info.h"
#include "ui_info.h"
#include"mainwindow.h"
info::info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    ui->school->setPlaceholderText("请输入学院全称");
    ui->class_2->setPlaceholderText("例：计算机1702");
    ui->number->setPlaceholderText("请输入学号");
    ui->name->setPlaceholderText("请输入姓名");
    //ui->photo->setPlaceholderText("请选择头像");
    //ui->photo->setReadOnly(false);
   // ui->photo->setEnabled(false);

}

info::~info()
{
    delete ui;
}

void info::on_exit_clicked()
{
    this->hide();
    emit mysig();
}

void info::on_ok_clicked()
{


    //建立并打开数据库
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
            ui->listWidget->addItem(tr("Error: Failed to connect database..."));

        }
        else
        {
            qDebug() << "Succeed to connect database..." ;
            ui->listWidget->addItem(tr("Succeed to connect database..."));

        }

        //创建表格
        QSqlQuery sql_query;


              if(!sql_query.exec("create table IF NOT EXISTS  student(id int primary key, name varchar(20), class_2 int, school varchar(20),time Text)"))
            {
                qDebug() << "Error: Fail to create table."<< sql_query.lastError();
                ui->listWidget->addItem(tr("Error: Fail to create student table."));
            }
            else
            {
                qDebug() << "student Table created!";
                ui->listWidget->addItem(tr("student Table created Success!"));
            }

            QDateTime time = QDateTime::currentDateTime();
            QString str = time.toString("yyyy-MM-dd hh:mm");
            QString arg[5]={ui->number->text(),ui->name->text(),ui->class_2->text(),ui->school->text(),str};

            QSqlQuery query;
            QString sql = QString("insert into student values ('%1','%2','%3','%4','%5')").arg(arg[0]).arg(arg[1]).arg(arg[2]).arg(arg[3]).arg(arg[4]);

            query.prepare(sql);
            if(!query.exec(sql)){
                qDebug() << "Database inserted Failed！"<< sql_query.lastError();
                ui->listWidget->addItem(tr("Database inserted Failed！"));

                 database.close();

            }
            else{
                qDebug() << "Database inserted successfully！";
                ui->listWidget->addItem(tr("Database inserted successfully"));
                database.close();

            }
}



/*void info::on_pushButton_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"选择文件","/", "Files(*.png *jpg)");
    ui->photo->setText(s);
}*/
