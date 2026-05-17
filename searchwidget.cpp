#include "searchwidget.h"
#include "ui_searchwidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

searchWidget::searchWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::searchWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("搜索");
    this->setFixedSize(506, 417);

    QSqlDatabase db = QSqlDatabase::database("MYDB");
    if (!db.isOpen()) {
        qDebug() << "搜索窗口：数据库未打开";
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("emails");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &searchWidget::on_pushButton_2_clicked);
}

searchWidget::~searchWidget()
{
    delete ui;
}

void searchWidget::on_pushButton_2_clicked()
{
    QString key = ui->lineEdit->text().trimmed();
    QSqlDatabase db = QSqlDatabase::database("MYDB");
    QSqlTableModel *model = (QSqlTableModel*)ui->tableView->model();

    if (key.isEmpty()) {
        model->setFilter("");
        model->select();
        return;
    }

    QString filter = QString("url LIKE '%%1%' OR email LIKE '%%1%'").arg(key);
    model->setFilter(filter);
    model->select();
}

void searchWidget::on_pushButton_clicked()
{
    emit back();
}

void searchWidget::closeEvent(QCloseEvent *event)
{
    emit back();
    event->accept();
}
