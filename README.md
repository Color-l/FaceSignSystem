# FaceSignSystem
本项目为实习期间做的一款基于百度AI的QT人脸考勤打卡系统

欢迎访问个人博客：https://flblog.top

项目地址：https://flblog.top/13.html

FaceSignSystem

本项目为本人做的一款基于百度AI的人脸识别考勤打卡系统，作者某双非二本院校，写于2020/09/04。

作者	翁飞龙
QQ交流群	692695467(点击跳转)
博客地址	https://www.flblog.top
源码地址	Github    码云
使用环境
支持C++编译器的QT5，Sqlite数据库，本项目在Ubuntu20.04系统下制作完成

准备材料
1、QT5 C/C++
2、Sqlite数据库
3、一台自带摄像头的电脑或者Linux单片机
百度AI接入
接入步骤

1、注册百度账号，用来登录百度AI开发平台（https://ai.baidu.com/），有账号的可以直接登录
2、注册成为开发者
3、创建应用，应用创建成功之后也就开通了人脸检测、人脸比对等等相关业务
4、获取密钥，AppID、API Key和Secret key
5、生成签名（Access Token），这个写代码的时候要用到，每个应用的Access Token有效期为30天，到期后要重新获取，或者是在写代码时每次都获取一下
百度AI开放平台上有详细的接入指南：https://ai.baidu.com/docs#/Begin/top

一、项目结构


二、核心源码
1.网络编程

这里使用了QtNetwork模块中的网络接口来实现http编程，需要在.pro文件中添加 QT += network，主要用到了下面三个类：

1、QNetworkAccessManager：该类允许应用程序发送网络请求和接收回复，类似于一个中转站或者一个容器，每当有请求创建或者接收到回复都由该类进行调度

2、QNetworkRequest：网络请求

3、QNetworkReply：网络请求的应答，在请求被完成调度是由QNetworkAccessManager创建

get、put、post请求方式的区别

1、GET请求（类似于数据库select操作），会向数据库发送数据的请求，从而来获取信息，不会改变数据内容，并且无论进行多少次操作，结果都是一样的

2、PUT请求（类似于数据库update操作），是会向服务器端发送数据的，会修改数据的内容，但是不会增加数据的种类，并且无论进行多少次操作，结果都是一样的

3、POST请求（类似于数据库insert操作），是会向服务器端发送数据的，但是该请求会改变数据的种类等资源，会创建新的内容

POST 提交数据方式

application/x-www-form-urlencoded
multipart/form-data
application/json
text/xml

百度AI使用application/json方式提交数据

2.获取Token
向授权服务地址https://aip.baidubce.com/oauth/2.0/token发送请求（推荐使用POST），并在URL中带上以下参数：

grant_type： 必须参数，固定为client_credentials；
client_id： 必须参数，应用的API Key；
client_secret： 必须参数，应用的Secret Key；

自动获取Token

bool JasonQt_Face::refreshToken(void)//自动获取token
{
    QNetworkRequest request(QUrl(QString("https://aip.baidubce.com/oauth/2.0/token?")));//api接口
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

3.图片Base64编码
1、提取图片
2、数据转换为BASE64编码
实现代码

QByteArray ba;
QBuffer buf(&ba);
image.save(&buf, "png");
QString imgData = QString(ba.toBase64());
buf.close();
全选代码复制
4.JSON数据解析
数据上传

bool JasonQt_Face::RegisterMember(QString qstrImage,QString UserId)//人脸注册
{
    //设置请求地址
    QUrl url("https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/add?access_token="+m_token);
    QNetworkRequest request(url);
    QJsonObject append;
    m_UserId = UserId;
    //设置数据提交格式
    request.setRawHeader("Content-Type", "aspplication/json");
    append["face_token"] = m_token;
    append["image"] = qstrImage;//face dat
    append["image_type"] = "BASE64";
    append["group_id"] = "Color";//member owner
    append["user_id"] =UserId;
   // append["quality_control"]="NORMAL";
    QByteArray buf;
    //发送请求
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

人脸库搜索

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

数据解析

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


三、运行效果展示
见：https://flblog.top/13.html
