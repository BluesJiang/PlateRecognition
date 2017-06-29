//
// Created by BluesJiang on 2017/6/29.
//

#ifndef PLATERECOGNITION_PLATEMODEL_H
#define PLATERECOGNITION_PLATEMODEL_H

#include <iostream>

class PlateModel {

public:
    std::string owner;
    std::string plate;
    std::string url;
    PlateModel();
    PlateModel(const std::string &plate, const std::string &url, const std::string &owner);
    void description();
};


#endif //PLATERECOGNITION_PLATEMODEL_H
