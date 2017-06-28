//
// Created by BluesJiang on 2017/6/28.
//

#include "MainWindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    this->menuBar()->setNativeMenuBar(false);

    standardItemModel = new QStandardItemModel(this);
    QStringList header;
    header.append("车牌号");
    header.append("姓名");
    header.append("用户号");
    standardItemModel->setColumnCount(3);
    standardItemModel->setHorizontalHeaderLabels(header);

    QStringList strings;
    strings.append("a");
    strings.append("b");
    int stringCount = strings.size();

    for(int i = 0; i < stringCount; i++)
    {
        QString string = strings.at(i);
        QStandardItem * item = new QStandardItem(string);
        standardItemModel->appendRow(item);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableView->setModel(standardItemModel);
    }
    int column_width = ui->tableView->width()/3;
    ui->tableView->setColumnWidth(0,column_width);
    ui->tableView->setColumnWidth(1,column_width);
    ui->tableView->setColumnWidth(2,column_width);
    image->load("/Users/yangchen/Desktop/carTest2.png");

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    ui->graphicsView->show();

    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,SLOT(itemClicked(QModelIndex)));



}

void MainWindow::onActionExitClicked() {
    close();
}


void MainWindow::itemClicked(QModelIndex index) {
}

MainWindow::~MainWindow() {
    delete ui;
}