#ifndef JASONQT_FACE_H
#define JASONQT_FACE_H
#include<QString>
#include<QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QBuffer>
#include "JasonQt_Net.h"
class JasonQt_Face :public QObject
{
    Q_OBJECT
public:
    JasonQt_Face(const QString &apiKey, const QString &secretKey);//返回相似度
    bool RegisterMember(QString qstrImage,QString UserId);//注册人脸
    int Identifyface(QString qstrImage);//比对人脸
private:
    //baidu.ai的 FACE相关key
    QString m_apiKey;
    QString m_secretKey;
    QString m_token;
    QByteArray m_buf;
    JasonQt_Net::HTTP m_http;
    QString m_UserId;
    double m_dThresholdValue; //人脸识别阈值
public slots:
    bool refreshToken(void);//更新Token
};

#endif // JASONQT_FACE_H
