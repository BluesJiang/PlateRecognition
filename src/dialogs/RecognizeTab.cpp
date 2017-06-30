//
// Created by BluesJiang on 2017/6/30.
//

#include "RecognizeTab.h"

RecognizeTab::RecognizeTab(QWidget *parent) {
    ui = new Ui::RecognizeTab();
    ui->setupUi(this);
    ui->recognizeButton->setEnabled(false);
    standardItemModel = new QStandardItemModel(this);
    QStringList header;
    header.append("图片名");
    header.append("车牌号");
    header.append("车牌图片");
    standardItemModel->setHorizontalHeaderLabels(header);
    standardItemModel->setColumnCount(3);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->label->setText(" ");
    ui->label->setAlignment(Qt::AlignCenter);



    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,SLOT(itemClicked(QModelIndex)));
}

RecognizeTab::~RecognizeTab() {
    delete ui;
}

void RecognizeTab::itemClicked(QModelIndex index) {
    QPixmap tempPix = QPixmap::fromImage(*images[index.row()]);
    tempPix = tempPix.scaled(QSize(461,451),Qt::KeepAspectRatio);
    ui->label->setPixmap(tempPix);
    ui->label->setAlignment(Qt::AlignCenter);
}

void RecognizeTab::import() {
    plates.clear();
    images.clear();
    standardItemModel->removeRows(0,standardItemModel->rowCount());
    filePath = QFileDialog::getExistingDirectory(this,"请选择导入路径...","./");
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
        int columnWidth = ui->tableView->width()/3;
        ui->tableView->setColumnWidth(0,columnWidth);
        ui->tableView->setColumnWidth(1,columnWidth);
        ui->tableView->setColumnWidth(2,columnWidth);
        for(int i = 0; i < fileCount; i++)  ui->tableView->setRowHeight(i,40);
        ui->label->show();


    }

    ui->recognizeButton->setEnabled(true);
}

void RecognizeTab::recognize() {
    PlateRecognisor recognisor;
    recognisor.recognizePlateInDirectory(fileInfoList, plates);

    for(int i = 0; i < fileInfoList.size(); i++)
    {
        standardItemModel->setItem(i,1,new QStandardItem(QString::fromStdString(plates[i].getPlateStr())));
        Mat plateMat = plates[i].getPlateMat();
        QStandardItem * item = new QStandardItem();
        item->setData(QVariant(QPixmap::fromImage(QImage(plateMat.data, plateMat.cols, plateMat.rows, plateMat.step, QImage::Format_RGB888))), Qt::DecorationRole);

        standardItemModel->setItem(i,2, item);
        ui->tableView->setModel(standardItemModel);

    }
}
