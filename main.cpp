/*
 *主程序负责窗口得位置
 */
#pragma execution_character_set("utf-8")
#include <QApplication>
#include "mainwindow.h"
#include<QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move ((QApplication::desktop()->width() - w.width()-50),(QApplication::desktop()->height() - w.height())/2);
    w.show();
    return a.exec();
}
