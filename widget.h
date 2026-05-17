#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <unordered_set>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class sonWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    std::string cleanUrl(const std::string& url);
    void updateStatisticsLabel();
    void logToTextEdit(const QString& logMsg);
    void updateProgressBar();
    void detectCycle();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::Widget *ui;
    QTimer *detectTimer;
    QTimer *progressTimer;
    sonWidget *ppage2;
    bool isPaused;
    int progressValue;
    bool isCleared;
    int totalEmailCount;
    std::string lastUrl;
    std::unordered_set<std::string> processedUrls;
    std::unordered_set<QString> loggedMessages;
};

#endif // WIDGET_H
