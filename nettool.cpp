#include "nettool.h"

QString httpRequest(const QUrl &requestedUrl){
    QUrl url;
    QNetworkRequest req;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

    url = requestedUrl;
    manager = new QNetworkAccessManager();

    // https需要的配置（http不需要）
    QSslConfiguration sslConf = req.sslConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConf.setProtocol(QSsl::TlsV1SslV3);
    req.setSslConfiguration(sslConf);
    // https需要的配置（http不需要）

    req.setUrl(url);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    reply = manager->get(req);
    connect(reply,SIGNAL(finished(QNetworkReply *)),this,SLOT(replyFinished()));
    if (reply->error() == QNetworkReply::NoError)
        {
            int statusCode  = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << "statusCode:" << statusCode;
            QTextCodec *codec = QTextCodec::codecForName("utf8");
            QString str = codec->toUnicode(reply->readAll());
            return str;
        }else {
            qDebug()<<reply->errorString();
            reply->deleteLater();
            return NULL;
        }
}

QStringList explainReply(const QString reply){
    QStringList liblist;
    if (reply.isEmpty()){
        qDebug()<<"reply is empty!";
        return liblist;
    }
    // 解析Json字符串
    QJsonParseError error;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(reply.toUtf8(), &error);
    qDebug()<<JsonDoc;
    // 字符串没有错误
    if (!JsonDoc.isEmpty() && (error.error == QJsonParseError::NoError)) {
        // 转为Json对象
        const QJsonObject JsonObj = JsonDoc.object();
        QJsonObject data = JsonObj.value("data").toObject();
        // 迭代获得route词典
        QJsonObject::iterator it;
        for(it=data.begin();it!=data.end();it++){
           QJsonArray routes = it.value().toArray();
           for(int i = 0; i < data.count(); i++){
               QJsonValue value = routes.at(i);
               liblist += value.toString();
           }
        }
    }
    return liblist;
}
