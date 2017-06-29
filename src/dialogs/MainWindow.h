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
#include <QFileDialog>
#include <QDir>
#include <vector>
#include "../ui/ui_MainWindow.h"
using namespace std;
class MainWindow: public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui = NULL;
    QStandardItemModel * standardItemModel = NULL;
    vector<QImage *> images;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~ MainWindow();

protected:
    void showEvent(QShowEvent *event);


private slots:

    void onActionExitClicked();
    void itemClicked(QModelIndex index);
    void import();



};


#endif //PLATERECOGNITION_MAINWINDOW_H
