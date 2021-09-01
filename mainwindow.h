#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pch.h"
#include "subspage.h"
#include "settingpage.h"
#include "global.h"
#include "sqltool.h"
#include "nettool.h"
#include "tinyxml2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //void QPaintEvent(QPaintEvent *);

private slots:
    void on_SubscriButton_clicked();

    void on_CataList_clicked(const QModelIndex &index);

    void on_StyleButton_clicked();

    void on_SettingButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    SubsPage *subspage;
    SettingPage *setpage;
    NetTool *m_network;
    QAxWidget* webWidget;
    QString aurl;

    int ViewWay;

    void init();
    void initBut();
    void initTreeWidget();
    void initListWidget();
    void initOther();
    void initStyle();
    void initTranslator();


    void updateList();
    void changeOverview (QString category);

private slots:
    void changeArticle(QString aurl);
};

#endif // MAINWINDOW_H
