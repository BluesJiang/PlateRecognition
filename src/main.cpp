#include <iostream>
#include <QApplication>
#include "dialogs/MainWindow.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
#include "tools/QiniuManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication* app = new QApplication(argc, argv);
    Qiniu_Client client;
    Qiniu_Mac mac;

    mac.accessKey = "QC3MrjeF38x1iUIdVBRVRVnlmZYOlqFRQy2PQ4pK";
    mac.secretKey = "l5hMWe_svAcifqy4zLjcScov18FAX75Xm9STxyLd";
    // 初始化
    Qiniu_Servend_Init(-1);
    Qiniu_Client_InitMacAuth(&client, 1024, &mac);

    QiniuManager * manager = new QiniuManager();
    const  char* bucketName = "cpptest";

    manager->uploadFile(&client,bucketName,&mac);
    Qiniu_Client_Cleanup(&client);
    Qiniu_Servend_Cleanup();
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();

    return app->exec();
}