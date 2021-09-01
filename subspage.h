#ifndef SUBSPAGE_H
#define SUBSPAGE_H

#include <QWidget>
#include "pch.h"
#include "nettool.h"
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


private slots:
    void on_SubButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::SubsPage *ui;
    QCompleter *completer;
    NetTool *s_network;
    QStringList Routelist;
};

#endif // SUBSPAGE_H
