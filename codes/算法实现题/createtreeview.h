#ifndef CREATETREEVIEW_H
#define CREATETREEVIEW_H

#include <QMainWindow>
#include <QWidget>
#include "paintboard.h"
#include "QPaintEvent"
#include "binarytree.h"
#include <QSpinBox>
#include "functionalpage.h"

class createTreeView : public QMainWindow
{
    Q_OBJECT
public:
    explicit createTreeView(QWidget *parent = nullptr);
    ~createTreeView()
    {
        if(paintBoard!=nullptr)
            delete paintBoard;
        if(spinbox!=nullptr)
            delete spinbox;
    }


private:
    QWidget * paintBoard= nullptr;
    PaintBoard paintboard;
    BinaryTree tree;
    void paintEvent(QPaintEvent*);
    void showTree();
    void resetParents();
    QSpinBox* spinbox=nullptr;
    void connect2LabelClick();


signals:
    //信号1，由Toolbar里面的returnaction 调用
    void return2mainpage();

};

#endif // CREATETREEVIEW_H
