//
// Created by BluesJiang on 2017/6/28.
//

#ifndef PLATERECOGNITION_PLATERECOGNISOR_H
#define PLATERECOGNITION_PLATERECOGNISOR_H

#include <vector>
#include <qstring.h>
#include <easypr.h>
#include <QDir>
#include <QFileInfoList>
#include <QObject>

class PlateRecognisor : public QObject {
    Q_OBJECT
    easypr::CPlateRecognize pr;

public:
    explicit PlateRecognisor();
    void recognizePlateInDirectory(const QString& path);
    void recognizePlateInFile(QString path, easypr::CPlate& plate);
    QString recognizePlateInFile(QString path);
    void recognizePlateInDirectory(QFileInfoList & infoList);




signals:
    void resultReady(std::vector<easypr::CPlate> retVec);

private slots:
    void handleResult(std::vector<easypr::CPlate> retVec);

};

#endif //PLATERECOGNITION_PLATERECOGNISOR_H
