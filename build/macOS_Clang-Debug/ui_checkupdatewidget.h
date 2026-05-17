/********************************************************************************
** Form generated from reading UI file 'checkupdatewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKUPDATEWIDGET_H
#define UI_CHECKUPDATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_checkUpdateWidget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *checkUpdateWidget)
    {
        if (checkUpdateWidget->objectName().isEmpty())
            checkUpdateWidget->setObjectName("checkUpdateWidget");
        checkUpdateWidget->resize(516, 233);
        pushButton = new QPushButton(checkUpdateWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(220, 40, 100, 32));
        pushButton_2 = new QPushButton(checkUpdateWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(70, 90, 101, 41));
        lineEdit = new QLineEdit(checkUpdateWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 90, 141, 41));
        label = new QLabel(checkUpdateWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(340, 150, 71, 21));
        progressBar = new QProgressBar(checkUpdateWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(180, 150, 141, 23));
        progressBar->setValue(24);

        retranslateUi(checkUpdateWidget);

        QMetaObject::connectSlotsByName(checkUpdateWidget);
    } // setupUi

    void retranslateUi(QWidget *checkUpdateWidget)
    {
        checkUpdateWidget->setWindowTitle(QCoreApplication::translate("checkUpdateWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("checkUpdateWidget", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("checkUpdateWidget", "\344\270\213\350\275\275\345\271\266\345\256\211\350\243\205", nullptr));
        label->setText(QCoreApplication::translate("checkUpdateWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class checkUpdateWidget: public Ui_checkUpdateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKUPDATEWIDGET_H
