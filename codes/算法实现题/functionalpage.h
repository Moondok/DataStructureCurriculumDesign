#ifndef FUNCTIONALPAGE_H
#define FUNCTIONALPAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QToolBar>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include "binarytree.h"
#include <QMap>
#include <stack>
#include <QVector>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include "utils.h"

const QString messages[9]=
{"统计结点个数",
 "先序遍历",
 "中序遍历",
 "后序遍历",
 "先序线索化",
 "中序线索化",
 "后序线索化",
 "先序线索化遍历",
 "中序线索化遍历"};

class FunctionalPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit FunctionalPage(BinaryTree *t );
    void resetParents();
    ~FunctionalPage()
    {
        if(messageLabel!=nullptr)
            delete messageLabel;
        if(auxMessageLabel!=nullptr)
            delete auxMessageLabel;
        if(returnbtn!=nullptr)
            delete returnbtn;
    }
private:
    void paintEvent(QPaintEvent*);
    BinaryTree * tree=nullptr;
    QWidget *leftPanel=new QWidget(this); //左侧控制面板
    void showMessage(BinaryTree::treeNode * r);
    QString message;
    QLabel * messageLabel=new QLabel(this);
    QLabel * auxMessageLabel=new QLabel(this);
    QPushButton *returnbtn=new QPushButton("返回",this); //返回按钮


signals:
    void return2createpage();

};

#endif // FUNCTIONALPAGE_H
