#ifndef SUBSPAGE_H
#define SUBSPAGE_H

#include <QWidget>
#include "pch.h"
#include "sqltool.h"

namespace Ui {
class SubsPage;
}

class SubsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SubsPage(QWidget *parent = nullptr);
    ~SubsPage();

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    void on_SubButton_clicked();

    void replyFinished(QNetworkReply *);

private:
    Ui::SubsPage *ui;
    QCompleter *completer;
    QUrl url;
    QNetworkRequest req;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QStringList Routelist;
    void httpRequest(const QUrl &requestedUrl);

};

#endif // SUBSPAGE_H
