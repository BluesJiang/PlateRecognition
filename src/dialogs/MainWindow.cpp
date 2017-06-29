//
// Created by BluesJiang on 2017/6/28.
//

#include "MainWindow.h"
#include <iostream>

using namespace easypr;

MainWindow::MainWindow(QWidget *parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    this->menuBar()->setNativeMenuBar(false);
    ui->pushButton_2->setEnabled(false);
    standardItemModel = new QStandardItemModel(this);
    QStringList header;
    header.append("图片名");
    header.append("车牌号");
    standardItemModel->setHorizontalHeaderLabels(header);
    standardItemModel->setColumnCount(2);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->label->setText(" ");
    ui->label->setAlignment(Qt::AlignCenter);



    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,SLOT(itemClicked(QModelIndex)));



}

void MainWindow::onActionExitClicked() {
    close();
}


void MainWindow::itemClicked(QModelIndex index) {


    QPixmap tempPix = QPixmap::fromImage(*images[index.row()]);
    tempPix = tempPix.scaled(QSize(351,321),Qt::KeepAspectRatio);
    ui->label->setPixmap(tempPix);
    ui->label->setAlignment(Qt::AlignCenter);

}


void MainWindow::showEvent(QShowEvent *event) {
}


void MainWindow::import() {
    QString filePath = QFileDialog::getExistingDirectory(this,"请选择导入路径...","./");
    QStringList filters;
    filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png");
    if(filePath.isEmpty())
    {
        return;
    }

    else
    {
        QDir qdir(filePath);
        if(!qdir.exists())  return;
        qdir.setFilter(QDir::Files | QDir::NoSymLinks);
        qdir.setNameFilters(filters);
        fileInfoList = qdir.entryInfoList();
        int fileCount = fileInfoList.size();
        for(int i = 0; i < fileCount; i++)
        {
            QStandardItem * tempItem = new QStandardItem(fileInfoList[i].fileName());
            QImage * qImage = new QImage;
            qImage->load(fileInfoList[i].filePath());
            images.push_back(qImage);
            standardItemModel->appendRow(tempItem);
        }

        ui->tableView->setModel(standardItemModel);
        int columnWidth = ui->tableView->width()/2;
        cout<<columnWidth<<","<<ui->tableView->width();

        ui->tableView->setColumnWidth(0,columnWidth);
        ui->tableView->setColumnWidth(1,columnWidth);
        ui->label->show();


    }

    ui->pushButton_2->setEnabled(true);
}

void MainWindow::recognize()
{
    CPlate cplate;
    PlateRecognisor recognisor;
    for(int i = 0; i < fileInfoList.size(); i++)
    {
        QString plateResult = recognisor.recognizePlateInFile(fileInfoList[i].filePath());

        //cout<<plateResult.toStdString()<<endl
        standardItemModel->setItem(i, 1, new QStandardItem(plateResult));
        ui->tableView->setModel(standardItemModel);
    }

}
MainWindow::~MainWindow() {
    delete ui;
}


