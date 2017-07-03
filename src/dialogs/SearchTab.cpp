//
// Created by BluesJiang on 2017/6/30.
//

#include "SearchTab.h"

SearchTab::SearchTab(QWidget *parent) {
    ui = new Ui::SearchTab();
    ui->setupUi(this);
    standardItemModel = new QStandardItemModel(this);
    standardItemModel->setColumnCount(2);
    QStringList header;
    header.append("车牌号");
    header.append("车主姓名");
    standardItemModel->setHorizontalHeaderLabels(header);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->label->setText("车辆图片");
    ui->listWidget->setIconSize(QSize(100,100));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setSpacing(25);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->searchButton->setEnabled(false);
    networkAccessManager = new QNetworkAccessManager(this);
    ui->searchButton->setShortcut(Qt::Key_Enter);
    //stylesheets
    ui->label->setStyleSheet("border-radius:3px;font-size:20px;color:#cfcfcf;border: 1px solid #cfcfcf;background-color:#ffffff");

    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->searchButton, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));


}

SearchTab::~SearchTab() {
    delete ui;
    delete standardItemModel;
    delete networkAccessManager;
}

void SearchTab::searchAndShow() {
    count = 0;
    imageUrls.clear();
    standardItemModel->removeRows(0,standardItemModel->rowCount());
    ui->listWidget->clear();
    ui->label->setText("车辆图片");
    pixmaps.clear();
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
        request.setUrl(imageUrls[i]);

        networkAccessManager->get(request);



    }

    item = new QStandardItem(QString::fromStdString(plateModel.plate));
    standardItemModel->appendRow(item);
    //standardItemModel->setItem(0,0, new QStandardItem(QString::fromStdString(plateModel.plate)));
    standardItemModel->setItem(0,1, new QStandardItem(QString::fromStdString(plateModel.owner)));
    ui->tableView->setModel(standardItemModel);


        standardItemModel->item(0,0)->setTextAlignment(Qt::AlignCenter);
        standardItemModel->item(0,1)->setTextAlignment(Qt::AlignCenter);

    int columnWidth = ui->tableView->width() / 2;
    ui->tableView->setColumnWidth(0, columnWidth);
    ui->tableView->setColumnWidth(1, columnWidth);
}

void SearchTab::display(QListWidgetItem * item) {
    int index = item->text().toInt() - 1;
    QPixmap tempPixmap = pixmaps[index];
    tempPixmap = tempPixmap.scaled(QSize(451, 281), Qt::KeepAspectRatio);
    ui->label->setPixmap(tempPixmap);
    ui->label->setAlignment(Qt::AlignCenter);
}

void SearchTab::enableSearchButton() {
    ui->searchButton->setEnabled(true);
}

void SearchTab::replyFinished(QNetworkReply * reply) {
    if(imageUrls[0].compare("") == 0)
    {
        return ;
    }

    QPixmap imagePixmap;

    imagePixmap.loadFromData(reply->readAll());

    pixmaps.push_back(imagePixmap);
    imagePixmap = imagePixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio);
    QListWidgetItem * item = new QListWidgetItem(QIcon(imagePixmap), QString::number(count+1, 10));
    item->setSizeHint(QSize(100,110));
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);

    ui->listWidget->insertItem(count++, item);
}
