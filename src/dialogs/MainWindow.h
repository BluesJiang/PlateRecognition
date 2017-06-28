//
// Created by BluesJiang on 2017/6/28.
//

#ifndef PLATERECOGNITION_MAINWINDOW_H
#define PLATERECOGNITION_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "../ui/ui_MainWindow.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui = NULL;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~ MainWindow();

private slots:

    void onActionExitClicked();



};


#endif //PLATERECOGNITION_MAINWINDOW_H
