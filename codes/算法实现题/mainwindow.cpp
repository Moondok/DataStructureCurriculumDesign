#include "mainwindow.h"
#include "createtreeview.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QString>
#include <memory>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1200,800);
    QColor color = QColor(245,245,245);
    QPalette p = this->palette();
    p.setColor(QPalette::Window,color);
    this->setPalette(p);
    QToolButton* startBtn=new QToolButton(this);

    //左侧”创建二叉树“的按钮
    startBtn->setText("创建二叉树");
    startBtn->setFixedSize(200,80);
    startBtn->setFont(QFont("宋体",16));
    startBtn->move(this->width()/2-300,this->height()/2+100);
    startBtn->show();
    connect(startBtn,&QToolButton::clicked,this,[=](){
        this->hide();
        createTreeView *treeView= new createTreeView;
        treeView->show();
        connect(treeView,&createTreeView::return2mainpage,this,[=](){
            treeView->hide();
            this->show();

        });
    });


    //右侧“退出程序”的按钮
    QToolButton* exitBtn=new QToolButton(this);
    exitBtn->setText("退出程序");
    exitBtn->setFixedSize(200,80);
    exitBtn->setFont(QFont("宋体",16));
    exitBtn->move(this->width()/2+100,this->height()/2+100);
    //连接signal-slot,点击即关闭窗口
    connect(exitBtn, &QToolButton::clicked,this,&QMainWindow::close);

    QLabel *title=new QLabel("欢迎来到二叉树遍历及线索化演示程序！",this);
    title->setFont(QFont("楷体",23,15));
    title->setFixedSize(800,400);
    title->move(330,120);

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap pix;
    bool re=pix.load("://image//title.png");
    if(!re)
        qDebug()<<"图片加载不出来！";

    pix=pix.scaled(260,196);
    QPainter painter(this);
    painter.drawPixmap(40,220,pix.width(),pix.height(),pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}

