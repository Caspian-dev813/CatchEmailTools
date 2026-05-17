#include "widget.h"
#include "ui_widget.h"
#include <QClipboard>
#include <QApplication>
#include <QTextCursor>
#include <algorithm>
#include "sonwidget.h"
#include <QMessageBox>
#include <string>
#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QPushButton>
#include <QEvent>
#include <QToolTip>
#include <QDateTime>
#include <QTimer>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <curl/curl.h>
#include <cstring>
#include <regex>
#include <set>
#include <unistd.h>
#include <QSettings>
#include <QCheckBox>

// std::string get_chrome_url() {
//     const char* script = R"(
//         tell application "Google Chrome"
//             if (count of windows) > 0 then
//                 set activeWin to front window
//                 set activeTab to active tab of activeWin
//                 return URL of activeTab
//             else
//                 return "ERROR: Chrome无打开窗口"
//             end if
//         end tell
//     )";

//     std::string cmd = "osascript -e '" + std::string(script) + "'";
//     FILE* pipe = popen(cmd.c_str(), "r");
//     if (!pipe) {
//         return "ERROR: 执行AppleScript失败";
//     }

//     char buffer[2048] = {0};
//     std::stringstream ss;
//     while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
//         ss << buffer;
//     }
//     pclose(pipe);

//     std::string url = ss.str();
//     url.erase(std::remove_if(url.begin(), url.end(), [](unsigned char c) {
//                   return std::isspace(c);
//               }), url.end());

//     if (url.empty() || url.find("ERROR:") != std::string::npos) {
//         return url.empty() ? "ERROR: 未获取到URL" : url;
//     }
//     return url;
// }
using namespace std;
int x;

size_t write_data(void *ptr, size_t size, size_t nmemb, string *data) {
    if (!data) {
        return 0;
    }
    size_t realsize = size * nmemb;
    data->append((char *)ptr, realsize);
    return realsize;
}

string get_edge_url() {
    const char* edgeScript = R"(
        osascript -e 'tell application "Microsoft Edge"
            if (count of windows) = 0 then return "ERROR: No windows open"
            set currentWindow to front window
            if (count of tabs of currentWindow) = 0 then return "ERROR: No tabs open"
            set currentTab to active tab of currentWindow
            set pageURL to URL of currentTab
            if pageURL is "" then return "ERROR: URL is empty"
            return pageURL
        end tell'
    )";

    cout << "正在自动获取 Edge 当前页面 URL..." << endl;
    FILE* pipe = popen(edgeScript, "r");
    if (!pipe) {
        cerr << "错误：无法执行 AppleScript 脚本！" << endl;
        return "ERROR: Script execute failed";
    }

    char buffer[1024];
    string urlResult = "";
    char* fgetsResult = fgets(buffer, sizeof(buffer), pipe);
    if (fgetsResult != nullptr) {
        urlResult += buffer;
    } else {
        urlResult = "ERROR: No output from script";
    }

    pclose(pipe);
    if (!urlResult.empty() && urlResult.back() == '\n') {
        urlResult.pop_back();
    }

    if (urlResult.find("ERROR:") == 0) {
        cerr << "URL获取失败：" << urlResult << endl;
    } else {
        cout << "URL获取成功：" << urlResult << endl;
    }
    return urlResult;
}

string get_chrome_url() {
    const char* chromeScript = R"(
        osascript -e 'tell application "Google Chrome"
            if (count of windows) = 0 then return "ERROR: No windows open"
            set currentWindow to front window
            if (count of tabs of currentWindow) = 0 then return "ERROR: No tabs open"
            set currentTab to active tab of currentWindow
            set pageURL to URL of currentTab
            if pageURL is "" then return "ERROR: URL is empty"
            return pageURL
        end tell'
    )";

    cout << "正在自动获取 Chrome 当前页面 URL..." << endl;
    FILE* pipe = popen(chromeScript, "r");
    if (!pipe) {
        cerr << "错误：无法执行 AppleScript 脚本！" << endl;
        return "ERROR: Script execute failed";
    }

    char buffer[1024];
    string urlResult = "";
    char* fgetsResult = fgets(buffer, sizeof(buffer), pipe);
    if (fgetsResult != nullptr) {
        urlResult += buffer;
    } else {
        urlResult = "ERROR: No output from script";
    }

    pclose(pipe);
    if (!urlResult.empty() && urlResult.back() == '\n') {
        urlResult.pop_back();
    }

    if (urlResult.find("ERROR:") == 0) {
        cerr << "URL获取失败：" << urlResult << endl;
    } else {
        cout << "URL获取成功：" << urlResult << endl;
    }
    return urlResult;
}

