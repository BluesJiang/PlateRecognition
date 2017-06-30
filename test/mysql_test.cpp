//
// Created by BluesJiang on 2017/6/29.
//

#include <iostream>
#include <mysql.h>
#include "DataManager.h"
#include "PlateModel.h"
#include "PlateRecognisor.h"
#include <QObject>
#include <QApplication>

using namespace std;


int main(int argc, char* argv[]) {


    DataManager manager;
    PlateModel plate;
    string password = manager.queryPassword("root");
    cout << password << endl;

    manager.queryPlateInfoWithOwner("蒋志远", plate);
    plate.description();

    manager.queryPlateInfoWithPlate("12345", plate);
    plate.description();

    vector<PlateModel> plateVector;
    vector<string> names = {"blues", "yangchen"};
    manager.queryPlateInfoWithOwners(names, plateVector);
    for (auto val : plateVector) {
        val.description();
    }
    plateVector.clear();
    manager.queryPlateInfoWithPlateKeyword("23", plateVector);
    for (auto val : plateVector) {
        val.description();
    }
    plateVector.clear();
    plateVector.push_back(PlateModel("123456", "/Users/Blues/Downloads/发送文件/03.CarPicture/03.CarPicture/琼AM6666.jpg", "blues"));
    plateVector.push_back(PlateModel("123456", "/Users/Blues/Downloads/发送文件/03.CarPicture/03.CarPicture/DSCF2916.JPG", "blues"));
    plateVector.push_back(PlateModel("123456","/Users/Blues/Downloads/发送文件/03.CarPicture/03.CarPicture/DSCF2916.JPG", "blues"));
    manager.uploadPlate(plateVector);


    return 0;
}
