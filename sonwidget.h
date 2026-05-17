#ifndef SONWIDGET_H
#define SONWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include "searchwidget.h"

namespace Ui {
class sonWidget;
}

class sonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit sonWidget(QWidget *parent = nullptr);
    ~sonWidget();

    searchWidget *ppage3 = NULL;

signals:
    void back();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::sonWidget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // SONWIDGET_H
