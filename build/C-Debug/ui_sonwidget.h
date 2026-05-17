/********************************************************************************
** Form generated from reading UI file 'sonwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONWIDGET_H
#define UI_SONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sonWidget
{
public:
    QPushButton *pushButton;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *sonWidget)
    {
        if (sonWidget->objectName().isEmpty())
            sonWidget->setObjectName("sonWidget");
        sonWidget->resize(627, 483);
        pushButton = new QPushButton(sonWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(480, 430, 100, 32));
        tableView = new QTableView(sonWidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(50, 50, 511, 191));
        pushButton_2 = new QPushButton(sonWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 260, 100, 32));
        pushButton_3 = new QPushButton(sonWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(180, 260, 100, 32));

        retranslateUi(sonWidget);

        QMetaObject::connectSlotsByName(sonWidget);
    } // setupUi

    void retranslateUi(QWidget *sonWidget)
    {
        sonWidget->setWindowTitle(QCoreApplication::translate("sonWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("sonWidget", "\345\205\263\351\227\255", nullptr));
        pushButton_2->setText(QCoreApplication::translate("sonWidget", "\345\210\240\351\231\244", nullptr));
        pushButton_3->setText(QCoreApplication::translate("sonWidget", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sonWidget: public Ui_sonWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONWIDGET_H
