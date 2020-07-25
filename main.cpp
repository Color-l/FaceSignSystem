#include "mainwindow.h"
#include <QApplication>
//#include <QTcpSocket>

int main(int argc, char *argv[])
{
    int m=0;//记录签到人数
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
