/********************************************************************************
** Form generated from reading UI file 'SearchTab.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHTAB_H
#define UI_SEARCHTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchTab
{
public:
    QLabel *label;
    QListWidget *listWidget;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QPushButton *searchButton;
    QRadioButton *plateRadioButton;
    QRadioButton *nameRadioButton;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SearchTab)
    {
        if (SearchTab->objectName().isEmpty())
            SearchTab->setObjectName(QStringLiteral("SearchTab"));
        SearchTab->resize(1050, 500);
        label = new QLabel(SearchTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 40, 441, 421));
        listWidget = new QListWidget(SearchTab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(40, 40, 151, 421));
        tableView = new QTableView(SearchTab);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(710, 80, 301, 381));
        lineEdit = new QLineEdit(SearchTab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(710, 40, 231, 31));
        searchButton = new QPushButton(SearchTab);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(950, 36, 61, 42));
        plateRadioButton = new QRadioButton(SearchTab);
        buttonGroup = new QButtonGroup(SearchTab);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(plateRadioButton);
        plateRadioButton->setObjectName(QStringLiteral("plateRadioButton"));
        plateRadioButton->setGeometry(QRect(710, 10, 121, 20));
        nameRadioButton = new QRadioButton(SearchTab);
        buttonGroup->addButton(nameRadioButton);
        nameRadioButton->setObjectName(QStringLiteral("nameRadioButton"));
        nameRadioButton->setGeometry(QRect(880, 10, 131, 20));

        retranslateUi(SearchTab);
        QObject::connect(searchButton, SIGNAL(clicked()), SearchTab, SLOT(searchAndShow()));
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), SearchTab, SLOT(display(QListWidgetItem*)));
        QObject::connect(buttonGroup, SIGNAL(buttonPressed(QAbstractButton*)), SearchTab, SLOT(enableSearchButton()));

        QMetaObject::connectSlotsByName(SearchTab);
    } // setupUi

    void retranslateUi(QWidget *SearchTab)
    {
        SearchTab->setWindowTitle(QApplication::translate("SearchTab", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("SearchTab", "TextLabel", Q_NULLPTR));
        searchButton->setText(QApplication::translate("SearchTab", "\346\237\245\350\257\242", Q_NULLPTR));
        plateRadioButton->setText(QApplication::translate("SearchTab", "\344\275\277\347\224\250\350\275\246\347\211\214\345\217\267\346\237\245\350\257\242", Q_NULLPTR));
        nameRadioButton->setText(QApplication::translate("SearchTab", "\344\275\277\347\224\250\350\275\246\344\270\273\345\247\223\345\220\215\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SearchTab: public Ui_SearchTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHTAB_H
