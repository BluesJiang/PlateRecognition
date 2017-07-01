//
// Created by BluesJiang on 2017/6/30.
//

#include "RecognizeTab.h"
#include <QApplication>

RecognizeTab::RecognizeTab(QWidget *parent) {
    ui = new Ui::RecognizeTab();
    ui->setupUi(this);
    ui->recognizeButton->setEnabled(false);
    standardItemModel = new QStandardItemModel(this);
    QStringList header;
    header.append("图片名");
    header.append("车牌号");
    header.append("车主姓名");
    header.append("车牌图片");
    standardItemModel->setHorizontalHeaderLabels(header);
    standardItemModel->setColumnCount(4);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->label->setText("车辆图片");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setFrameShape(QFrame::Box);



    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,SLOT(itemClicked(QModelIndex)));
}

RecognizeTab::~RecognizeTab() {
    delete ui;
    delete standardItemModel;
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
            ui->tableView->setModel(standardItemModel);
            standardItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);

        }


        int columnWidth = ui->tableView->width()/3;
        ui->tableView->setColumnWidth(0,2*columnWidth/3);
        ui->tableView->setColumnWidth(1,2*columnWidth/3);
        ui->tableView->setColumnWidth(2,2*columnWidth/3);

        ui->tableView->setColumnWidth(3,columnWidth-1);
        for(int i = 0; i < fileCount; i++)  ui->tableView->setRowHeight(i,40);
        ui->label->show();


    }

    ui->recognizeButton->setEnabled(true);
}

void RecognizeTab::recognize() {
    emit startRecognize();

    PlateRecognisor recognisor;
    recognisor.recognizePlateInDirectory(fileInfoList, plates);
    DataManager dataManager;

    for(int i = 0; i < fileInfoList.size(); i++)
    {
        QString tempString = QString::fromStdString(plates[i].getPlateStr());
        tempString = tempString.split(":").last();
        QStandardItem * plateItem = new QStandardItem(tempString);
        standardItemModel->setItem(i,1,plateItem);
        PlateModel plateModel;
        dataManager.queryPlateInfoWithPlate(tempString.toStdString(),plateModel);
        standardItemModel->setItem(i,2, new QStandardItem(QString::fromStdString(plateModel.owner)));

        Mat plateMat = plates[i].getPlateMat();
        cvtColor(plateMat,plateMat,CV_BGR2RGB);

        QStandardItem * item = new QStandardItem();
        item->setData(QVariant(QPixmap::fromImage(QImage(plateMat.data, plateMat.cols, plateMat.rows, plateMat.step, QImage::Format_RGB888))), Qt::DecorationRole);
        standardItemModel->setItem(i,3, item);

        ui->tableView->setModel(standardItemModel);
        standardItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);
        standardItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);


    }

    emit endRecognize();

    QMessageBox::information(this, "识别完成", "识别已完成，请检查和完善车牌和车主信息，再点击上传");
}


void RecognizeTab::upload() {
    emit startUpload();
    DataManager dataManager;
    vector<std::string> uploadPlates;
    for(int i = 0; i < fileInfoList.size(); i++) {
        uploadPlates.push_back(QString::fromStdString(plates[i].getPlateStr()).split(":").last().toStdString());
    }
    vector<PlateModel> returnVec;
    dataManager.queryPlateInfoWithPlates(uploadPlates, returnVec);

    vector<PlateModel> plateModels;
    PlateModel plateModel;
    QModelIndex qModelIndex;
    for(int row = 0; row < fileInfoList.size(); row++){
        plateModel.url = fileInfoList[row].filePath().toStdString();
        qModelIndex = standardItemModel->index(row,1);

        plateModel.plate = qModelIndex.data().toString().toStdString();
        qModelIndex = standardItemModel->index(row,2);
        plateModel.owner = qModelIndex.data().toString().toStdString();
        plateModels.push_back(plateModel);
    }

    dataManager.uploadPlate(plateModels);
    emit endUpload();

}