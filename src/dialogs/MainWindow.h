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
#include <easypr.h>

#include "ui_MainWindow.h"
#include "PlateRecognisor.h"
using namespace std;
using namespace easypr;

class MainWindow: public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui = NULL;
    QStandardItemModel * standardItemModel = NULL;
    vector<QImage *> images;
    QFileInfoList fileInfoList;
    vector<CPlate> plates;
    QString filePath;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~ MainWindow();

protected:
    void showEvent(QShowEvent *event);


private slots:

    void onActionExitClicked();
    void itemClicked(QModelIndex index);
    void import();
    void recognize();



};


#endif //PLATERECOGNITION_MAINWINDOW_H
