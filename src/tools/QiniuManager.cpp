//
// Created by CGJ on 2017/6/29.
//

#include "QiniuManager.h"
//using namespace std;

void  QiniuManager::debuginfo(Qiniu_Client* client, Qiniu_Error err)
{
    printf("\nerror code: %d, message: %s\n", err.code, err.message);
    printf("response header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
    printf("response body:\n%s", Qiniu_Buffer_CStr(&client->b));
    printf("\n\n\n");
}

char*  QiniuManager::upLoadToken(const char* bucket, Qiniu_Mac* mac)
{
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Zero(putPolicy);
    putPolicy.scope = bucket;
    return Qiniu_RS_PutPolicy_Token(&putPolicy, mac);
}

int QiniuManager::uploadFile(std::vector<PlateModel> inputVec,std::vector<PlateModel>& retVec) {
    Qiniu_Client client;
    Qiniu_Mac mac;
    const  char* bucketName = "cpptest";

    mac.accessKey = "QC3MrjeF38x1iUIdVBRVRVnlmZYOlqFRQy2PQ4pK";
    mac.secretKey = "l5hMWe_svAcifqy4zLjcScov18FAX75Xm9STxyLd";
    // 初始化
    Qiniu_Servend_Init(-1);
    Qiniu_Client_InitMacAuth(&client, 1024, &mac);

    char* uploadtoken = upLoadToken(bucketName, &mac);
//    std::string uploadName[2] = {"jikeup3.jpg","jikeup4.jpg"};
    // int i=0;
    for (auto plate : inputVec){
        uuid_t uuid;
        char str[36];
        std::string pLocalFilePath = plate.url;
        uuid_generate(uuid);
        uuid_unparse(uuid, str);
        // plate = inputaVec[i].
        plate.url = str ;
        // std::string newUrl = plate.url+";";
        plate.url = "http://osabw6t6t.bkt.clouddn.com/"+plate.url;
        retVec.push_back(plate);
        Qiniu_Io_PutRet putRet;
        Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uploadtoken, str, pLocalFilePath.c_str(), NULL);
        if (error.code != 200)
        {
            printf("Upload File %s To %s:%s error.\n", pLocalFilePath.c_str(), bucketName, (plate.url).c_str());
            debuginfo(&client, error);
        }
        else
        {
            printf("Upload File %s To %s:%s success.\n", pLocalFilePath.c_str(), bucketName, (plate.url).c_str());
//            printf("uploadtoken: %s ",uploadtoken);
        }
        // i++;

    }
//    for(int i=0;i<2;i++){
//        /*得到uploadKey*/
//
//        std::string pLocalFile = "/Users/cgj/Desktop/upload/";
//        std::string pLocalFilePath = pLocalFile + uploadName[i];
//
//        Qiniu_Io_PutRet putRet;
//        Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uploadtoken, uploadName[i].c_str(), pLocalFilePath.c_str(), NULL);
//        if (error.code != 200)
//        {
//            printf("Upload File %s To %s:%s error.\n", pLocalFilePath.c_str(), bucketName,  uploadName[i].c_str());
//            debuginfo(&client, error);
//        }
//        else
//        {
//            printf("Upload File %s To %s:%s success.\n", pLocalFilePath.c_str(), bucketName,  uploadName[i].c_str());
////            printf("uploadtoken: %s ",uploadtoken);
//        }
//
//    }

    Qiniu_Free(uploadtoken);
};

int QiniuManager::uploadFile(PlateModel inPlate, PlateModel & retPlate) {
    Qiniu_Client client;
    Qiniu_Mac mac;
    const  char* bucketName = "cpptest";

    mac.accessKey = "QC3MrjeF38x1iUIdVBRVRVnlmZYOlqFRQy2PQ4pK";
    mac.secretKey = "l5hMWe_svAcifqy4zLjcScov18FAX75Xm9STxyLd";
    // 初始化
    Qiniu_Servend_Init(-1);
    Qiniu_Client_InitMacAuth(&client, 1024, &mac);

    char* uploadtoken = upLoadToken(bucketName, &mac);
//    std::string uploadName[2] = {"jikeup3.jpg","jikeup4.jpg"};
    // int i=0;

        uuid_t uuid;
        char str[36];
        std::string pLocalFilePath = inPlate.url;
        uuid_generate(uuid);
        uuid_unparse(uuid, str);
        // inPlate = inputaVec[i].
        inPlate.url = str ;
        // std::string newUrl = inPlate.url+";";
        inPlate.url = "http://osabw6t6t.bkt.clouddn.com/"+inPlate.url;
        retPlate=inPlate;
        Qiniu_Io_PutRet putRet;
        Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uploadtoken, str, pLocalFilePath.c_str(), NULL);
        if (error.code != 200)
        {
            printf("Upload File %s To %s:%s error.\n", pLocalFilePath.c_str(), bucketName, (inPlate.url).c_str());
            debuginfo(&client, error);
        }
        else
        {
            printf("Upload File %s To %s:%s success.\n", pLocalFilePath.c_str(), bucketName, (inPlate.url).c_str());
//            printf("uploadtoken: %s ",uploadtoken);
        }
        // i++;


    Qiniu_Free(uploadtoken);
};

QiniuManager::QiniuManager() {

};
