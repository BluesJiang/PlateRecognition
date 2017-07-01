/********************************************************************************
** Form generated from reading UI file 'RecognizeTab.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOGNIZETAB_H
#define UI_RECOGNIZETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecognizeTab
{
public:
    QLabel *label;
    QTableView *tableView;
    QPushButton *importButton;
    QPushButton *recognizeButton;
    QPushButton *uploadButton;

    void setupUi(QWidget *RecognizeTab)
    {
        if (RecognizeTab->objectName().isEmpty())
            RecognizeTab->setObjectName(QStringLiteral("RecognizeTab"));
        RecognizeTab->resize(1050, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RecognizeTab->sizePolicy().hasHeightForWidth());
        RecognizeTab->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        font.setFamily("华文黑体");
        label = new QLabel(RecognizeTab);
        label->setFont(font);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 50, 285, 410));
        tableView = new QTableView(RecognizeTab);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(410, 50, 600, 410));
        importButton = new QPushButton(RecognizeTab);
        importButton->setObjectName(QStringLiteral("importButton"));
        importButton->setGeometry(QRect(403, 20, 100, 32));
        recognizeButton = new QPushButton(RecognizeTab);
        recognizeButton->setObjectName(QStringLiteral("recognizeButton"));
        recognizeButton->setGeometry(QRect(510, 20, 100, 32));
        uploadButton = new QPushButton(RecognizeTab);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setGeometry(QRect(616, 20, 100, 32));

        retranslateUi(RecognizeTab);
        QObject::connect(importButton, SIGNAL(clicked()), RecognizeTab, SLOT(import()));
        QObject::connect(recognizeButton, SIGNAL(clicked()), RecognizeTab, SLOT(recognize()));
        QObject::connect(uploadButton, SIGNAL(clicked()), RecognizeTab, SLOT(upload()));

        QMetaObject::connectSlotsByName(RecognizeTab);
    } // setupUi

    void retranslateUi(QWidget *RecognizeTab)
    {
        RecognizeTab->setWindowTitle(QApplication::translate("RecognizeTab", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("RecognizeTab", "TextLabel", Q_NULLPTR));
        importButton->setText(QApplication::translate("RecognizeTab", "\345\257\274\345\205\245", Q_NULLPTR));
        recognizeButton->setText(QApplication::translate("RecognizeTab", "\350\257\206\345\210\253", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("RecognizeTab", "\344\270\212\344\274\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RecognizeTab: public Ui_RecognizeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOGNIZETAB_H
