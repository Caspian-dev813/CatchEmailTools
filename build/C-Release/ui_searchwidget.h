/********************************************************************************
** Form generated from reading UI file 'searchwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWIDGET_H
#define UI_SEARCHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchWidget
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;
    QTableView *tableView;
    QLineEdit *lineEdit;

    void setupUi(QWidget *searchWidget)
    {
        if (searchWidget->objectName().isEmpty())
            searchWidget->setObjectName("searchWidget");
        searchWidget->resize(512, 416);
        pushButton = new QPushButton(searchWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(370, 330, 100, 32));
        label = new QLabel(searchWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 20, 31, 16));
        pushButton_2 = new QPushButton(searchWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 330, 100, 32));
        tableView = new QTableView(searchWidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(30, 70, 451, 241));
        lineEdit = new QLineEdit(searchWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(370, 20, 113, 21));

        retranslateUi(searchWidget);

        QMetaObject::connectSlotsByName(searchWidget);
    } // setupUi

    void retranslateUi(QWidget *searchWidget)
    {
        searchWidget->setWindowTitle(QCoreApplication::translate("searchWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("searchWidget", "\345\205\263\351\227\255", nullptr));
        label->setText(QCoreApplication::translate("searchWidget", "\346\237\245\346\211\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("searchWidget", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class searchWidget: public Ui_searchWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWIDGET_H
