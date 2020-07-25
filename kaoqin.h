#ifndef KAOQIN_H
#define KAOQIN_H

#include <QWidget>

namespace Ui {
class Kaoqin;
}

class Kaoqin : public QWidget
{
    Q_OBJECT

public:
    explicit Kaoqin(QWidget *parent = 0);
    ~Kaoqin();

signals:
    void mysig();

private slots:
    void on_return_2_clicked();

private:
    Ui::Kaoqin *ui;
};

#endif // KAOQIN_H
