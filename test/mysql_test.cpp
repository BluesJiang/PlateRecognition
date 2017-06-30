//
// Created by BluesJiang on 2017/6/29.
//

#include <iostream>
#include <mysql.h>
#include "../src/tools/DataManager.h"
#include "../src/model/PlateModel.h"

using namespace std;

int main() {
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    MYSQL_RES * result;
//    MYSQL_ROW sql_row;
//    int ret = mysql_set_character_set(&mysql, "utf8");
//
//
//    connection = mysql_real_connect(&mysql,"123.207.59.11","root","5Believe!!","T-Dog",0,0,0);
//
//    int res = mysql_query(&mysql, "select * from itemtable");
//
//    if(!res)
//    {
//        result = mysql_store_result(&mysql);
//        if (result)
//        {
//            while ((sql_row = mysql_fetch_row(result)))//获取具体的数据
//            {
//                cout<<"  ID:" << sql_row[0] << endl;
//                cout<<"NAME:" << sql_row[1] << endl;
//            }
//        }
//    }
//    if (connection == NULL)
//    {
//        //unable to connect
//        printf("Oh Noes!\n");
//    }
//    else
//    {
//        printf("Connected.\n");
//    }

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
    plate.url = "test;";
    manager.uploadPlate(plate);
    manager.uploadPlate(plate);
    manager.uploadPlate(plateVector);

    return 0;
}