string fetch_html(const std::string& url) {
    if (url.empty() || url.find("ERROR:") == 0) {
        cerr << "错误：URL无效，跳过页面抓取！" << endl;
        return "";
    }
    cout << "正在自动抓取页面：" << url << endl;
    CURL *curl;
    CURLcode res;
    string html_data;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html_data);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "页面抓取失败：" << curl_easy_strerror(res) << endl;
            html_data = "";
        } else {
            cout << "页面抓取成功，内容长度：" << html_data.size() << " 字节" << endl;
        }
        curl_easy_cleanup(curl);
    } else {
        cerr << "错误：curl初始化失败！" << endl;
    }
    curl_global_cleanup();
    return html_data;
}

string catch_email_edge() {
    string url = get_edge_url();
    string html = fetch_html(url);
    if (html.empty()) return "";

    regex email_regex(R"([a-zA-Z0-9_+&*-]+(?:\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,})");
    sregex_iterator it(html.begin(), html.end(), email_regex), end;
    set<string> unique_emails;

    for (; it != end; ++it) {
        string temp = (*it).str();
        if (!temp.empty()) unique_emails.insert(temp);
    }

    string all_emails;
    int count = 0;
    for (auto& e : unique_emails) {
        count++;
        all_emails += e + "\n";
    }
    x = count;
    return all_emails;
}

string catch_email_chrome() {
    string url = get_chrome_url();
    string html = fetch_html(url);
    if (html.empty()) return "";

    regex email_regex(R"([a-zA-Z0-9_+&*-]+(?:\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,})");
    sregex_iterator it(html.begin(), html.end(), email_regex), end;
    set<string> unique_emails;

    for (; it != end; ++it) {
        string temp = (*it).str();
        if (!temp.empty()) unique_emails.insert(temp);
    }

    string all_emails;
    int count = 0;
    for (auto& e : unique_emails) {
        count++;
        all_emails += e + "\n";
    }
    x = count;
    return all_emails;
}

string start_catch_chrome(){
    return catch_email_chrome();
}

string start_catch_edge(){
    return catch_email_edge();
}

int return_x(){
    return x;
}


std::string Widget::cleanUrl(const std::string& url) {
    std::string cleaned = url;
    cleaned.erase(cleaned.begin(), std::find_if(cleaned.begin(), cleaned.end(), [](unsigned char ch) {
                      return !std::isspace(ch);
                  }));
    cleaned.erase(std::find_if(cleaned.rbegin(), cleaned.rend(), [](unsigned char ch) {
                      return !std::isspace(ch);
                  }).base(), cleaned.end());
    return cleaned;
}

void Widget::updateStatisticsLabel() {
    if (ui->label_4) {
        ui->label_4->setText(QString("%1").arg(totalEmailCount));
    }
}

void Widget::logToTextEdit(const QString& logMsg) {
    ui->pushButton_4->setEnabled(true);
    if (loggedMessages.count(logMsg) > 0) {
        return;
    }

    if (ui->textEdit) {
        ui->textEdit->setReadOnly(true);
        ui->textEdit->append(QString("[%1] %2").arg(QTime::currentTime().toString("HH:mm:ss"), logMsg));
    }
    loggedMessages.insert(logMsg);
    updateStatisticsLabel();
}

void Widget::updateProgressBar() {
    if (ui->updateProgressBar) {
        progressValue += 5;
        if (progressValue >= 100) {
            progressValue = 100;
            progressTimer->stop();
        }
        ui->updateProgressBar->setValue(progressValue);
    }
}

