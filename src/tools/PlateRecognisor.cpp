//
// Created by BluesJiang on 2017/6/28.
//

#include "PlateRecognisor.h"
#include <QTimer>


using namespace easypr;

PlateRecognisor::PlateRecognisor() {
    pr.setResultShow(false);
    pr.setDetectType(PR_DETECT_CMSER|PR_DETECT_SOBEL|PR_DETECT_SOBEL);
    pr.setLifemode(true);
    pr.setMaxPlates(1);
}

void PlateRecognisor::recognizePlateInDirectory(const QString& path, std::vector<CPlate>& plates) {
    std::string stdpath = path.toStdString();
    QDir dir(path);
    dir.setFilter(QDir::Files);
    QStringList filters;
    filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png");
    dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList();
    recognizePlateInDirectory(list, plates);

}

void PlateRecognisor::recognizePlateInDirectory(QFileInfoList & infoList, std::vector<CPlate>& plates) {
    for(int i = 0; i < infoList.size(); i++)
    {
        CPlate plate;
        recognizePlateInFile(infoList[i].filePath(), plate);
        plates.push_back(plate);
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

QString PlateRecognisor::recognizePlateInFile(QString path) {

    std::vector<CPlate> plateVec;
    cv::Mat img = cv::imread(path.toStdString().c_str());
    int result = pr.plateRecognize(img, plateVec);
    QString plateStr;
    plateStr = QString::fromStdString(plateVec.at(0).getPlateStr());
    if (result == 0 && plateVec.size() == 1) {
       return plateStr;
    }

}






