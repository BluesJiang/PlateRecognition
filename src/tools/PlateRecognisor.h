//
// Created by BluesJiang on 2017/6/28.
//

#ifndef PLATERECOGNITION_PLATERECOGNISOR_H
#define PLATERECOGNITION_PLATERECOGNISOR_H

#include <vector>
#include <qstring.h>
#include <easypr.h>

class PlateRecognisor {
    easypr::CPlateRecognize pr;
public:
    explicit PlateRecognisor();
    void recognizePlateInDirectory(QString path, std::vector<easypr::CPlate>& plates);
    void recognizePlateInFile(QString path, easypr::CPlate& plate);

};


#endif //PLATERECOGNITION_PLATERECOGNISOR_H
