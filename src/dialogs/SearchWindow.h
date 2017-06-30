//
// Created by 杨晨 on 2017/6/30.
//

#ifndef PLATERECOGNITION_SEARCHWINDOW_H
#define PLATERECOGNITION_SEARCHWINDOW_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMainWindow>
#include <vector>
#include <easypr.h>
#include <QStandardItemModel>
#include "../tools/DataManager.h"
#include "../model/PlateModel.h"
#include "../ui/ui_SearchWindow.h"
#include <QLabel>
#include <QPixmap>


using namespace std;
using namespace easypr;

class SearchWindow: public QMainWindow {
    Q_OBJECT
    Ui::SearchWindow * ui = NULL;
    vector<PlateModel> queryResult;
    vector<QPixmap> pixmaps;

    QStandardItemModel * standardItemModel = NULL;
    QStringList imageUrls;
    QNetworkRequest request;
    QNetworkAccessManager * networkAccessManager;
    QNetworkReply * reply = NULL;
    int count = 0;


public:
    explicit SearchWindow(QWidget* parent = 0);
    ~ SearchWindow();

protected:
    //void showEvent(QShowEvent *event);


private slots:
    void searchAndShow();
    void display(QListWidgetItem *);
    void enablesearch();
    void replyFinished(QNetworkReply * );




};
#endif //PLATERECOGNITION_SEARCHWINDOW_H
