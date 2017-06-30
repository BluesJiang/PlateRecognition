//
// Created by BluesJiang on 2017/6/30.
//

#ifndef PLATERECOGNITION_SEARCHTAB_H
#define PLATERECOGNITION_SEARCHTAB_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMainWindow>
#include <vector>
#include <easypr.h>
#include <QStandardItemModel>
#include "DataManager.h"
#include "PlateModel.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include "ui_SearchTab.h"


class SearchTab: public QWidget {
    Q_OBJECT
    Ui::SearchTab * ui = NULL;
    vector<PlateModel> queryResult;
    vector<QPixmap> pixmaps;

    QStandardItemModel * standardItemModel = NULL;
    QStringList imageUrls;
    QNetworkRequest request;
    QNetworkAccessManager * networkAccessManager;
    QNetworkReply * reply = NULL;
    int count = 0;
public:
    explicit SearchTab(QWidget* parent = 0);
    ~SearchTab();

private slots:
    void searchAndShow();
    void display(QListWidgetItem *);
    void enableSearchButton();
    void replyFinished(QNetworkReply * );


};


#endif //PLATERECOGNITION_SEARCHTAB_H
