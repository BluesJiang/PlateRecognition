#include <iostream>
#include <QApplication>
#include "dialogs/MainWindow.h"
#include "dialogs/Login.h"
#include "dialogs/SearchWindow.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
#include "tools/QiniuManager.h"
#include "RecognizeTab.h"
#include "SearchTab.h"
using namespace std;

int main(int argc, char* argv[]) {

    QApplication* app = new QApplication(argc, argv);


//    QiniuManager * manager = new QiniuManager();
//    const  char* bucketName = "cpptest";
//
//    manager->uploadFile(&client,bucketName,&mac);
//    Qiniu_Client_Cleanup(&client);
//    Qiniu_Servend_Cleanup();
//
//    Dialog * login = new Dialog();
    MainWindow* mainWindow = new MainWindow();
//    SearchWindow * searchWindow = new SearchWindow();
    mainWindow->show();

//    RecognizeTab regTab;
//    SearchTab seaTab;
//    regTab.show();
//    seaTab.show();



//    searchWindow->show();

    return app->exec();
}