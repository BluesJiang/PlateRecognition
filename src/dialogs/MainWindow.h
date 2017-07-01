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
#include "RecognizeTab.h"
#include "SearchTab.h"
using namespace std;
using namespace easypr;

class MainWindow: public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui = NULL;
    RecognizeTab* recognizeTab;
    SearchTab* searchTab;
    QLabel * label = NULL;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~ MainWindow();
private slots:
    void startRecognizeStatus();
    void endRecognizeStatus();
    void startUploadStatus();
    void endUploadStatus();




};


#endif //PLATERECOGNITION_MAINWINDOW_H
