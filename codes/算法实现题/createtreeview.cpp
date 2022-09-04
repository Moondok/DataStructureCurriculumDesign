#include "createtreeview.h"
#include <QLabel>
#include <QString>
#include <QFont>
#include <QToolButton>
#include <QToolBar>
#include <QAction>
#include <binarytree.h>
#include <QDebug>
#include <nondelabel.h>
#include <cmath>
#include <queue>
#include <stack>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QMessageBox>

createTreeView::createTreeView(QWidget *parent) : QMainWindow(parent)
{

    this->setFixedSize(1200,800);
    const QString message1("请选择二叉树的高度(2-6)");
    QLabel *messageLabel1=new QLabel(message1,this);
    messageLabel1->setFixedSize(390,70);
    messageLabel1->move(15,100);
    messageLabel1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    messageLabel1->setFont(QFont("隶书",17,18));
    messageLabel1->show();

    //用户输入树的层数的框
    spinbox=new QSpinBox(this);
    spinbox->setMaximum(6);
    spinbox->setMinimum(2);  //最小是二层的
    spinbox->setFont(QFont("宋体",20,15));
    spinbox->move(100,200);
    spinbox->resize(140,50);
    spinbox->setValue(4);//初始默认4层，比较符合规矩



    //下方的第一句提示语
    const QString message2("            提示\n1.程序默认建立满二叉树，您可以通过点击对应结点执行删除操作。\n\n2.删除操作不可逆。\n\n3.您只能删除叶结点");
    QLabel* messageLabel2 =new QLabel(message2,this);
    messageLabel2->move(15,350);
    messageLabel2->resize(360,200);
    messageLabel2->setWordWrap(true);
    messageLabel2->setFont(QFont("宋体",12,8));

    //上方的返回按钮和退出程序按钮，用Toolbar
    QToolBar * tools= new QToolBar;
    addToolBar(Qt::TopToolBarArea,tools);
    tools->setMovable(false);

    QAction* returnAction=tools->addAction("返回主页");
    //连接信号和主场景
    connect(returnAction,&QAction::triggered,this,[=](){
        emit this->return2mainpage();
    });
    tools->addSeparator(); //分割线

    QAction * exitAction=tools->addAction("退出程序");
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);

    connect(&tree,&BinaryTree::signal_buildtree,this,[&](){ //这里注意tree我用了引用
        std::queue<BinaryTree::treeNode*> q;
        q.push(tree.root);
        for(int i=0;i<tree.getLayer();i++)
        {
            int h=40+i*(720/tree.getLayer());

            int gap=750/(static_cast<int>(pow(2,i))+1);
            for(int j=0;j<static_cast<int>(pow(2,i));j++)
            {
                int w=j*gap+gap;
                BinaryTree::treeNode* tmp=q.front();
                q.pop();
                NondeLabel * nodelabel= tree.node2label[tmp];
                if(nodelabel==nullptr)
                    qDebug()<<"这是shit";

                nodelabel->setParent(this);
                nodelabel->move(w+400,h+50);
                nodelabel->show();
                connect(nodelabel,&QPushButton::clicked,this,&createTreeView::connect2LabelClick);
                if(i!=tree.getLayer()-1)
                {

                    q.push(tmp->lchild);
                    q.push(tmp->rchild);
                }
            }
        }

    });

    tree.buildTree();
    void(QSpinBox::*ptr)(int )=&QSpinBox::valueChanged;
    connect(spinbox,ptr,this,[&](){
       tree.setLayer(spinbox->value());  //这里spinbox老出错
       tree.destroy();
       tree.buildTree();
       update();
   });


    showTree();
    //先序非递归遍历
    //下方的创建完成按钮
    QToolButton* finishBtn= new QToolButton(this);
    finishBtn->setText("创建完成");
    finishBtn->move(105,620);
    finishBtn->resize(180,60);
    finishBtn->setFont(QFont("黑体",12,12));
    connect(finishBtn,&QPushButton::clicked,this,[=](){
        this->hide();
        QMap<NondeLabel*,BinaryTree::treeNode*>::iterator ite=tree.label2node.begin();

        for(;ite!=tree.label2node.end();ite++)
            disconnect(ite.key(),&QPushButton::clicked,this,&createTreeView::connect2LabelClick);//顺手在这里重连

        FunctionalPage *functionalPage=new FunctionalPage(&tree);
        functionalPage->show();
        connect(functionalPage,&FunctionalPage::return2createpage,this,[=](){
            functionalPage->hide();
            this->resetParents();
            QMap<NondeLabel*,BinaryTree::treeNode*>::iterator ite=tree.label2node.begin();

            for(;ite!=tree.label2node.end();ite++)
                connect(ite.key(),&QPushButton::clicked,this,&createTreeView::connect2LabelClick);//在这里断开连接

            this->show();
            });
    });

}


void createTreeView ::paintEvent(QPaintEvent*)
{
    QPixmap *map=new QPixmap(750,720);
    map->fill(Qt::white);
    QPainter painter2(this);
    painter2.drawPixmap(415,50,*map);
    QPainter painter(this);
    QPen pen;

    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(pen);
    std::stack<BinaryTree::treeNode*> s;
    if(tree.root==nullptr)
    {
        //qDebug()<<"no";
        return ;
    }
    s.push(tree.root);

    int widthBias=tree.node2label[tree.root]->size().width()/2;
    int heightBias=tree.node2label[tree.root]->size().height()/2;

    while(!s.empty())
    {
        BinaryTree::treeNode * node=s.top();
        s.pop();
        if(node->lchild!=nullptr)
        {
            s.push(node->lchild);
            painter.drawLine(tree.node2label[node]->pos().x()+widthBias,tree.node2label[node]->pos().y()+heightBias,
                             tree.node2label[node->lchild]->pos().x()+widthBias,tree.node2label[node->lchild]->pos().y()+heightBias);
        }
        if(node->rchild!=nullptr)
        {
            s.push(node->rchild);
            painter.drawLine(tree.node2label[node]->pos().x()+widthBias,tree.node2label[node]->pos().y()+heightBias,
                             tree.node2label[node->rchild]->pos().x()+widthBias,tree.node2label[node->rchild]->pos().y()+heightBias);
        }
    }
}

void createTreeView::resetParents()
{
    QMap<NondeLabel*,BinaryTree::treeNode*>::iterator ite=tree.label2node.begin();
    for(;ite!=tree.label2node.end();ite++)
    {
        ite.key()->setParent(this);//顺手在这里重连

    }
}

void createTreeView ::showTree()
{

}

void createTreeView ::connect2LabelClick()
{
    if(QMessageBox::Yes==QMessageBox::question(this,"疑问","确认删除该结点？"))
    {
            NondeLabel*a= qobject_cast<NondeLabel*>(sender());
            BinaryTree::treeNode* tmp=tree.label2node[a];
            if(tmp->isLeaf==false)
                QMessageBox::critical(this,"错误","您只可以删除叶子结点。");
            else if(tmp==tree.root)
                 QMessageBox::critical(this,"错误","您不可以删除根结点。");
             else
            {
                tree.node2label.remove(tmp);
                tree.label2node.remove(a);

                if(tmp->parent->rchild==tmp)
                      tmp->parent->rchild=nullptr;

                 else if(tmp->parent->lchild==tmp)
                      tmp->parent->lchild=nullptr;

                if(tmp->parent->lchild==nullptr&&tmp->parent->rchild==nullptr)
                    tmp->parent->isLeaf=true;
                 delete tmp;
                 delete a;
                 update();
            }
    }
}
