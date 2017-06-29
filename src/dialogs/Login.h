//
// Created by 杨晨 on 2017/6/29.
//

#ifndef PLATERECOGNITION_LOGIN_H
#define PLATERECOGNITION_LOGIN_H

#include <QDialog>
#include "../ui/ui_Login.h"

#include "src/tools/PlateRecognisor.h"
using namespace std;
using namespace easypr;

class Dialog: public QDialog {
    Q_OBJECT
    Ui::Dialog * ui = NULL;
public:
    explicit Dialog(QWidget* parent = 0);
    ~ Dialog();

protected:
private slots:


};
#endif //PLATERECOGNITION_LOGIN_H
