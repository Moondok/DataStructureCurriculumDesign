#include "functionalpage.h"
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QInputDialog>
#include <QLabel>
#include <QColor>
#include <QRectF>
#include "personalinfopage.h"
#include <algorithm>
//注意左侧画板和右侧panel,上面得Toolbar
FunctionalPage::FunctionalPage(QWidget *parent) : QMainWindow(parent)
{


    this->setFixedSize(1600*WIDTH_RATIO,1000*HEIGHT_RATIO);
    QToolBar *tools=new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,tools);
    QAction *returnAct=tools->addAction("返回");
    tools->addSeparator();
    QAction *exitAct=tools->addAction("退出");
    tools->setMovable(false);
    tools->setAllowedAreas(Qt::TopToolBarArea);

    //连接toolbar的信号和槽
    connect(exitAct,&QAction::triggered,this,&QMainWindow::close);
    connect(returnAct,&QAction::triggered,this,[=](){
        emit return2mainpage();
    });

    QPushButton *addMember=new QPushButton("添加新成员",this);
    QPushButton *addGroup=new QPushButton("添加新群组",this);
    QPushButton *groupInfo=new QPushButton("查看当前群组",this);
    textBrowser=new QTextBrowser(this);


    //设计右侧的3个按钮
   addMember->setFixedSize(180*WIDTH_RATIO,60*HEIGHT_RATIO);
   addMember->setFont(QFont("宋体",12*WIDTH_RATIO,12*HEIGHT_RATIO));
   addMember->move(1160*WIDTH_RATIO,120*HEIGHT_RATIO);

   addGroup->setFixedSize(180*WIDTH_RATIO,60*HEIGHT_RATIO);
   addGroup->setFont(QFont("宋体",12*WIDTH_RATIO,12*HEIGHT_RATIO));
   addGroup->move(1370*WIDTH_RATIO,120*HEIGHT_RATIO);

   groupInfo->setFixedSize(180*WIDTH_RATIO,60*HEIGHT_RATIO);
   groupInfo->setFont(QFont("宋体",12*WIDTH_RATIO,12*HEIGHT_RATIO));
   groupInfo->move(1160*WIDTH_RATIO,230*HEIGHT_RATIO);


   QPushButton * memberInfo=new QPushButton("选择成员",this);
   memberInfo->setFixedSize(180*WIDTH_RATIO,60*HEIGHT_RATIO);
   memberInfo->move(1370*WIDTH_RATIO,230*HEIGHT_RATIO);
   memberInfo->setFont(QFont("宋体",12*WIDTH_RATIO,12*HEIGHT_RATIO));

   QLabel* message=new QLabel("详细信息",this);
   message->setFont(QFont("楷体",20*WIDTH_RATIO,15*HEIGHT_RATIO));
   message->setAlignment((Qt::AlignVCenter|Qt::AlignHCenter));
   message->setFixedSize(390*WIDTH_RATIO,100*HEIGHT_RATIO);
   message->move(1160*WIDTH_RATIO,360*HEIGHT_RATIO);


    //为四个按钮设置信号和槽
   connect(addMember,&QPushButton::clicked,this,&FunctionalPage::getMemberInfo);
   connect(addGroup,&QPushButton::clicked,this,&FunctionalPage::getGroupInfo);
   connect(memberInfo,&QPushButton::clicked,this,&FunctionalPage::getChooseInfo);
   connect(groupInfo,&QPushButton::clicked,this,&FunctionalPage::showGroupInfo);

   //设置初始的成员和群组
   initMember();
   initGroup();

   graph=new InnerGraph();

   textBrowser->setFixedSize(440*WIDTH_RATIO,500*HEIGHT_RATIO);
   textBrowser->move(1140*WIDTH_RATIO,475*HEIGHT_RATIO);
   textBrowser->append("当前共有"+QString::number(memberList.size())+" 名成员\n");
   textBrowser->append("当前共有"+QString::number(groupList.size())+" 个群组\n");

}

