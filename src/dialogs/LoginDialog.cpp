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
    QImage * image = new QImage("https://ss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1_31bdc765.png");

    ui->label->setPixmap(QPixmap::fromImage(*image));



}

LoginDialog::~LoginDialog() {
    delete ui;
}