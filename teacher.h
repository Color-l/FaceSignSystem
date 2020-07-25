#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include"info.h"

namespace Ui {
class teacher;
}

class teacher : public QWidget
{
    Q_OBJECT

public:
    explicit teacher(QWidget *parent = 0);
    ~teacher();

private slots:
    void on_return_2_clicked();


    void on_addinfo_clicked();

    void on_delinfo_clicked();

    void on_reflash_clicked();

signals:
    void mysig();

private:
    Ui::teacher *ui;
    info* ma;
};

#endif // TEACHER_H
