//
// Created by 杨晨 on 2017/6/30.
//

#include "SearchWindow.h"

SearchWindow::SearchWindow(QWidget *parent) {
    ui = new Ui::SearchWindow();
    ui->setupUi(this);
    standardItemModel = new QStandardItemModel(this);
    standardItemModel->setColumnCount(2);
    QStringList header;
    header.append("车牌号");
    header.append("车主姓名");
    standardItemModel->setHorizontalHeaderLabels(header);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listWidget->setIconSize(QSize(100,100));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setSpacing(8);
    ui->pushButton_2->setEnabled(false);
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
}


SearchWindow::~SearchWindow() {
    delete ui;
    delete standardItemModel;
    delete networkAccessManager;
}

void SearchWindow::searchAndShow() {
    count = 0;
    imageUrls.clear();
    standardItemModel->removeRows(0,standardItemModel->rowCount());
    ui->listWidget->clear();
    DataManager manager;
    PlateModel plateModel;
    std::string plate, owner;

    QStandardItem * item;
    if(ui->plateRadioButton->isChecked())
    {
        plate = ui->lineEdit->text().toStdString();
        manager.queryPlateInfoWithPlate(plate, plateModel);
    }
    else if(ui->nameRadioButton->isChecked())
    {
        owner = ui->lineEdit->text().toStdString();
        manager.queryPlateInfoWithOwner(owner, plateModel);
    }
    imageUrls = QString::fromStdString(plateModel.url).split(";");
    int imageCount = imageUrls.size();



    for(int i = 0 ;i < imageCount; i++)
    {
        request.setUrl(QUrl(imageUrls[i]));
        networkAccessManager->get(request);



    }

    item = new QStandardItem(QString::fromStdString(plateModel.plate));
    standardItemModel->appendRow(item);
    //standardItemModel->setItem(0,0, new QStandardItem(QString::fromStdString(plateModel.plate)));
    standardItemModel->setItem(0,1, new QStandardItem(QString::fromStdString(plateModel.owner)));
    ui->tableView->setModel(standardItemModel);
    int columnWidth = ui->tableView->width() / 2;
    ui->tableView->setColumnWidth(0, columnWidth);
    ui->tableView->setColumnWidth(1, columnWidth);


}


void SearchWindow::display(QListWidgetItem * item)
{
    int index = item->text().toInt() - 1;
    QPixmap tempPixmap = pixmaps[index];
    tempPixmap = tempPixmap.scaled(QSize(481, 311), Qt::KeepAspectRatio);
    ui->label->setPixmap(tempPixmap);
    ui->label->setAlignment(Qt::AlignCenter);
}

void SearchWindow::enablesearch() {
    ui->pushButton_2->setEnabled(true);
}

void SearchWindow::replyFinished(QNetworkReply * reply){
    QPixmap imagePixmap;
    imagePixmap.loadFromData(reply->readAll());

    pixmaps.push_back(imagePixmap);

    imagePixmap = imagePixmap.scaled(QSize(100, 90), Qt::KeepAspectRatio);
    QListWidgetItem * item = new QListWidgetItem(QIcon(imagePixmap), QString::number(count+1, 10));
    item->setSizeHint(QSize(100,110));
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    ui->listWidget->insertItem(count++, item);
}