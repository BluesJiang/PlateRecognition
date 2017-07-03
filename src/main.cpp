#include <iostream>
#include <vector>
#include <QApplication>
#include "MainWindow.h"
#include "LoginDialog.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
#include "tools/QiniuManager.h"
#include "RecognizeTab.h"
#include "SearchTab.h"
#include "easypr.h"
#include "PlateModel.h"

typedef std::vector<easypr::CPlate> PlateVector;



int main(int argc, char* argv[]) {

    QApplication* app = new QApplication(argc, argv);




    LoginDialog * login = new LoginDialog();
    MainWindow* mainWindow = new MainWindow();
//    SearchWindow * searchWindow = new SearchWindow();
    mainWindow->show();

//    if(login->exec() == QDialog::Accepted)
//    {
//        mainWindow->show();
//    }

    qRegisterMetaType<std::vector<easypr::CPlate>>("std::vector<easypr::CPlate>");
    qRegisterMetaType<std::vector<PlateModel>>("std::vector<PlateModel>");

//    RecognizeTab regTab;
//    SearchTab seaTab;
//    regTab.show();
//    seaTab.show();

    return app->exec();
}