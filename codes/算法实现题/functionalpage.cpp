#include "functionalpage.h"
#include <QTime>
#include <QCoreApplication>

FunctionalPage::FunctionalPage(BinaryTree *t) : tree(t)
{
    this->setFixedSize(1200,800);

    QToolBar * tools= new QToolBar;
    addToolBar(Qt::TopToolBarArea,tools);
    tools->setMovable(false);

    QAction* returnAction=tools->addAction("返回上页");
    //连接信号和主场景
    connect(returnAction,&QAction::triggered,this,[=](){
        emit this->return2createpage();
    });
    tools->addSeparator(); //分割线

    QAction * exitAction=tools->addAction("退出程序");
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);

    resetParents();

    QLabel*title=new QLabel(leftPanel);
    title->setFixedSize(320,60);
    title->move(55,0);
    title->setText("请选择要执行的操作");
    title->setFont(QFont("楷体",16,22));
    leftPanel->move(0,40);
    leftPanel->setFixedSize(390,750);

    //返回按钮
    returnbtn->move(100,450);
    returnbtn->setFixedSize(190,70);
    returnbtn->hide();

    //debug
    //messageLabel->setText("hhhh");

    //画出左侧面板的按钮
    QVector<QPushButton*> buttonList;
    for(int i=0;i<9;i++)
    {
        QPushButton* btn=new QPushButton(leftPanel);//挂载到leftpanel而不是this
        btn->setFixedSize(250,55);
        btn->setText(messages[i]);
        btn->setFont(QFont("宋体",12,12));
        btn->move(70,70+i*75);
        btn->show();
        connect(btn,&QPushButton::clicked,this,[=](){
            btn->show();
            tools->hide();
            leftPanel->hide();
            messageLabel->show();
            QLabel* label=new QLabel(this);  //标签挂载在functionalPage下即可
            label->setFixedSize(380,80);
            label->move(10,50);
            label->setText(btn->text());
            label->setFont(QFont("隶书",22,15));
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            label->show();
            auxMessageLabel->show();

            message="";
            connect(tree,&BinaryTree::signal_traverse,this,&FunctionalPage::showMessage,Qt::UniqueConnection);

            if(label->text()=="先序遍历")
            {
                auxMessageLabel->setText("以下为遍历结果");
                tree->preOrderTraverse();
            }
            else if(label->text()=="中序遍历")
            {
                auxMessageLabel->setText("以下为遍历结果");
                 tree->midOrderTraverse();
            }
            else if(label->text()=="后序遍历")
            {
                auxMessageLabel->setText("以下为遍历结果");
                tree->postOrderTraverse();
            }
            else if(label->text()=="先序线索化")
            {
                tree->preOrderThread();
                update();
                auxMessageLabel->setText("右侧为线索化结果\n红:前驱 蓝:后继");
                QTime time;
                time.start();
                while(time.elapsed() < 2500)
                    QCoreApplication::processEvents(); //等待时间流逝4秒钟

            }
            else if(label->text()=="中序线索化")
            {
                tree->midOrderThread();
                update();
                auxMessageLabel->setText("右侧为线索化结果\n红:前驱 蓝:后继");
                QTime time;
                time.start();
                while(time.elapsed() < 2500)
                    QCoreApplication::processEvents(); //等待时间流逝4秒钟


            }
            else if(label->text()=="后序线索化")
            {
                tree->postOrderThread();
                update();
                auxMessageLabel->setText("右侧为线索化结果\n红:前驱 蓝:后继");
                QTime time;
                time.start();
                while(time.elapsed() < 2500)
                    QCoreApplication::processEvents(); //等待时间流逝4秒钟
            }

            else if(label->text()=="先序线索化遍历")
            {
                auxMessageLabel->setText("以下为遍历结果\n右侧为线索化结果\n红:前驱 蓝:后继");
                tree->preOrderThread();
                update();
                tree->preOrderThreadTraverse();
            }
            else if(label->text()=="中序线索化遍历")
            {
                auxMessageLabel->setText("以下为遍历结果\n右侧为线索化结果\n红:前驱 蓝:后继");
                tree->midOrderThread();
                update();
                tree->midOrderThreadTraverse();
            }
            else if(label->text()=="统计结点个数")
            {
                int n=tree->getNodeNum(tree->root);
                auxMessageLabel->setText("结点个数为:"+QString::number(n));
                QTime time;
                time.start();
                while(time.elapsed() < 2500)
                    QCoreApplication::processEvents(); //等待时间流逝2秒钟

            }


             messageLabel->setText("");
             messageLabel->hide();

             auxMessageLabel->setText("已完成该操作");
//             QTime time;
//             time.start();
//             while(time.elapsed() < 3000)
//                 QCoreApplication::processEvents(); //等待时间流逝2秒钟
             returnbtn->show();
             connect(returnbtn,&QPushButton::clicked,this,[=](){
                 tree->clearThread();
                 update();
                 auxMessageLabel->hide();
                 returnbtn->hide();
                 label->hide();
                 leftPanel->show();
                 tools->show();



             });

             //qDebug()<<"m"<<message;

            //messageLabel->hide();

        });
        buttonList.push_back(btn);
    }

    //画出当点进去一个功能后，下方的显示提示的Label

    messageLabel->move(50,350);
    messageLabel->setFixedSize(280,400);
    messageLabel->setFont(QFont("宋体",12,10));
    messageLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    messageLabel->setWordWrap(true);

    messageLabel->hide();
    auxMessageLabel->move(50,250);
    auxMessageLabel->setFixedSize(280,85);
    auxMessageLabel->setFont(QFont("楷体",12,12));
    auxMessageLabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    auxMessageLabel->hide();


}