void FunctionalPage::paintEvent(QPaintEvent *)
{
    QPixmap map(1100*WIDTH_RATIO,930*HEIGHT_RATIO);
    map.fill(QColor(255,250,240));
    QPainter painter(this);
    painter.drawPixmap(20*WIDTH_RATIO,45*HEIGHT_RATIO,map.width(),map.height(),map);

    int num=memberList.size();

    double gap=360/num;//每俩个结点的角度差距

    int ox=555*WIDTH_RATIO;
    int oy=505*HEIGHT_RATIO;
    int r=400*std::min(WIDTH_RATIO,HEIGHT_RATIO);
    int R=(55-(num-3)*0.9)*std::min(WIDTH_RATIO,HEIGHT_RATIO);
    int l=static_cast<int>(R*0.55);


    //假如二人相识，画线
    QPainter painter3(this);
    painter3.setRenderHint(QPainter::HighQualityAntialiasing);
    QPen pen2(QColor(153,76,0));
    pen2.setWidth(3);
    painter3.setPen(pen2);
    for(int i=0;i<memberList.size();i++)
    {
        for(int j=0;j<memberList.size();j++)
        {
            if(i!=j&&graph->adjMatrix[i][j])
            {
                painter3.drawLine(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),
                                  QPoint(ox+r*cos(2*PI/360*gap*j),oy+r*sin(2*PI/360*gap*j)));
            }
        }
    }

    QPainter painter2(this);
    painter2.setRenderHint(QPainter::HighQualityAntialiasing);
    QPen pen(Qt::white);
    pen.setWidth(2);
    painter2.setPen(pen);
    QBrush brush(QColor(255,153,204));



    painter2.setBrush(brush);
    for(int i=0;i<num;i++)
    {
        painter2.drawEllipse(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),R,R);
        painter2.drawText(QRectF(ox+r*cos(2*PI/360*gap*i)-l,oy+r*sin(2*PI/360*gap*i)-l,2*l,2*l),
                          Qt::AlignVCenter|Qt::AlignHCenter,memberList.at(i).name);
    }


}

void FunctionalPage::getMemberInfo()
{
    if(memberList.size()>=MAX_MEMBER_NUM)
    {
        QMessageBox::warning(this,"警告","当前已有25名成员，不可以再添加");

        return ;
    }

    AddmemberDialog * dialog=new AddmemberDialog(memberList,groupList);
    dialog->exec();


    if(dialog->isValid())
   {
    person newperson(dialog->nameEdit->text(),dialog->primarySchoolEdit->text(),
                     dialog->midSchoolEdit->text(),dialog->universityEdit->text(),
                     dialog->workplaceEdit->text(),dialog->localityEdit->text());
    newperson.tag=memberList.size();

    memberList.push_back(newperson);

    //处理innergraph里面的事情
    graph->num++;
    int cnt=0,pos=newperson.tag;
    for(auto ite=dialog->btnList2.begin();ite!=dialog->btnList2.end();ite++)
    {

        if((*ite)->isChecked()==true)
        {
            graph->adjMatrix[cnt][pos]=graph->adjMatrix[pos][cnt]=1;

        }
        cnt++;
    }

    //处理GroupList里面的事情
    cnt=0;
    for(auto ite=dialog->btnList1.begin();ite!=dialog->btnList1.end();ite++)
    {

        if((*ite)->isChecked()==true)
        {
            groupList[cnt].num++;  //这里at方法和[]重载不同
            groupList[cnt].isMember.push_back(1);
        }
        else
            groupList[cnt].isMember.push_back(0);
        cnt++;
    }

    //处理GroupList之前，替客户背锅
    QString names[5]={
            dialog->primarySchoolEdit->text(),
            dialog->midSchoolEdit->text(),
            dialog->universityEdit->text(),
            dialog->workplaceEdit->text(),
            dialog->localityEdit->text()};


    //有新群组了！
    int preNum=groupList.size();
    for(int i=0;i<5;i++)
    {
        if(names[i]=="")
            continue;
        int isExist=0;
        for(int j=0;j<preNum;j++)
        {
            if(names[i]==groupList[j].groupname)
            {
                isExist=1;
                if(dialog->btnList1[j]->isChecked()==false)
                {
                    groupList[j].num++;  //这里at方法和[]重载不同
                    groupList[j].isMember.back()=1;  //之前push进去了0，改为1
                }
            }
        }
        if(!isExist)
        {
            Group newgroup(names[i]);
            newgroup.num=1;
            for(int i=0;i<memberList.size()-1;i++)
                newgroup.isMember.push_back(0);
             newgroup.isMember.push_back(1);

             groupList.push_back(newgroup);


        }
    }
    //更新字符浏览器
    textBrowser->clear();
    textBrowser->append("当前共有"+QString::number(memberList.size())+" 名成员\n");
    textBrowser->append("当前共有"+QString::number(groupList.size())+" 个群组\n");
    update();
    }
}

