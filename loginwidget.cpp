#include "loginwidget.h"
#include "ui_loginwidget.h"
/**************************************
*@brief         LoginWidget 登录构造函数
*@param         QWidget *parent父窗口指针
*@return        无
*@author        孔令辉
*@date          2020-07-09
*****************************************/
LoginWidget::LoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    m_UserName ="123";
    m_PassWord = "123";
    m_LoginInfo= LOGIN_ERROR;
    connect(this,SIGNAL(accepted()),this,SLOT(OnOKBtn()));
    connect(this,SIGNAL(rejected()),this,SLOT(OnCancelBtn()));
}
/**************************************
*@brief         GetLoginInfo获取登录信息
*@param         无
*@return        int登录结果
*@author        孔令辉
*@date          2020-07-09
*****************************************/
int LoginWidget::GetLoginInfo()
{
    return m_LoginInfo;
}
/**************************************
*@brief         OnOKBtn 接受按钮相应函数
*@param         无
*@return        无
*@author        孔令辉
*@date          2020-07-09
*****************************************/
void LoginWidget::OnOKBtn()
{
    QString qstrUserName=ui->UserEdt->text();
    QString qstrPassWord=ui->PassWordEdt->text();
    if((qstrUserName==m_UserName)&&(qstrPassWord==m_PassWord))
    {
        m_LoginInfo= LOGIN_SUCCEED;
    }
    else if((qstrUserName!=m_UserName)&&(qstrPassWord!=m_PassWord))
    {
         m_LoginInfo= LOGIN_ERROR;
    }
    else if(qstrUserName!=m_UserName)
    {
        m_LoginInfo= LOGIN_ERROR_NAME;
    }
    else
    {
         m_LoginInfo= LOGIN_ERROR_PASSD;
    }
}
/**************************************
*@brief         OnCancelBtn 取消按钮相应函数
*@param         无
*@return        无
*@author        孔令辉
*@date          2020-07-09
*****************************************/
void LoginWidget::OnCancelBtn()
{
    //nothing to do
}
LoginWidget::~LoginWidget()
{
    delete ui;
}


