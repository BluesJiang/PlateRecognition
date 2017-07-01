//
// Created by BluesJiang on 2017/6/29.
//

#include "DataManager.h"


DataManager::DataManager():ip("123.207.59.11"), user("root"), pwd("5Believe!!"), dbname("PlateRecognition") {
    mysql_init(&mysql);
    mysql_set_character_set(&mysql, "utf8");
    qiniuManager = new QiniuManager();
}

DataManager::~DataManager() {
    mysql_close(connect);
    delete qiniuManager;
}


std::string DataManager::queryPassword(std::string username) {
    connectDB();
    std::string sql_query = "select password from User where username=\"" + username + "\"";

    int res = mysql_query(&mysql, sql_query.c_str());
    if (!res) {
        MYSQL_RES* result = mysql_store_result(&mysql);
        MYSQL_ROW result_row;
        if (result) {
            if ((result_row = mysql_fetch_row(result))) {
                return std::string(result_row[0]);
            }
        }
    }
    return "";
}

int DataManager::updatePassword(std::string username, std::string newPassword) {
    connectDB();
    std::string sql_query = "update User set password='" + newPassword + "' where username=\"" + username + "\"";
    return mysql_query(&mysql, sql_query.c_str());
}

int DataManager::queryPlateInfoWithOwner(std::string owner, PlateModel &retPlate) {
    return queryPlateInfo("owner", owner, retPlate);
}

int DataManager::queryPlateInfoWithOwner(std::string owner, std::vector<PlateModel> &retVec) {
    std::string sql_query = "select * from PlateInfo where owner=\"" + owner +"\"";
    return queryMultiObject(sql_query, retVec);
}

int DataManager::queryPlateInfoWithPlate(std::string plate, PlateModel &retPlate) {
    return queryPlateInfo("plate", plate, retPlate);
}
int DataManager::queryPlateInfoWithPlate(std::string plate, std::vector<PlateModel> &retVec) {
    std::string sql_query = "select * from PlateInfo where owner=\"" + plate +"\"";
    return queryMultiObject(sql_query, retVec);
}

int DataManager::queryPlateInfo(std::string ownerOrPlate, std::string key, PlateModel &retPlate) {
    std::string sql_query = "select * from PlateInfo where "+ownerOrPlate+"=\"" + key+ "\"";
    return querySingleObject(sql_query, retPlate);

}

int DataManager::querySingleObject(std::string sql_str, PlateModel &retPlate) {
    connectDB();
    int res = mysql_query(&mysql, sql_str.c_str());
    if (!res) {
        MYSQL_RES* result = mysql_store_result(&mysql);
        MYSQL_ROW result_row;
        if (result) {
            if ((result_row = mysql_fetch_row(result))) {
                retPlate.plate = result_row[1];
                retPlate.owner = result_row[2];
                retPlate.url = result_row[3];
                return 0;
            }
        }
    }
    return -1;
}

void DataManager::connectDB() {
    static bool onceToken = 1;
    if (onceToken) {
//        onceToken = 0;
        connect = mysql_real_connect(&mysql, ip.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, 0, 0);
    }
}

int DataManager::reconnectDB() {
    for (int i = 0; i < 5; ++i) {
        if ((connect = mysql_real_connect(&mysql, ip.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, 0, 0))){
            return 0;
        }
    }
    return -1;
}

int DataManager::queryPlateInfoWithOwners(std::vector<std::string> owners, std::vector<PlateModel> &retVec) {
    return queryPlateInfo("owner", owners, retVec);
}

int DataManager::queryPlateInfoWithPlates(std::vector<std::string> plates, std::vector<PlateModel> &retVec) {
    return queryPlateInfo("plate", plates, retVec);
}

int DataManager::queryPlateInfoWithPlateKeyword(std::string keyword, std::vector<PlateModel> &retVec) {
    std::string sql_query = "select * from PlateInfo where plate like '%" + keyword + "%' ";
    return queryMultiObject(sql_query, retVec);
}

int DataManager::queryMultiObject(std::string sql_query, std::vector<PlateModel, std::allocator<PlateModel>>& retVec) {
    connectDB();
    std::cout << sql_query << std::endl;
    int res = mysql_query(&mysql, sql_query.c_str());
    if (!res) {
        MYSQL_RES* result = mysql_store_result(&mysql);
        MYSQL_ROW result_row;
        int count = 0;
        if (result) {
            while ((result_row = mysql_fetch_row(result))) {
                PlateModel plate;
                plate.plate = result_row[1];
                plate.owner = result_row[2];
                plate.url = result_row[3];
                retVec.push_back(plate);
                count++;
            }
        }
        return count;
    }
    return -1;

}

int DataManager::queryPlateInfo(std::string ownerOrPlate, std::vector<std::string> keys, std::vector<PlateModel> &retVec) {
    std::string sql_query = "select * from PlateInfo where " + ownerOrPlate
                            + " in (";
    for (auto val : keys) {
        sql_query += "\"" + val + "\"" + ",";
    }
    sql_query[sql_query.length()-1] = ')';
    return queryMultiObject(sql_query, retVec);
}

int DataManager::uploadPlate(const PlateModel &plate) {
    PlateModel tmpPlate, retPlate;
    qiniuManager->uploadFile(plate, retPlate);
    int res = queryPlateInfoWithPlate(plate.plate, tmpPlate);
    std::string sql_query;
    if (!res) {
        sql_query = "update PlateInfo set images='";
        if (tmpPlate.url != "") {
            tmpPlate.url += ";" + retPlate.url;
        } else {
            tmpPlate.url = retPlate.url;
        }
        sql_query += tmpPlate.url;
        sql_query += "' where plate="+tmpPlate.plate;
    } else {
        sql_query = "insert into PlateInfo (plate, owner, images) values ";
        sql_query += plate.packForSQLValues();
    }

    return updateDB(sql_query);
}

int DataManager::uploadPlate(const std::vector<PlateModel> &plates) {
    std::vector<PlateModel> retVec;
    qiniuManager->uploadFile(plates, retVec);
    std::string sql_query;
    int count = 0;
    for (auto plate : retVec) {
        PlateModel tmpPlate;
        int res = queryPlateInfoWithPlate(plate.plate, tmpPlate);
        if (!res) {
            sql_query = "update PlateInfo set images='";
            if (tmpPlate.url != "") {
                tmpPlate.url += ";" + plate.url;
            } else {
                tmpPlate.url = plate.url;
            }
            sql_query += tmpPlate.url;
            sql_query += "' where plate="+tmpPlate.plate;
            if(updateDB(sql_query) == 0) {
                count++;
            }

        } else {
            sql_query = "insert into PlateInfo (plate, owner, images) values ";
            sql_query += plate.packForSQLValues();
            if(updateDB(sql_query) == 0) {
                count++;
            }
        }
    }
    return count;
}

int DataManager::updateDB(std::string sql_str) {
    connectDB();
    int res = mysql_query(&mysql, sql_str.c_str());
    if (!res) {
        return 0;
    }
    return -1;
}



















