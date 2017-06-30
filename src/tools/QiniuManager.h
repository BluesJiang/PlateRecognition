//
// Created by CGJ on 2017/6/29.
//

#ifndef PLATERECOGNITION_QINIUMANAGER_H
#define PLATERECOGNITION_QINIUMANAGER_H

#include <vector>

#include <PlateModel.h>
#include <iostream>
//#include <QApplication>
//#include "MainWindow.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
//#include <stdio.h>
#include <uuid/uuid.h>
class QiniuManager {

public:
    explicit QiniuManager();
//    void uploadFile(Qiniu_Client* pClient, const char* bucketName, Qiniu_Mac* mac, <vector>* plateVevtor);
//    char* upLoadToken(const char* bucket, Qiniu_Mac* mac);
//    int uploadFile(std::vector<PlateModel>& retVec);

    int uploadFile(std::vector<PlateModel, std::allocator<PlateModel>> inputVec,
                   std::vector<PlateModel, std::allocator<PlateModel>> &retVec);
    int uploadSingleFile(PlateModel inPlate, PlateModel & retPlate);

private:
    void  debuginfo(Qiniu_Client* client, Qiniu_Error err);
    char*  upLoadToken(const char* bucket, Qiniu_Mac* mac);
};


#endif //PLATERECOGNITION_QINIUMANAGER_H