void Widget::detectCycle() {
    if (isPaused) return;

    std::string currentUrl = get_chrome_url();
    std::string cleanedUrl = cleanUrl(currentUrl);

    if (isCleared && cleanedUrl == lastUrl && !cleanedUrl.empty()) {
        return;
    }

    if (cleanedUrl != lastUrl) {
        lastUrl = cleanedUrl;
        isCleared = false;
        progressValue = 0;
        if (ui->updateProgressBar) {
            ui->updateProgressBar->setValue(0);
        }
        progressTimer->start(10);

        if (cleanedUrl.empty() || cleanedUrl.find("ERROR:") != std::string::npos) {
            logToTextEdit("URL无效，跳过检测");
        } else if (processedUrls.count(cleanedUrl) > 0) {
            logToTextEdit(QString("URL已处理过：%1").arg(QString::fromStdString(cleanedUrl)));
        } else {
            std::string newResult;
            if(int selectedIndex = ui->setmod->currentIndex()==0)
                newResult = catch_email_edge();
            if(int selectedIndex = ui->setmod->currentIndex()==1)
                newResult = catch_email_chrome();
            if (!newResult.empty()) {
                QString displayText = QString::fromStdString(newResult);
                if (ui->showRes) {
                    QTextCursor cursor = ui->showRes->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.insertText(displayText);
                    ui->showRes->setTextCursor(cursor);
                }

                int cnt = displayText.split('\n', Qt::SkipEmptyParts).size();
                totalEmailCount += cnt;
                processedUrls.insert(cleanedUrl);
                logToTextEdit(QString("新URL处理完成，新增%1条邮箱记录").arg(cnt));

                QSqlDatabase db;
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

                if (db.isOpen()) {
                    const QStringList lines = displayText.split('\n', Qt::SkipEmptyParts);
                    const QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    for (const QString& line : lines) {
                        QString e = line.trimmed();
                        if (e.isEmpty()) continue;
                        QSqlQuery query(db);
                        query.prepare("INSERT INTO emails (url, email, create_time) VALUES (?, ?, ?)");
                        query.addBindValue(QString::fromStdString(cleanedUrl));
                        query.addBindValue(e);
                        query.addBindValue(now);
                        query.exec();
                    }
                }

                updateStatisticsLabel();
            }
        }
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , detectTimer(nullptr)
    , progressTimer(new QTimer(this))
    , ppage2(nullptr)
    , isPaused(false)
    , progressValue(0)
    , isCleared(false)
    , totalEmailCount(0)
{
    ui->setupUi(this);

    this->setWindowTitle("CatchEmailTools 4.0");

    QPixmap pixmap(":/images/sleeping.png");
    if (pixmap.isNull()) {
        qDebug() << "图片加载失败";
        ui->emojiLabel->setText("图片缺失");
    } else {
        ui->emojiLabel->setPixmap(pixmap);
        ui->emojiLabel->setScaledContents(true);
        ui->emojiLabel->setFixedSize(24, 24);
    }

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->save->setEnabled(false);
    ui->save->setToolTip("按钮已禁用，无法点击");
    ui->save->installEventFilter(this);

    if (ui->showRes)
        ui->showRes->setReadOnly(true);

    if (ui->updateProgressBar) {
        ui->updateProgressBar->setRange(0, 100);
        ui->updateProgressBar->setValue(0);
        ui->updateProgressBar->setFormat("检测中: %p%");
    }

    updateStatisticsLabel();
    connect(progressTimer, &QTimer::timeout, this, &Widget::updateProgressBar);

    QSettings settings("CatchEmailTools", "CatchEmailTools");
    qDebug() << "=== 调试信息 ===";
    qDebug() << "QSettings 配置文件路径:" << settings.fileName();
    bool dontShowAgain = settings.value("dontShowWelcome", false).toBool();
    qDebug() << "读取到的 'dontShowWelcome' 值:" << dontShowAgain;
    qDebug() << "原始QVariant值:" << settings.value("dontShowWelcome");
    if (!dontShowAgain) {
        qDebug() << "条件满足，将显示欢迎提示框";
        QMessageBox msgBox;
        msgBox.setWindowTitle("欢迎使用 CatchEmailTools 4.0");
        msgBox.setText("1.新增了Chrome支持，切换Edge/Chrome时，需将页面刷新");
        msgBox.setIcon(QMessageBox::Information);
        QCheckBox *cb = new QCheckBox("以后不再显示此提示", &msgBox);
        msgBox.setCheckBox(cb);
        msgBox.addButton(QMessageBox::Ok);
        int result = msgBox.exec();
        qDebug() << "对话框返回结果:" << result << "(Ok=" << QMessageBox::Ok << ")";
        qDebug() << "复选框是否被勾选:" << cb->isChecked();
        if (result == QMessageBox::Ok && cb->isChecked()) {
            settings.setValue("dontShowWelcome", true);
            settings.sync();
            qDebug() << "已保存设置，新值:" << settings.value("dontShowWelcome").toBool();
            qDebug() << "保存后立即读取测试:" << settings.value("dontShowWelcome", false).toBool();
        } else {
            qDebug() << "未保存设置（用户取消或未勾选）";
        }
    } else {
        qDebug() << "条件不满足，跳过显示欢迎提示框";
    }
    qDebug() << "=== 调试结束 ===";
}

Widget::~Widget()
{
    delete ui;
    delete detectTimer;
}


void Widget::on_pushButton_clicked()
{
    ui->pushButton_5->setEnabled(true);
    ui->pushButton->setEnabled(false);

    QPixmap pixmap(":/images/thinking.png");
    if (pixmap.isNull())
        ui->emojiLabel->setText("图片缺失");
    else {
        ui->emojiLabel->setPixmap(pixmap);
        ui->emojiLabel->setScaledContents(true);
        ui->emojiLabel->setFixedSize(24, 24);
    }

    if (detectTimer) {
        logToTextEdit("检测已启动，无需重复点击！");
        return;
    }

    detectTimer = new QTimer(this);
    connect(detectTimer, &QTimer::timeout, this, &Widget::detectCycle);
    detectTimer->start(1000);
    QMetaObject::invokeMethod(this, "detectCycle", Qt::QueuedConnection);

    std::string currentUrl = get_chrome_url();
    std::string cleanedUrl = cleanUrl(currentUrl);

    lastUrl = "";
    isCleared = false;
    progressValue = 0;
    if (ui->updateProgressBar)
        ui->updateProgressBar->setValue(0);
    progressTimer->start(30);

    logToTextEdit("开始检测！");

    if (cleanedUrl.empty() || cleanedUrl.find("ERROR:") != std::string::npos) {
        logToTextEdit("首次检测URL无效，跳过");
    } else if (processedUrls.count(cleanedUrl) == 0) {
        std::string newResult;
        if(int selectedIndex = ui->setmod->currentIndex()==0)
            newResult = catch_email_edge();
        if(int selectedIndex = ui->setmod->currentIndex()==1)
            newResult = catch_email_chrome();
        logToTextEdit(QString("首次捕获原始字符串：%1").arg(QString::fromStdString(newResult)));

        if (!newResult.empty()) {
            ui->pushButton_2->setEnabled(true);
            QString displayText = QString::fromStdString(newResult);

            if (ui->showRes) {
                QTextCursor cursor = ui->showRes->textCursor();
                cursor.movePosition(QTextCursor::End);
                cursor.insertText(displayText);
                ui->showRes->setTextCursor(cursor);

                ui->pushButton_4->setEnabled(true);
                ui->pushButton_3->setEnabled(true);
            }

            int cnt = displayText.split('\n', Qt::SkipEmptyParts).size();
            totalEmailCount += cnt;
            processedUrls.insert(cleanedUrl);

            QSqlDatabase db;
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

            if (db.isOpen()) {
                const QStringList lines = displayText.split('\n', Qt::SkipEmptyParts);
                const QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                for (const QString& line : lines) {
                    QString e = line.trimmed();
                    if (e.isEmpty()) continue;
                    QSqlQuery query(db);
                    query.prepare("INSERT INTO emails (url, email, create_time) VALUES (?, ?, ?)");
                    query.addBindValue(QString::fromStdString(cleanedUrl));
                    query.addBindValue(e);
                    query.addBindValue(now);
                    query.exec();
                }
            }

            updateStatisticsLabel();
            newResult="";
        } else {
            logToTextEdit("未找到邮箱地址");
        }
    }
}

void Widget::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->showRes->clear();
    processedUrls.clear();
    loggedMessages.clear();
    lastUrl = cleanUrl(get_chrome_url());
    isCleared = true;
    totalEmailCount = 0;

    if (ui->updateProgressBar) {
        progressValue = 0;
        ui->updateProgressBar->setValue(0);
    }
    if (progressTimer->isActive())
        progressTimer->stop();

    logToTextEdit("已清空显示内容和已处理URL记录");
    updateStatisticsLabel();

    QPixmap pixmap(":/images/winking.png");
    if (pixmap.isNull())
        ui->emojiLabel->setText("图片缺失");
    else {
        ui->emojiLabel->setPixmap(pixmap);
        ui->emojiLabel->setScaledContents(true);
        ui->emojiLabel->setFixedSize(24, 24);
    }
}

void Widget::on_pushButton_3_clicked()
{
    QApplication::clipboard()->setText(ui->showRes->toPlainText());
    logToTextEdit("已复制内容到剪贴板");

    QPixmap pixmap(":/images/winking.png");
    if (pixmap.isNull())
        ui->emojiLabel->setText("图片缺失");
    else {
        ui->emojiLabel->setPixmap(pixmap);
        ui->emojiLabel->setScaledContents(true);
        ui->emojiLabel->setFixedSize(24, 24);
    }
}

void Widget::on_pushButton_5_clicked()
{
    if (!detectTimer) {
        logToTextEdit("检测尚未启动，无法暂停/恢复！");
        return;
    }

    if (isPaused) {
        isPaused = false;
        logToTextEdit("已恢复实时检测！");
        ui->pushButton_5->setText("暂停");

        QPixmap pixmap(":/images/thinking.png");
        if (pixmap.isNull())
            ui->emojiLabel->setText("图片缺失");
        else {
            ui->emojiLabel->setPixmap(pixmap);
            ui->emojiLabel->setScaledContents(true);
            ui->emojiLabel->setFixedSize(24, 24);
        }
    } else {
        isPaused = true;
        logToTextEdit("已暂停实时检测！");
        ui->pushButton_5->setText("继续");
        if (progressTimer->isActive())
            progressTimer->stop();

        QPixmap pixmap(":/images/sleepy.png");
        if (pixmap.isNull())
            ui->emojiLabel->setText("图片缺失");
        else {
            ui->emojiLabel->setPixmap(pixmap);
            ui->emojiLabel->setScaledContents(true);
            ui->emojiLabel->setFixedSize(24, 24);
        }
    }
}

void Widget::on_pushButton_4_clicked()
{
    QApplication::clipboard()->setText(ui->textEdit->toPlainText());
    logToTextEdit("已复制日志到剪贴板");

    QPixmap pixmap(":/images/winking.png");
    if (pixmap.isNull())
        ui->emojiLabel->setText("图片缺失");
    else {
        ui->emojiLabel->setPixmap(pixmap);
        ui->emojiLabel->setScaledContents(true);
        ui->emojiLabel->setFixedSize(24, 24);
    }
}

void Widget::on_pushButton_7_clicked()
{
    const QString strCN = "1. 本软件为兼容显示正常，已将窗口缩放禁用\n"
                          "2. 本软件内置存储数据库依赖外部db文件，误操作数据丢失概不负责\n"
                          "4. 请勿在非崩溃状态下强制退出，避免数据异常\n"
                          "6. 打开存储、查询这些子窗口的时候，关闭会自动销毁，请保存后关闭\n\n"
                          "Ps: 更多咨询请联系 mikehuang5286@outlook.com";

    const QString strEN = "1. Window resizing disabled for compatibility\n"
                          "2. Built-in DB uses external file, misuse at your own risk\n"
                          "3. Do not force quit unless crashed\n"
                          "4. Sub-windows are automatically deleted when closed. Save before closing.\n\n"
                          "Ps: For inquiries: mikehuang5286@outlook.com";

    bool showEnglish = false;

    while (true) {
        QMessageBox msg(this);
        msg.setWindowTitle("Notice");
        msg.setIcon(QMessageBox::Information);

        if (showEnglish) {
            msg.setText(strEN);
            msg.setFixedSize(460, 300);
        } else {
            msg.setText(strCN);
            msg.setFixedSize(620, 340);
        }

        QPushButton *btnCN = msg.addButton("中文", QMessageBox::ActionRole);
        QPushButton *btnEN = msg.addButton("English", QMessageBox::ActionRole);
        msg.addButton("OK", QMessageBox::AcceptRole);

        msg.exec();

        if (msg.clickedButton() == btnEN)
            showEnglish = true;
        else if (msg.clickedButton() == btnCN)
            showEnglish = false;
        else
            break;
    }
}

void Widget::on_pushButton_6_clicked()
{
    if (ppage2 == nullptr) {
        ppage2 = new sonWidget(this);
        ppage2->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
        connect(ppage2, &sonWidget::destroyed, this, [this](){
            ppage2 = nullptr;
        });
        connect(ppage2, &sonWidget::back, this, [this](){
            ppage2->close();
        });
    }
    if (ppage2->isHidden())
        ppage2->show();
    else
        ppage2->raise();
}
