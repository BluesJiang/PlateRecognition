//
// Created by BluesJiang on 2017/6/30.
//

#ifndef PLATERECOGNITION_RECOGNIZETAB_H
#define PLATERECOGNITION_RECOGNIZETAB_H

#include <QWidget>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFrame>
#include <vector>
#include <easypr.h>
#include "./model/PlateModel.h"
#include "PlateRecognisor.h"
#include "ui_RecognizeTab.h"
#include "DataManager.h"
class RecognizeTab : public QWidget {
    Q_OBJECT
    Ui::RecognizeTab* ui = NULL;
    QStandardItemModel * standardItemModel = NULL;
    vector<QImage *> images;
    QFileInfoList fileInfoList;
    vector<easypr::CPlate> plates;
    QString filePath;
    PlateRecognisor recognisor;
    DataManager dataManager;
public:
    explicit RecognizeTab(QWidget* parent = 0);
    ~RecognizeTab();

private slots:

    void itemClicked(QModelIndex index);
    void import();
    void recognize();
    void upload();
    void handleResult(std::vector<easypr::CPlate> retVec);
    void uploadFinished();

signals:
    void startRecognize();
    void endRecognize();
    void startUpload();
    void endUpload();


};


#endif //PLATERECOGNITION_RECOGNIZETAB_H
