#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QUuid>
#include "pch.h"
#include "mainwindow.h"
#include "sqltool.h"

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private:
    QLabel *TitleImage;
    QLabel *UserLabel;
    QLabel *PasswordLabel;
    QLineEdit *UserLine;
    QLineEdit *PasswordLine;

    QPushButton *LoginButton;
    QPushButton *SignUpButton;

    MainWindow *SSReader;
signals:
private slots:
    void log_in();
    void sign_up();
};

#endif // LOGINPAGE_H
