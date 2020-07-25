#include "jasonqt_face.h"
/**************************************
*@brief         摘要
*@param         无
*@return        无
*@author        翁飞龙
*@date          2020-07-08
*****************************************/
JasonQt_Face::JasonQt_Face(const QString &apiKey, const QString &secretKey):
    m_apiKey(apiKey),m_secretKey(secretKey),m_dThresholdValue(80.1)//默认为80分以上通过
{

}
bool JasonQt_Face::RegisterMember(QString qstrImage,QString UserId)//人脸注册
{
    QUrl url("https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/add?access_token="+m_token);
    QNetworkRequest request(url);
    QJsonObject append;
    m_UserId = UserId;
    request.setRawHeader("Content-Type", "aspplication/json");
    append["face_token"] = m_token;
    append["image"] = qstrImage;//face dat
    append["image_type"] = "BASE64";
    append["group_id"] = "Color";//member owner
    append["user_id"] =UserId;
   // append["quality_control"]="NORMAL";
    QByteArray buf;
    m_http.post(request, QJsonDocument(append).toJson(), buf, 15000);
    QJsonObject acceptedData(QJsonDocument::fromJson(buf).object());
    if(buf.isEmpty() || acceptedData.isEmpty() || !acceptedData.contains("result"))
    {
        return false;
    }
    else
    {
        return true;
    }
}
int  JasonQt_Face::Identifyface(QString qstrImage)//人脸搜索
{
    QUrl url("https://aip.baidubce.com/rest/2.0/face/v3/search?access_token="+m_token);
    QNetworkRequest request(url);
    QJsonObject append;
    request.setRawHeader("Content-Type", "aspplication/json");
    append["image"] = qstrImage;//face dat
    append["image_type"]="BASE64";
    append["group_id_list"] = "Color";
    //append["quality_control"]="NORMAL";
    QByteArray buf;
    m_http.post(request, QJsonDocument(append).toJson(), buf, 15000);
    QJsonObject acceptedData(QJsonDocument::fromJson(buf).object());
    if(buf.isEmpty() || acceptedData.isEmpty() || !acceptedData.contains("result"))
    {
        return false;
    }
    QJsonObject result=acceptedData.take("result").toObject();
    if(result.contains("user_list"))
    {
        QJsonArray user_list =  result.take("user_list").toArray();
        QJsonObject userObj = user_list.at(0).toObject();
        double score = userObj["score"].toDouble();
        QString user_id=userObj["user_id"].toString();
        int tmp=user_id.toInt();
        if(score>=m_dThresholdValue)
            return tmp;
        else
            return false;
    }
    return false;
}
bool JasonQt_Face::refreshToken(void)//自动获取token
{
    QNetworkRequest request(QUrl(QString("https://aip.baidubce.com/oauth/2.0/token?")));
    QByteArray append = QString("grant_type=client_credentials&client_id=%1&client_secret=%2").arg(m_apiKey).arg(m_secretKey).toUtf8();
    QByteArray buf;

    request.setRawHeader("Content-Type", "application/json");
    //超时为15000ms
    const auto &&flag = m_http.post(request, append, buf, 15000);
    if(!flag) { return false; }

    const auto &&data = QJsonDocument::fromJson(buf).object();
    if(data.isEmpty() || !data.contains("access_token")) { return false; }

    m_token = data["access_token"].toString();
    return true;
}
