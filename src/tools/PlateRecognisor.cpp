//
// Created by BluesJiang on 2017/6/28.
//

#include "PlateRecognisor.h"
#include <sys/types.h>
#include <dirent.h>


using namespace easypr;

PlateRecognisor::PlateRecognisor() {
    pr.setResultShow(false);
    pr.setDetectType(PR_DETECT_CMSER|PR_DETECT_SOBEL|PR_DETECT_SOBEL);
    pr.setLifemode(true);
    pr.setMaxPlates(1);
}

void PlateRecognisor::recognizePlateInDirectory(QString path, std::vector<CPlate>& plates) {
    std::string stdpath = path.toStdString();
    DIR* dir = opendir(stdpath.c_str());
    struct dirent* ptr = NULL;
    while ((ptr = readdir(dir)) != NULL) {
        if (ptr->d_name[0] == '.') {
            continue;
        }

        QString str(ptr->d_name);
        if (str.endsWith(".jpg")) {
            QString name = path + str;
            std::cout << name.toStdString().c_str() << std::endl;
            CPlate plate;
            recognizePlateInFile(name, plate);
            plates.push_back(plate);
        }

    }


}

void PlateRecognisor::recognizePlateInFile(QString path, CPlate& plate) {

    std::vector<CPlate> plateVec;
    cv::Mat img = cv::imread(path.toStdString().c_str());
    int result = pr.plateRecognize(img, plateVec);
    if (result == 0 && plateVec.size() == 1) {
        plate = plateVec.at(0);
    }

}