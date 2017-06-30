/********************************************************************************
** Form generated from reading UI file 'SearchWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QRadioButton *plateRadioButton;
    QRadioButton *nameRadioButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLabel *label;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName(QStringLiteral("SearchWindow"));
        SearchWindow->resize(1013, 646);
        centralwidget = new QWidget(SearchWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(620, 110, 321, 441));
        plateRadioButton = new QRadioButton(centralwidget);
        buttonGroup = new QButtonGroup(SearchWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(plateRadioButton);
        plateRadioButton->setObjectName(QStringLiteral("plateRadioButton"));
        plateRadioButton->setGeometry(QRect(620, 40, 141, 20));
        nameRadioButton = new QRadioButton(centralwidget);
        buttonGroup->addButton(nameRadioButton);
        nameRadioButton->setObjectName(QStringLiteral("nameRadioButton"));
        nameRadioButton->setGeometry(QRect(740, 40, 141, 20));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(620, 70, 221, 31));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(840, 70, 101, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(49, 75, 481, 311));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(50, 410, 481, 131));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        SearchWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SearchWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1013, 22));
        SearchWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SearchWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SearchWindow->setStatusBar(statusbar);

        retranslateUi(SearchWindow);
        QObject::connect(pushButton_2, SIGNAL(clicked()), SearchWindow, SLOT(searchAndShow()));
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), SearchWindow, SLOT(display(QListWidgetItem*)));
        QObject::connect(buttonGroup, SIGNAL(buttonPressed(QAbstractButton*)), SearchWindow, SLOT(enablesearch()));

        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SearchWindow)
    {
        SearchWindow->setWindowTitle(QApplication::translate("SearchWindow", "MainWindow", Q_NULLPTR));
        plateRadioButton->setText(QApplication::translate("SearchWindow", "\344\275\277\347\224\250\350\275\246\347\211\214\346\237\245\350\257\242", Q_NULLPTR));
        nameRadioButton->setText(QApplication::translate("SearchWindow", "\344\275\277\347\224\250\350\275\246\344\270\273\345\247\223\345\220\215\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SearchWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
