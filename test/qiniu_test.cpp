//
// Created by CGJ on 2017/6/30.
//

#include <iostream>
#include <QApplication>
#include "src/dialogs/MainWindow.h"
#include "src/dialogs/Login.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
#include "src/tools/QiniuManager.h"

#include <vector>
#include "src/model/PlateModel.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication* app = new QApplication(argc, argv);

    QiniuManager * manager = new QiniuManager();

    vector<PlateModel> plates;
    vector<PlateModel> retVec;


    plates.push_back(PlateModel("123456",  "/Users/cgj/Desktop/upload/jikeup1.jpg","guojin"));
    plates.push_back(PlateModel("123457",  "/Users/cgj/Desktop/upload/jikeup2.jpg","guojin1"));
    manager->uploadFile(plates,retVec);

    PlateModel  plateSingle("test", "/Users/cgj/Desktop/upload/jikeup2.jpg", "guojinTEst");
    PlateModel  retPlate;
    manager->uploadFile(plateSingle,retPlate);
    cout<<"retPalte url:"<<retPlate.url<<endl;
    Dialog * login = new Dialog();
    MainWindow* mainWindow = new MainWindow();

    login->show();

    return app->exec();
}
