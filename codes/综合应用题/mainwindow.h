#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include "utils.h"
#include <QGuiApplication>
#include <QScreen>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent*) ;

    void startNewPage();
};
#endif // MAINWINDOW_H
