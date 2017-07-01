//
// Created by 杨晨 on 2017/6/29.
//

#ifndef PLATERECOGNITION_LOGIN_H
#define PLATERECOGNITION_LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "ui_LoginDialog.h"
#include "DataManager.h"
#include "PlateRecognisor.h"
using namespace std;
using namespace easypr;

class LoginDialog: public QDialog {
    Q_OBJECT
    Ui::LoginDialog * ui = NULL;
public:
    explicit LoginDialog(QWidget* parent = 0);
    ~ LoginDialog();

protected:

private slots:
    void userIdentify();
    void exit();


};
#endif //PLATERECOGNITION_LOGIN_H
