/**************************************
*@projectName   JasonQt_Net
*@brief         链接百度ai相关函数封装
*@date          2020-07-08
*@author        翁飞龙
*@version       V0.1
*****************************************/
#ifndef __JasonQt_Net_h__
#define __JasonQt_Net_h__

// Qt lib import
#include <QUrl>
#include <QString>
#include <QByteArray>
#include <QEventLoop>
#include <QTimer>

#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

namespace JasonQt_Net
{

QNetworkAddressEntry getNetworkAddressEntry(void);

QString getDeviceName(void);

class HTTP: public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager m_manage;
    QNetworkReply *m_reply = nullptr;
    QTimer m_timer;

public:
    HTTP(void);

public slots:
    void get(const QUrl &url, const int &maxTime = 30000);

    void post(const QNetworkRequest &networkRequest, const QByteArray &append, const int &maxTime = 30000);

    void stop(void);

    bool get(const QUrl &url, QByteArray &target, const int &maxTime = 30000);

    bool post(const QNetworkRequest &networkRequest, const QByteArray &append, QByteArray &target, const int &maxTime = 30000);

private slots:
    void onFinished(QNetworkReply *reply);

    void onTimeout(void);

    void onError(const QNetworkReply::NetworkError &error);

signals:
    void finished(const QByteArray data);

    void error(const QNetworkReply::NetworkError error);
};

}

#endif//__JasonQt_Net_h__
