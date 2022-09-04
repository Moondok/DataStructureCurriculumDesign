#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <functionalpage.h>
#include <utils.h>

extern double WIDTH_RATIO;
extern double HEIGHT_RATIO;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1600*WIDTH_RATIO,1000*HEIGHT_RATIO);
    QColor color = QColor(245,245,245);
    QPalette p = this->palette();
    p.setColor(QPalette::Window,color);
    this->setPalette(p);

    QLabel * message=new QLabel("欢迎进入社会关系网络演示程序！",this);
    message->move(500*WIDTH_RATIO,200*HEIGHT_RATIO);
    message->setFixedSize(1100*WIDTH_RATIO,350*HEIGHT_RATIO);
    QFont font("楷体",35*WIDTH_RATIO,20*HEIGHT_RATIO);
    message->setFont(font);

    QPushButton * enterBtn=new QPushButton(this);
    enterBtn->setText("进入演示");
    enterBtn->move(350*WIDTH_RATIO,700*HEIGHT_RATIO);
    enterBtn->setFixedSize(300*WIDTH_RATIO,100*HEIGHT_RATIO);
    enterBtn->setIcon(QIcon(QPixmap("://images//btn1.png")));
    enterBtn->setIconSize(QSize(80*WIDTH_RATIO,80*HEIGHT_RATIO));
    enterBtn->setFont(QFont("黑体",15*WIDTH_RATIO,20*HEIGHT_RATIO));

    QPushButton * exitBtn=new QPushButton(this);
    exitBtn->setText("退出程序");
    exitBtn->move(950*WIDTH_RATIO,700*HEIGHT_RATIO);
    exitBtn->setFixedSize(300*WIDTH_RATIO,100*HEIGHT_RATIO);
    exitBtn->setIcon(QIcon(QPixmap("://images//btn2.png")));
    exitBtn->setIconSize(QSize(80*WIDTH_RATIO,80*HEIGHT_RATIO));
    exitBtn->setFont(QFont("黑体",15*WIDTH_RATIO,20*HEIGHT_RATIO));

    connect(exitBtn,&QPushButton::clicked,this,&QMainWindow::close);
    connect(enterBtn,&QPushButton::clicked,this,&MainWindow::startNewPage);


}

void MainWindow::paintEvent(QPaintEvent*)
{

    QPixmap i;
    bool ret =i.load("://images//icon.png");
    if(!ret)
        qDebug()<<"图片无法加载！";
    QPainter painter(this);
    painter.drawPixmap(100*WIDTH_RATIO,200*HEIGHT_RATIO,350*WIDTH_RATIO,350*HEIGHT_RATIO,i);
}

void MainWindow::startNewPage()
{
   FunctionalPage* functionalPage=new FunctionalPage;
   connect(functionalPage,&FunctionalPage::return2mainpage,this,[=](){
       this->show();
       functionalPage->hide();
   });
   functionalPage->show();
   this->hide();

}


MainWindow::~MainWindow()
{
    delete ui;
}

