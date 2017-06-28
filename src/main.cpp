#include <iostream>
#include <QApplication>
#include "dialogs/MainWindow.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication* app = new QApplication(argc, argv);

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();

    return app->exec();
}