#include <iostream>
#include <QApplication>
#include "MainWindow.h"
#include "LoginDialog.h"
#include "SearchWindow.h"
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




    LoginDialog * login = new LoginDialog();
    MainWindow* mainWindow = new MainWindow();
//    SearchWindow * searchWindow = new SearchWindow();
    mainWindow->show();
//    if(login->exec() == QDialog::Accepted)
//    {
//        mainWindow->show();
//    }

    return app->exec();
}