void FunctionalPage::paintEvent(QPaintEvent*)
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

    QPen pen3;
    pen3.setWidth(4);
    pen3.setColor(Qt::red);

    QPen pen4;
    pen4.setWidth(4);
    pen4.setColor(Qt::blue);
//    painter3.setRenderHint(QPainter::HighQualityAntialiasing);
//    painter3.setPen(pen3);
    std::stack<BinaryTree::treeNode*> s;
    if(tree->root==nullptr)
    {
        return ;
    }
    s.push(tree->root);

    int widthBias=tree->node2label[tree->root]->size().width()/2;
    int heightBias=tree->node2label[tree->root]->size().height()/2;

    while(!s.empty())
    {
        BinaryTree::treeNode * node=s.top();
        s.pop();
        if(node->lchild!=nullptr&&node->ltag==0)  //正经结点而不是线索
        {
            s.push(node->lchild);
            painter.drawLine(tree->node2label[node]->pos().x()+widthBias,tree->node2label[node]->pos().y()+heightBias,
                             tree->node2label[node->lchild]->pos().x()+widthBias,tree->node2label[node->lchild]->pos().y()+heightBias);
        }
        else if(node->lchild!=nullptr&&node->ltag==1) //是线索
        {
            painter.setPen(pen3);

            double x1=tree->node2label[node]->pos().x()+15+widthBias;
            double y1=tree->node2label[node]->pos().y()+heightBias-10;
            double x2=tree->node2label[node->lchild]->pos().x()+15+widthBias;
            double y2=tree->node2label[node->lchild]->pos().y()+heightBias-10;
            drawArrow(painter,x1,y1,x2,y2);
//            painter.drawLine(tree->node2label[node]->pos().x()+15+widthBias,tree->node2label[node]->pos().y()+heightBias-10,
//                             tree->node2label[node->lchild]->pos().x()+15+widthBias,tree->node2label[node->lchild]->pos().y()+heightBias-10);
            painter.setPen(pen);
        }
        if(node->rchild!=nullptr&&node->rtag==0)
        {
            s.push(node->rchild);
            painter.drawLine(tree->node2label[node]->pos().x()+widthBias,tree->node2label[node]->pos().y()+heightBias,
                         tree->node2label[node->rchild]->pos().x()+widthBias,tree->node2label[node->rchild]->pos().y()+heightBias);
        }
        else if(node->rchild!=nullptr&&node->rtag==1) //是线索
        {
            painter.setPen(pen4);
            drawArrow(painter,tree->node2label[node]->pos().x()-15+widthBias,tree->node2label[node]->pos().y()+heightBias+10,
                                                   tree->node2label[node->rchild]->pos().x()-15+widthBias,tree->node2label[node->rchild]->pos().y()+heightBias+10);
//            painter.drawLine(tree->node2label[node]->pos().x()-15+widthBias,tree->node2label[node]->pos().y()+heightBias+10,
//                             tree->node2label[node->rchild]->pos().x()-15+widthBias,tree->node2label[node->rchild]->pos().y()+heightBias+10);
            painter.setPen(pen);
        }

    }

}

void FunctionalPage::resetParents()
{
    QMap<NondeLabel*,BinaryTree::treeNode*>::iterator ite=tree->label2node.begin();
    for(;ite!=tree->label2node.end();ite++)
    {
        ite.key()->setParent(this);
    }
}

void FunctionalPage::showMessage(BinaryTree::treeNode * r)
{
    NondeLabel * label=tree->node2label[r];
    label->focused();
    update();
    message.push_back(QString::number(r->data));
    message.push_back(" ");
    messageLabel->setText(message);
    messageLabel->show();
    QTime time;
    time.start();
    while(time.elapsed() < 300)
        QCoreApplication::processEvents();
    label->released();
    update();


}
