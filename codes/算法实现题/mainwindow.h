#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QDebug>
const int WINDOW_WIDTH=1200;
const int WINDOW_HEIGHT=800;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
