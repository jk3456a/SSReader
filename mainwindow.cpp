#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    initBut();
    initTreeWidget();
    initListWidget();
    /*initOther();
    initStyle();
    initTranslator();8*/
}

void MainWindow::initBut(){

    QPixmap pixmap1_1(":/img/But1_1.png");
    QIcon SubButIcon(pixmap1_1);
    ui->SubscriButton->setIcon(SubButIcon);
    ui->SubscriButton->setIconSize(QSize(40,40));
    ui->SubscriButton->setFlat(true);

    QPixmap pixmap1_2(":/img/But1_2.png");
    QIcon StyleButIcon(pixmap1_2);
    ui->StyleButton->setIcon(StyleButIcon);
    ui->StyleButton->setIconSize(QSize(40,40));
    ui->StyleButton->setFlat(true);

    QPixmap pixmap1_3(":/img/But1_3.png");
    QIcon SetButIcon(pixmap1_3);
    ui->SettingButton->setIcon(SetButIcon);
    ui->SettingButton->setIconSize(QSize(40,40));
    ui->SettingButton->setFlat(true);

    QPixmap pixmap1_4(":/img/But1_4.png");
    QIcon HelpButIcon(pixmap1_4);
    ui->HelpButton->setIcon(HelpButIcon);
    ui->HelpButton->setIconSize(QSize(40,40));
    ui->HelpButton->setFlat(true);

    //account需要生成图片 @Todolist
    QPixmap pixmap1_5(":/img/But1_5.png");
    QIcon AccButIcon(pixmap1_5);
    ui->AccountButton->setIcon(AccButIcon);
    ui->AccountButton->setIconSize(QSize(40,40));
    ui->AccountButton->setFlat(true);

    QPixmap pixmap2_1(":/img/But2_1.png");
    QIcon ButIcon2_1(pixmap2_1);
    ui->CataButton->setIcon(ButIcon2_1);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap3_1(":/img/But3_1.png");
    QIcon ButIcon3_1(pixmap3_1);
    ui->CataButton->setIcon(ButIcon3_1);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap3_2(":/img/But3_2.png");
    QIcon ButIcon3_2(pixmap3_2);
    ui->CataButton->setIcon(ButIcon3_2);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap3_3(":/img/But3_3.png");
    QIcon ButIcon3_3(pixmap3_3);
    ui->CataButton->setIcon(ButIcon3_3);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap3_4(":/img/But3_4.png");
    QIcon ButIcon3_4(pixmap3_4);
    ui->CataButton->setIcon(ButIcon3_4);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap4_1(":/img/But4_1.png");
    QIcon ButIcon4_1(pixmap4_1);
    ui->CataButton->setIcon(ButIcon4_1);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap4_2(":/img/But4_2.png");
    QIcon ButIcon4_2(pixmap4_2);
    ui->CataButton->setIcon(ButIcon4_2);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap4_3(":/img/But4_3.png");
    QIcon ButIcon4_3(pixmap4_1);
    ui->CataButton->setIcon(ButIcon4_3);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);

    QPixmap pixmap4_4(":/img/But4_4.png");
    QIcon ButIcon4_4(pixmap4_4);
    ui->CataButton->setIcon(ButIcon4_4);
    ui->CataButton->setIconSize(QSize(20,20));
    ui->CataButton->setFlat(true);
}

/*依靠账户首字生成图片
void MainWindow::paintEvent(QPaintEvent *){
    QPainter Painter(this);
    QPixmap pixmap1_5(":/img/AccButton.png");

    QColor qc=QColor::fromHsl(rand()%360,rand()%256,rand()%200);
    QBrush brush(QColor(qc.red(),qc.green(),qc.blue()));

    Painter.setFont(QFont(QString::fromLocal8Bit("宋体"),50,-1,false));
    QChar C = LogUser.at(0);

    Painter.setBrush(brush);
    Painter.drawRect(0,0,40,40);

    Painter.setPen(Qt::black);
    Painter.drawText(rect(),Qt::AlignCenter,QString(C));
}*/

void MainWindow::on_SubscriButton_clicked()
{
    subspage = new SubsPage;
    subspage->show();
    this->update();
}

void MainWindow::initTreeWidget(){
    //ui->CataList->clear();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare(load_src);
    query->addBindValue(Loguid);
    if(!query->exec()) {
        qDebug()<<"fail to load src";
    }

    QString cid = "";
    QString source = "";
    QMap<QString, QList<QString>> Category;
    while (query->next()) {
        if(cid != query->value(0).toString()){
            cid = query->value(0).toString();
            Category["all"] += cid;
            if(source != query->value(1).toString()){
                source = query->value(1).toString();
                Category[cid] += QList<QString>()<<source;
                Category[source] += QList<QString>()<<query->value(2).toString();
            }else {
                Category[source] += QList<QString>()<<query->value(2).toString();
            }

        }else{
            if(source != query->value(1).toString()){
                source = query->value(1).toString();
                Category[cid] += QList<QString>()<<source;
                Category[source] += QList<QString>()<<query->value(2).toString();
            }else {
                Category[source] += QList<QString>()<<query->value(2).toString();
            }
        }

    }

    model = new QStandardItemModel();

   //int n = 0;
   for (QString cid : Category.value("all")) {
       qDebug()<<cid;
       QStandardItem *cateItem = new QStandardItem(cid);
       model->appendRow(cateItem); // [*] 创建了多列

       // 遍历当前省下的市，创建市的节点
       for (QString source : Category.value(cid)) {
           QStandardItem *sourceItem = new QStandardItem(source);
           cateItem->appendRow(sourceItem); // [*] 只创建了一列

           // 遍历当前市下的县，创建县的节点
           for (QString rssurl : Category.value(source)) {
               QStandardItem *rssurlItem = new QStandardItem(rssurl);
               sourceItem->appendRow(rssurlItem); // [*] 创建了多列
           }
       }
   }

    ui->CataList->setModel(model);



}

void MainWindow::on_CataList_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    QDate date = QDate::currentDate();
    ui->CataView->setText(date.toString()+"\n"+index.data().toString());
    //changeOverview(index.data().toString());

}



void MainWindow::on_StyleButton_clicked()
{
    //切换夜间模式
}

void MainWindow::on_SettingButton_clicked()
{
    setpage = new SettingPage;
    setpage->show();
}

void MainWindow::changeOverview(const QString *category){
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare(load_overview);
    query->addBindValue(Loguid);
    query->addBindValue(category);
    query->addBindValue(category);
    query->addBindValue(category);
    if(!query->exec()){
        qDebug()<<"sql load error";
    }
    while(query->next()){

    }

}
void MainWindow::initListWidget(){
    ViewWay = 0;
    QDate date = QDate::currentDate();
    ui->CataView->setText(date.toString());
}