#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 动用资源文件中的btn_style1.qss文件：按钮样式1
    QFile file(":/new/styles/btn_style1.qss");  // 资源路径
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString qss = stream.readAll();
        a.setStyleSheet(qss);  // 应用 QSS 样式
        file.close();
    }
    // SliderButton button;
    // button.show();
    w.show();
    return a.exec();
}
