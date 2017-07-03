//
// Created by BluesJiang on 2017/6/30.
//

#include "RecognizeTab.h"
#include <QApplication>

RecognizeTab::RecognizeTab(QWidget *parent) {
    ui = new Ui::RecognizeTab();
    ui->setupUi(this);
    ui->recognizeButton->setEnabled(false);
    ui->uploadButton->setEnabled(false);
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
    ui->label->setStyleSheet("font-size:20px;color:#cfcfcf;border: 1px solid #cfcfcf;background-color:#ffffff");


    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,SLOT(itemClicked(QModelIndex)));
    connect(&recognisor, SIGNAL(resultReady(std::vector<easypr::CPlate>)), this, SLOT(handleResult(std::vector<easypr::CPlate>)));
    connect(&dataManager, SIGNAL(uploadFinished()), this, SLOT(uploadFinished()));
}

RecognizeTab::~RecognizeTab() {
    delete ui;
    delete standardItemModel;
}

void RecognizeTab::itemClicked(QModelIndex index) {
    QPixmap tempPix = QPixmap::fromImage(*images[index.row()]);
    tempPix = tempPix.scaled(QSize(391,380),Qt::KeepAspectRatio);
    ui->label->setPixmap(tempPix);
    ui->label->setAlignment(Qt::AlignCenter);
}

void RecognizeTab::import() {


    filePath = QFileDialog::getExistingDirectory(this,"请选择导入路径...","./");
    if(filePath.compare("") == 0)   return;

    plates.clear();
    images.clear();
    standardItemModel->removeRows(0,standardItemModel->rowCount());
    ui->importButton->setEnabled(false);
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
        for(int i = 0; i < fileInfoList.size(); i++)
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
        for(int i = 0; i < fileInfoList.size(); i++)  ui->tableView->setRowHeight(i,40);
        ui->label->show();


    }
    ui->importButton->setEnabled(true);
    ui->recognizeButton->setEnabled(true);
}

void RecognizeTab::recognize() {
    emit startRecognize();
    ui->recognizeButton->setEnabled(false);

    recognisor.recognizePlateInDirectory(fileInfoList);



}

void RecognizeTab::handleResult(std::vector<easypr::CPlate> retVec) {
    for(int i = 0; i < retVec.size(); i++)
    {

        QString tempString = QString::fromStdString(retVec[i].getPlateStr());
        tempString = tempString.split(":").last();
        QStandardItem * plateItem = new QStandardItem(tempString);
        standardItemModel->setItem(i,1,plateItem);
        PlateModel plateModel;
        dataManager.queryPlateInfoWithPlate(tempString.toStdString(),plateModel);

        standardItemModel->setItem(i,2, new QStandardItem(QString::fromStdString(plateModel.owner)));

        Mat plateMat = retVec[i].getPlateMat();
        cvtColor(plateMat,plateMat,CV_BGR2RGB);

        QStandardItem * item = new QStandardItem();
        item->setData(QVariant(QPixmap::fromImage(QImage(plateMat.data, plateMat.cols, plateMat.rows, plateMat.step, QImage::Format_RGB888))), Qt::DecorationRole);
        standardItemModel->setItem(i,3, item);

        ui->tableView->setModel(standardItemModel);
        standardItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);
        standardItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);


    }

    emit endRecognize();
    ui->recognizeButton->setEnabled(true);
    ui->uploadButton->setEnabled(true);
}


void RecognizeTab::upload() {
    QMessageBox messageBox(QMessageBox::Warning,"确认上传", "请确认和完善车牌号和车主姓名的信息，是否确认上传？");
    ui->uploadButton->setEnabled(false);
    messageBox.addButton(QMessageBox::Ok);
    messageBox.addButton(QMessageBox::Cancel);
    messageBox.setButtonText(QMessageBox::Ok, "确认");
    messageBox.setButtonText(QMessageBox::Cancel, "取消");
    if(messageBox.exec() == QMessageBox::Cancel) {
        ui->uploadButton->setEnabled(true);
        return;
    }
    emit startUpload();

//    vector<std::string> uploadPlates;
//    cout<<plates[0].getPlateStr()<<endl;
//    for(int i = 0; i < fileInfoList.size(); i++) {
//        uploadPlates.push_back(QString::fromStdString(plates[i].getPlateStr()).split(":").last().toStdString());
//    }
//    cout<<"aaa"<<endl;

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


//    emit endUpload();


}

void RecognizeTab::uploadFinished() {
    ui->uploadButton->setEnabled(true);
    std::cout<< "上传完毕" << std::endl;
    emit endUpload();
}
