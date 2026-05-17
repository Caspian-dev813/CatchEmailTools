/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QTextEdit *showRes;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QProgressBar *updateProgressBar;
    QLabel *emojiLabel;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *save;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 476);
        Widget->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(140, 240, 100, 32));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 240, 100, 32));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(580, 20, 100, 32));
        showRes = new QTextEdit(Widget);
        showRes->setObjectName("showRes");
        showRes->setGeometry(QRect(280, 60, 501, 341));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(500, 30, 58, 16));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 30, 58, 16));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 60, 241, 171));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(180, 20, 100, 32));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(30, 280, 100, 32));
        updateProgressBar = new QProgressBar(Widget);
        updateProgressBar->setObjectName("updateProgressBar");
        updateProgressBar->setGeometry(QRect(80, 400, 118, 20));
        updateProgressBar->setValue(24);
        emojiLabel = new QLabel(Widget);
        emojiLabel->setObjectName("emojiLabel");
        emojiLabel->setGeometry(QRect(50, 20, 51, 31));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(670, 430, 61, 16));
        label_4 = new QLabel(Widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(740, 430, 41, 16));
        pushButton_6 = new QPushButton(Widget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(140, 280, 100, 32));
        pushButton_7 = new QPushButton(Widget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(30, 320, 100, 32));
        save = new QPushButton(Widget);
        save->setObjectName("save");
        save->setGeometry(QRect(140, 320, 100, 32));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\213\267\350\264\235", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\273\223\346\236\234\350\276\223\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\227\245\345\277\227\350\276\223\345\207\272", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\346\213\267\350\264\235", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "\346\232\202\345\201\234", nullptr));
        emojiLabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\351\202\256\347\256\261\347\273\237\350\256\241\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "\345\255\230\345\202\250", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "\350\257\264\346\230\216", nullptr));
        save->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