void FunctionalPage::getGroupInfo()
{

    if(groupList.size()>=MAX_GROUP_NUM)
    {
        QMessageBox::warning(this,"警告","当前已有18个群组，不可以再添加");

        return ;
    }

    AddGroupDialog* dialog=new AddGroupDialog(memberList,groupList,this);//this是我新加上的
    dialog->exec();
    if(dialog->isValid(groupList))
    {
        //添加一个新群组
        Group newgroup(dialog->groupedit->text());

        int cnt=0;
        for(auto ite=dialog->lst.begin();ite!=dialog->lst.end();ite++)
        {
            if((*ite)->isChecked()==true)
            {
                 newgroup.isMember.push_back(1);
                 newgroup.num++;

            }
            else
                newgroup.isMember.push_back(0);
            cnt++;
        }

        groupList.push_back(newgroup);
    }

    textBrowser->clear();
    textBrowser->append("当前共有"+QString::number(memberList.size())+" 名成员\n");
    textBrowser->append("当前共有"+QString::number(groupList.size())+" 个群组\n");

}

void FunctionalPage::getChooseInfo()
{
        QStringList items;
        for (auto i:memberList)
            items.append(i.name);

        bool isComfirm;

        QInputDialog dialog(this);

        QString chosenName=dialog.getItem(this,"成员选择对话框","请选择要查看的成员",items,0,false,&isComfirm);

        if(isComfirm&&!items.isEmpty())
        {
//            //在这里完成了数据的传递，传递指针
            PersonalInfoPage* personalPage=new PersonalInfoPage(memberList,groupList,graph,chosenName);
            this->hide();
            personalPage->show();
            personalPage->editBrowser();
            connect(personalPage,&PersonalInfoPage::return2lastPage,this,[=](){
                this->show();
                personalPage->hide();
                delete personalPage;
       });


       }

}

void FunctionalPage::initMember()
{
    person person1("KDB","光明小学","大同一中","同济大学","");
    person1.tag=0;
    memberList.push_back(person1);

    person person2("Moondok","未来小学","长青中学","同济大学","百度");
    person2.tag=1;
    memberList.push_back(person2);

    person person3("Leon","","鹏城中学","哈弗大学","百度");
    person3.tag=2;
    memberList.push_back(person3);

}

void FunctionalPage::initGroup()
{
    Group group1("光明小学");
    group1.num=1;
    group1.isMember.push_back(1);
    group1.isMember.push_back(0);
    group1.isMember.push_back(0);
    groupList.push_back(group1);

    Group group2("大同一中");
    group2.num=1;
    group2.isMember.push_back(1);
    group2.isMember.push_back(0);
    group2.isMember.push_back(0);
    groupList.push_back(group2);

    Group group3("同济大学");
    group3.num=2;
    group3.isMember.push_back(1);
    group3.isMember.push_back(1);
    group3.isMember.push_back(0);
    groupList.push_back(group3);

    Group group4("未来小学");
    group4.num=1;
    group4.isMember.push_back(0);
    group4.isMember.push_back(1);
    group4.isMember.push_back(0);
    groupList.push_back(group4);

    Group group5("长青中学");
    group5.num=1;
    group5.isMember.push_back(0);
    group5.isMember.push_back(1);
    group5.isMember.push_back(0);
    groupList.push_back(group5);

    Group group6("百度");
    group6.num=2;
    group6.isMember.push_back(0);
    group6.isMember.push_back(1);
    group6.isMember.push_back(1);
    groupList.push_back(group6);

    Group group7("鹏城中学");
    group7.num=1;
    group7.isMember.push_back(0);
    group7.isMember.push_back(0);
    group7.isMember.push_back(1);
    groupList.push_back(group7);

    Group group8("哈弗大学");
    group8.num=1;
    group8.isMember.push_back(0);
    group8.isMember.push_back(0);
    group8.isMember.push_back(1);
    groupList.push_back(group8);

}

void FunctionalPage::showGroupInfo()
{
    GroupInfoDialog dialog(memberList,groupList,this);
    dialog.exec();
}
