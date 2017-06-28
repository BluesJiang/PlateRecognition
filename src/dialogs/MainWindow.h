//
// Created by BluesJiang on 2017/6/28.
//

#ifndef PLATERECOGNITION_MAINWINDOW_H
#define PLATERECOGNITION_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>
#include "../ui/ui_MainWindow.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui = NULL;
    QStandardItemModel * standardItemModel = NULL;
    QImage * image = new QImage;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~ MainWindow();



private slots:

    void onActionExitClicked();
    void itemClicked(QModelIndex index);



};


#endif //PLATERECOGNITION_MAINWINDOW_H
