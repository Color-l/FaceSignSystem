#include "kaoqin.h"
#include"mainwindow.h"
#include "ui_kaoqin.h"
#include <QSqlTableModel>

Kaoqin::Kaoqin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kaoqin)
{

    ui->setupUi(this);
    ui->studaka->setColumnWidth(4,200);
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
    QString sql = QString("SELECT * FROM student ");
    query.exec(sql);
    QString id;
    QString name;
    QString class_2;
    QString school;
    ui->studaka->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->studaka->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->studaka->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int cow=0;
    while(query.next()){
        for(int row=0;row<5;row++){
            ui->studaka->setItem(cow,row,new QTableWidgetItem(query.value(row).toString()));
        }
        cow++;
    }
    database.close();
}

Kaoqin::~Kaoqin()
{
    delete ui;
}

void Kaoqin::on_return_2_clicked()
{
    this->hide();
    emit mysig();
}
