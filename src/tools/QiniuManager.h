//
// Created by CGJ on 2017/6/29.
//

#ifndef PLATERECOGNITION_QINIUMANAGER_H
#define PLATERECOGNITION_QINIUMANAGER_H

#include <vector>
#include <PlateModel.h>
#include <iostream>
#include <QObject>
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "qiniu/base.h"
#include "qiniu/resumable_io.h"
#include <uuid/uuid.h>
class QiniuManager : public QObject {
    Q_OBJECT

public:
    explicit QiniuManager();
//    void uploadFile(Qiniu_Client* pClient, const char* bucketName, Qiniu_Mac* mac, <vector>* plateVevtor);
//    char* upLoadToken(const char* bucket, Qiniu_Mac* mac);
//    int uploadFile(std::vector<PlateModel>& retVec);

    int uploadFile(std::vector<PlateModel, std::allocator<PlateModel>> inputVec);
    int uploadFile(PlateModel inPlate, PlateModel & retPlate);

private:
    void  debuginfo(Qiniu_Client* client, Qiniu_Error err);
    char* upLoadToken(const char* bucket, Qiniu_Mac* mac);


signals:
    void resultReady(std::vector<PlateModel> );

private slots:
    void handleResult(std::vector<PlateModel> );

};


#endif //PLATERECOGNITION_QINIUMANAGER_H
