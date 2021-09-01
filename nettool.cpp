#include "nettool.h"

NetTool::NetTool(QObject *parent) : QObject(parent){
    manager = new QNetworkAccessManager(this);
}

NetTool::~NetTool(){
}

int NetTool::httpRequest(const QUrl&requestUrl, httpReply_t *httpReply){
    QNetworkRequest request;
    QNetworkReply *reply;
    QVariant statusCode;
    QEventLoop eventLoop;
    QTimer timer;

    // https需要的配置（http不需要）
    //QSslConfiguration sslConf = request.sslConfiguration();
    //sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    //sslConf.setProtocol(QSsl::TlsV1SslV3);
    //request.setSslConfiguration(sslConf);

    //填充request
    request.setUrl(requestUrl);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");

    //建立循环收取reply
    reply = manager->get(request);
    connect(manager,&QNetworkAccessManager::finished, &eventLoop,&QEventLoop::quit);
    connect(&timer,SIGNAL(timeout()), &eventLoop,SLOT(quit()));
    timer.start(30 * 1000);
    eventLoop.exec();

    //超时操作
    if(timer.isActive()){
        timer.stop();
    }else{
        disconnect(reply,SIGNAL(finished()), &eventLoop, SLOT(quit()));
        reply->abort();
        reply->deleteLater();
        return -1;
    }

    // 判断reply有没有错误
    if (reply->error()){
      qDebug()<<reply->errorString();
      reply->deleteLater();
      return -1;
    }

    QByteArray bytes = reply->readAll();
    httpReply->response = bytes;
    //获取状态码
    statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()){
        httpReply->httpCode = statusCode.toInt();
        qDebug() << "recv finished: " << statusCode.toInt();
    }

    httpReply->httpCode = statusCode.toInt();
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "recv data: " << httpReply->httpCode;
    } else {
        qDebug() << "reply error: " << reply->error();
    }

    if (reply != NULL) {
        disconnect(reply, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
        reply->abort();
        reply->deleteLater();
    }

    return httpReply->httpCode;

}

bool NetTool::loadJson(const QUrl &requestUrl, QStringList *Routelist){
    httpReply_t reply;
    int retCode = 0;

    retCode = httpRequest(requestUrl, &reply);
    qDebug() << "Send finished response: " << retCode;
    QByteArray str = reply.response;
    //qDebug()<<"下面是reply.response:"<<"\n"<<reply.response;
    if (str.isEmpty()){
            qDebug()<<"replystring is empty!";
        }
    // 解析Json字符串
    QJsonParseError error;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(str, &error);
    //qDebug()<<"下面是jsondoc:"<<"\n"<<JsonDoc;

    // 字符串没有错误
    if (!JsonDoc.isEmpty() && (error.error == QJsonParseError::NoError)) {
        // 转为Json对象
        const QJsonObject JsonObj = JsonDoc.object();
        QJsonObject data = JsonObj.value("data").toObject();
        // 迭代获得route词典
        QJsonObject::iterator it;
        for(it=data.begin();it!=data.end();it++){
            QJsonObject item = it.value().toObject();
            QJsonArray routes = item.value("routes").toArray();
            for(int i = 0; i < routes.count(); i++){
                QJsonValue value = routes.at(i);
                Routelist->append(value.toString().remove(0,1));
            }
        }
        return true;
    }else {
        qDebug()<<"JsonDoc translate error";
        return false;
    }
}

void NetTool::loadXml(const QUrl &requestUrl, QString *XmlContent){
    XmlContent->clear();
    httpReply_t reply;
    int retCode = 0;

    retCode = httpRequest(requestUrl, &reply);
    qDebug() << "Send finished response: " << retCode;
    QTextCodec *tc = QTextCodec::codecForName("UTF8");
    QString str=tc->toUnicode(reply.response);
    //qDebug()<<"下面是str:"<<"\n"<<str;
    if (str.isEmpty()){
            qDebug()<<"replyxml is empty!";
    }
    XmlContent->append(str);

}

//QString NetTool::FindTitle(const QString sUrl){
//    httpReply_t reply;
//    int retCode = 0;

//    retCode = httpRequest(QUrl(sUrl), &reply);
//    qDebug() << "Send finished response: " << retCode;
//    QTextCodec *tc = QTextCodec::codecForName("UTF8");
//    QString str=tc->toUnicode(reply.response);



//}



