//
// Created by BluesJiang on 2017/6/28.
//

#include "MainWindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    this->menuBar()->setNativeMenuBar(false);
}

void MainWindow::onActionExitClicked() {
    close();
}

MainWindow::~MainWindow() {
    delete ui;
}