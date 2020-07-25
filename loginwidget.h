#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
/**************************************
*@projectName   LoginWidget
*@brief         登录界面设计
*@date          2020-07-8
*@author        杨英凡
*@version       V0.1
*****************************************/
namespace Ui {
class LoginWidget;
}
#define LOGIN_SUCCEED       1//登录成功
#define LOGIN_ERROR_NAME    2//用户名错误
#define LOGIN_ERROR_PASSD   3//密码错误
#define LOGIN_ERROR         4//用户名和密码均错误
class LoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    int GetLoginInfo();
private slots:
    void OnOKBtn();
    void OnCancelBtn();

private:
    Ui::LoginWidget *ui;
    QString m_UserName;
    QString m_PassWord;
    int  m_LoginInfo;
};

#endif // LOGINWIDGET_H
