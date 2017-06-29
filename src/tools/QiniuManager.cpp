//
// Created by CGJ on 2017/6/29.
//

#include "QiniuManager.h"
//using namespace std;

void  debuginfo(Qiniu_Client* client, Qiniu_Error err)
{
    printf("\nerror code: %d, message: %s\n", err.code, err.message);
    printf("response header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
    printf("response body:\n%s", Qiniu_Buffer_CStr(&client->b));
    printf("\n\n\n");
}

char*  upLoadToken(const char* bucket, Qiniu_Mac* mac)
{
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Zero(putPolicy);
    putPolicy.scope = bucket;
    return Qiniu_RS_PutPolicy_Token(&putPolicy, mac);
}

void QiniuManager::uploadFile(Qiniu_Client *pClient, const char *bucketName, Qiniu_Mac *mac) {
    char* uploadtoken = upLoadToken(bucketName, mac);
    std::string uploadName[2] = {"jikeup3.jpg","jikeup4.jpg"};
    for(int i=0;i<2;i++){
        /*得到uploadKey*/

        std::string pLocalFile = "/Users/cgj/Desktop/upload/";
        std::string pLocalFilePath = pLocalFile + uploadName[i];

        Qiniu_Io_PutRet putRet;
        Qiniu_Error error = Qiniu_Io_PutFile(pClient, &putRet, uploadtoken, uploadName[i].c_str(), pLocalFilePath.c_str(), NULL);
        if (error.code != 200)
        {
            printf("Upload File %s To %s:%s error.\n", pLocalFilePath.c_str(), bucketName,  uploadName[i].c_str());
            debuginfo(pClient, error);
        }
        else
        {
            printf("Upload File %s To %s:%s success.\n", pLocalFilePath.c_str(), bucketName,  uploadName[i].c_str());
//            printf("uploadtoken: %s ",uploadtoken);
        }

    }

    Qiniu_Free(uploadtoken);
}

QiniuManager::QiniuManager() {

}

