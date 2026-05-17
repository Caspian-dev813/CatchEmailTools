/********************************************************************************
** Form generated from reading UI file 'cheakupdatewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHEAKUPDATEWIDGET_H
#define UI_CHEAKUPDATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cheakUpdateWidget
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *cheakUpdateWidget)
    {
        if (cheakUpdateWidget->objectName().isEmpty())
            cheakUpdateWidget->setObjectName("cheakUpdateWidget");
        cheakUpdateWidget->resize(493, 216);
        pushButton = new QPushButton(cheakUpdateWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 50, 191, 32));
        lineEdit = new QLineEdit(cheakUpdateWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(160, 100, 211, 21));
        pushButton_2 = new QPushButton(cheakUpdateWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 90, 100, 41));
        progressBar = new QProgressBar(cheakUpdateWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(120, 140, 161, 23));
        progressBar->setValue(24);
        label = new QLabel(cheakUpdateWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 140, 91, 16));

        retranslateUi(cheakUpdateWidget);

        QMetaObject::connectSlotsByName(cheakUpdateWidget);
    } // setupUi

    void retranslateUi(QWidget *cheakUpdateWidget)
    {
        cheakUpdateWidget->setWindowTitle(QCoreApplication::translate("cheakUpdateWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("cheakUpdateWidget", "\346\243\200\346\237\245\346\233\264\346\226\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("cheakUpdateWidget", "\344\270\213\350\275\275\345\271\266\345\256\211\350\243\205", nullptr));
        label->setText(QCoreApplication::translate("cheakUpdateWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cheakUpdateWidget: public Ui_cheakUpdateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHEAKUPDATEWIDGET_H
