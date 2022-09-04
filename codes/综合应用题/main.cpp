#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <QSize>
#include "utils.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
