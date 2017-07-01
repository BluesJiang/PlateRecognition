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
    label = new QLabel();
    ui->statusBar->addWidget(label);
    ui->tabWidget->addTab(recognizeTab, "车牌识别");
    ui->tabWidget->addTab(searchTab, "车牌检索");
    connect(recognizeTab, SIGNAL(startRecognize()), this, SLOT(startRecognizeStatus()), Qt::DirectConnection);
    connect(recognizeTab, SIGNAL(endRecognize()), this, SLOT(endRecognizeStatus()));
    connect(recognizeTab, SIGNAL(startUpload()), this, SLOT(startUploadStatus()));
    connect(recognizeTab, SIGNAL(endUpload()), this, SLOT(endUploadStatus()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete recognizeTab;
    delete searchTab;
}


void MainWindow::startRecognizeStatus() {
    label->setText("正在识别...");

}

void MainWindow::endRecognizeStatus() {
    label->setText("识别完成");

}

void MainWindow::startUploadStatus() {
   label->setText("正在上传...");
}

void MainWindow::endUploadStatus() {
    label->setText("上传完成");
}

