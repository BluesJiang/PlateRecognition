//
// Created by BluesJiang on 2017/6/28.
//

#include "PlateRecognisor.h"
#include <QThread>



using namespace easypr;

class RecognizeWorker : public QThread {
    Q_OBJECT
    QFileInfoList & infoList;
public:
    explicit RecognizeWorker(QFileInfoList & infoList, QObject *parent = 0)
    : QThread(parent), infoList(infoList)
    {

    }
protected:
    virtual void run() Q_DECL_OVERRIDE {
        emit started();
        CPlateRecognize pr;
        pr.setResultShow(false);
        pr.setDetectType(PR_DETECT_CMSER|PR_DETECT_SOBEL|PR_DETECT_SOBEL);
        pr.setLifemode(true);
        pr.setMaxPlates(1);
        std::vector<CPlate> resultVec;
        for (auto fileInfo : infoList) {
            std::vector<CPlate> plateVec;
            cv::Mat img = cv::imread(fileInfo.absoluteFilePath().toStdString().c_str());
            int result = pr.plateRecognize(img, plateVec);
            if (result == 0 && plateVec.size() == 1) {
                CPlate plate = plateVec.at(0);
                resultVec.push_back(plate);
            }
        }
        emit resultReady(resultVec);

    }

public:
signals:
    void started();
    void resultReady(std::vector<easypr::CPlate>);
};


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

    RecognizeWorker* worker = new RecognizeWorker(infoList, this);
    connect(worker, SIGNAL(resultReady(std::vector<easypr::CPlate>)), this, SLOT(handleResult(std::vector<easypr::CPlate>)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();

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

    std::vector<easypr::CPlate> plateVec;
    cv::Mat img = cv::imread(path.toStdString().c_str());
    int result = pr.plateRecognize(img, plateVec);
    QString plateStr;
    plateStr = QString::fromStdString(plateVec.at(0).getPlateStr());
    if (result == 0 && plateVec.size() == 1) {
       return plateStr;
    }

}

void PlateRecognisor::handleResult(vector<CPlate> retVec) {
    emit resultReady(retVec);
}


#include "PlateRecognisor.moc"


