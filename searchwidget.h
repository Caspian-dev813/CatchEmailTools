#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class searchWidget;
}

class searchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit searchWidget(QWidget *parent = nullptr);
    ~searchWidget();

signals:
    void back();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::searchWidget *ui;
};

#endif
