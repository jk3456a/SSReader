#ifndef INTERNET_H
#define INTERNET_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

typedef struct {
    int httpCode;
    QByteArray response;
} httpReply_t;

class Internet : public QObject
{
    Q_OBJECT
public:
    explicit Internet(QObject *parent = nullptr);
    ~Internet();
    bool loadJson(const QUrl &requestUrl, QStringList *Routelist);
    bool loadXml(const QUrl &requestUrl, QString *XmlContent);
    

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    int httpRequest(const QUrl &requestUrl, httpReply_t *reply);
};

#endif // INTERNET_H
