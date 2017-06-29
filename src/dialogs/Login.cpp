//
// Created by 杨晨 on 2017/6/29.
//

#include "Login.h"
#include <iostream>


Dialog::Dialog(QWidget *parent) {
    ui = new Ui::Dialog();
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignRight);
    ui->label_3->setAlignment(Qt::AlignRight);
    ui->label_2->setAlignment(Qt::AlignVCenter);
    ui->label_3->setAlignment(Qt::AlignVCenter);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QImage * image = new QImage("/Users/yangchen/Desktop/logo.png");
    ui->label->setPixmap(QPixmap::fromImage(*image));



}

Dialog::~Dialog() {
    delete ui;
}