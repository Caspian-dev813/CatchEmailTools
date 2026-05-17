#include "sonwidget.h"
#include "ui_sonwidget.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include "searchwidget.h"

sonWidget::sonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sonWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("存储设置");
    this->setFixedSize(627, 515);

    ppage3 = nullptr;

    if (QSqlDatabase::contains("MYDB")) {
        db = QSqlDatabase::database("MYDB");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", "MYDB");
        db.setDatabaseName("email_data.db");
        db.open();

        QSqlQuery query(db);
        query.exec(R"(
            CREATE TABLE IF NOT EXISTS emails (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                url TEXT,
                email TEXT,
                create_time TEXT
            )
        )");
    }

    model = new QSqlTableModel(this, db);
    model->setTable("emails");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

sonWidget::~sonWidget()
{
    delete ui;/*
    if (ppage3 != nullptr) {
        delete ppage3;
    }*/
}

void sonWidget::on_pushButton_clicked()
{
    emit back();
}

void sonWidget::on_pushButton_2_clicked()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if (!idx.isValid()) {
        QMessageBox::warning(this, "提示", "请选择一行！");
        return;
    }

    if (QMessageBox::question(this, "删除", "确定删除？") != QMessageBox::Yes) {
        return;
    }

    int id = idx.sibling(idx.row(), 0).data().toInt();
    QSqlQuery q(db);
    q.prepare("DELETE FROM emails WHERE id = ?");
    q.addBindValue(id);
    q.exec();

    model->select();
}

void sonWidget::on_pushButton_3_clicked()
{
    if (ppage3 == nullptr) {
        ppage3 = new searchWidget(this);
        ppage3->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
        connect(ppage3, &searchWidget::destroyed, this, [=](){
            ppage3 = nullptr;
        });
        connect(ppage3, &searchWidget::back, this, [=](){
            ppage3->close();
        });
    }
    if (ppage3->isHidden()) {
        ppage3->show();
    } else {
        ppage3->raise();
    }
}

void sonWidget::closeEvent(QCloseEvent *event)
{
    emit back();
    event->accept();
}
