//
// Created by BluesJiang on 2017/6/29.
//

#include "PlateModel.h"

using std::cout;
using std::endl;

PlateModel::PlateModel(const std::string &plate, const std::string &url, const std::string &owner ) : owner(owner),
                                                                                                     plate(plate),
                                                                                                     url(url) {}
PlateModel::PlateModel() : owner(""), plate(""), url("") {}

void PlateModel::description() {
    std::string des = "{\n\towner : " + owner + "\n\tplate : " + plate + "\n\turl : " + url + "\n}";
    cout << des.c_str() << endl;

}

PlateModel::PlateModel(const PlateModel &plate) {
    this->owner = plate.owner;
    this->plate = plate.plate;
    this->url = plate.url;
}

std::string PlateModel::packForSQLValues() const {
    return "("+plate+","+owner+",'"+url+"')";
}
