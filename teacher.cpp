#include "teacher.h"
#include "ui_teacher.h"
#include "mainwindow.h"

teacher::teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacher)
{
    ui->setupUi(this);
    ma = new info();
        connect(ma,SIGNAL(mysig()),this,SLOT(show()));

}

teacher::~teacher()
{
    delete ui;
}


void teacher::on_return_2_clicked()
{
    this->hide();
    emit mysig();
}

void teacher::on_addinfo_clicked()
{
    this->hide();
    ma->show();
}

void teacher::on_delinfo_clicked()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("User_Id"),tr("请输入学号"), QLineEdit::Password,0, &ok);

        if(text.isEmpty()){
            QMessageBox::information(NULL, "错误", "请输入正确的学号！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
            //text = QInputDialog::getText(this, tr("User_Id"),tr("请输入学号"), QLineEdit::Password,0, &ok);


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
    QString sql = QString("DELETE FROM student WHERE id = '%1'").arg(text);
    query.prepare( sql);
      if( !query.exec() )
        qDebug() << "删除数据失败！"<< query.lastError();
      else
        qDebug( "Deleted Success!" );
      database.close();
}

void teacher::on_reflash_clicked()
{
    for(int cow=0;cow<40;cow++){
    for(int row=0;row<4;row++){
        ui->student->setItem(cow,row,new QTableWidgetItem(nullptr));
    }
    }

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
    ui->student->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->student->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->student->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int cow=0;
    while(query.next()){
        for(int row=0;row<4;row++){
            ui->student->setItem(cow,row,new QTableWidgetItem(query.value(row).toString()));
        }
        cow++;
    }
    database.close();
}
