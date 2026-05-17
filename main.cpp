#include "widget.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{

    qSetMessagePattern("[%{time}] %{type}: %{message}");
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &, const QString &msg) {
        if (msg.contains("IMKCFRunLoopWakeUpReliable") || msg.contains("mach port")) {
            return;
        }
        fprintf(stderr, "%s\n", qPrintable(msg));
    });
    QApplication a(argc, argv);
    Widget w;
    w.show();
    qDebug() << "当前运行路径：" << QDir::currentPath();
    qDebug() << "数据库文件路径：" << QDir::currentPath() + "/data.db";

    return a.exec();
}
