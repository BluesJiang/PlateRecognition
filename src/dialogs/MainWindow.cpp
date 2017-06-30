//
// Created by BluesJiang on 2017/6/28.
//

#include "MainWindow.h"
#include <iostream>

using namespace easypr;

MainWindow::MainWindow(QWidget *parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    recognizeTab = new RecognizeTab();
    searchTab = new SearchTab();
    ui->tabWidget->addTab(recognizeTab, "车牌识别");
    ui->tabWidget->addTab(searchTab, "车牌检索");
}

MainWindow::~MainWindow() {
    delete ui;
    delete recognizeTab;
    delete searchTab;
}



