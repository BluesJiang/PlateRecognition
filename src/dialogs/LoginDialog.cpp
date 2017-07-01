//
// Created by 杨晨 on 2017/6/29.
//

#include "LoginDialog.h"
#include <iostream>


LoginDialog::LoginDialog(QWidget *parent) {
    ui = new Ui::LoginDialog();
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignRight);
    ui->label_3->setAlignment(Qt::AlignRight);
    ui->label_2->setAlignment(Qt::AlignVCenter);
    ui->label_3->setAlignment(Qt::AlignVCenter);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QImage * image = new QImage("/Users/yangchen/Desktop/PlateRecognition/resources/image/logo.png");
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->loginButton, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), ui->loginButton, SIGNAL(clicked()), Qt::UniqueConnection);
    ui->label->setPixmap(QPixmap::fromImage(*image));



}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::userIdentify() {
    QString usernameInput = ui->lineEdit->text();
    QString passwordInput = ui->lineEdit_2->text();

    if(usernameInput.compare("") == 0)
    {
        QMessageBox::warning(this, "请输入用户名", "用户名不能为空");
        return;
    }
    DataManager dataManager;
    string passwordFromDatabase = dataManager.queryPassword(usernameInput.toStdString());

    if(passwordFromDatabase.compare("") == 0)
    {
        QMessageBox::warning(this, "用户名输入错误", "该用户名不存在");
        return;
    }


    if(passwordInput.compare(QString::fromStdString(passwordFromDatabase)) != 0)
    {
        QMessageBox::warning(this, "密码错误", "密码输入错误，请重新输入");
        return;
    }

    this->hide();
    return accept();

}

void LoginDialog::exit() {
    this->close();
}