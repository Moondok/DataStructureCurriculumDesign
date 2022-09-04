#include "addmemberdialog.h"
AddmemberDialog::AddmemberDialog(QVector<person> &personList,QVector<Group>&groupList,QWidget *parent) : QDialog(parent)
{

    setFixedSize(700*WIDTH_RATIO,1200*HEIGHT_RATIO);
    setWindowTitle("添加新成员");
    QLabel* namelabel=new QLabel("姓名");
    QLabel* primarySchoolName= new QLabel("小学");
    QLabel* midSchoolName= new QLabel("中学");
    QLabel* universityName= new QLabel("大学");
    QLabel* workplaceName= new QLabel("工作单位");
    QLabel * localityName=new QLabel("地区");

    nameEdit=new QLineEdit();
     primarySchoolEdit= new QLineEdit();
    midSchoolEdit= new QLineEdit();
     universityEdit= new QLineEdit();
     workplaceEdit= new QLineEdit();
    localityEdit=new QLineEdit();

    nameEdit=new QLineEdit();
    primarySchoolEdit= new QLineEdit();
    midSchoolEdit= new QLineEdit();
    universityEdit= new QLineEdit();
    workplaceEdit= new QLineEdit();
    localityEdit=new QLineEdit();
    QGridLayout * editLayout=new QGridLayout();
    editLayout->addWidget(namelabel,0,0);
    editLayout->addWidget(nameEdit,0,1);
    editLayout->addWidget(primarySchoolName,1,0);
    editLayout->addWidget(primarySchoolEdit,1,1);
    editLayout->addWidget(midSchoolName,2,0);
    editLayout->addWidget(midSchoolEdit,2,1);
    editLayout->addWidget(universityName,3,0);
    editLayout->addWidget(universityEdit,3,1);
    editLayout->addWidget(workplaceName,4,0);
    editLayout->addWidget(workplaceEdit,4,1);
    editLayout->addWidget(localityName,5,0);
    editLayout->addWidget(localityEdit,5,1);

    //现在我们需要一个选择 既有的 朋友 和群组
    //再来一个选择 是否是某个既有群组成员的 按钮组
    QLabel* groupSetMessage=new QLabel("属于下列哪个既有群组");
    //创建好友列表

    QButtonGroup* groupSetList= new QButtonGroup(this);
    for(int i=0;i<groupList.size();i++)
    {
        QRadioButton * chooseBtn=new QRadioButton(QString(groupList.at(i).groupname),this);
        groupSetList->addButton(chooseBtn,i);
        //这里的id号就是顺序和tag
    }
    groupSetList->setExclusive(false);
    QGridLayout * groupLayout=new QGridLayout();
    btnList1=groupSetList->buttons();
    auto beg1=btnList1.begin();
    auto end1=btnList1.end();

    int cnt=0;  //控制位置的计数器
    groupLayout->addWidget(groupSetMessage,0,0,3,3);
    for(auto ite=beg1;ite!=end1;ite++)
    {
        groupLayout->addWidget(*ite,cnt/3+3,cnt%3,3,3);
        cnt++;
    }

    QLabel* friendSetMessage=new QLabel("下列哪个是他的朋友");
    //创建好友列表
    QButtonGroup* friendSetList= new QButtonGroup(this);
    for(int i=0;i<personList.size();i++)
    {
        QRadioButton * chooseBtn=new QRadioButton(QString(personList.at(i).name),this);
        friendSetList->addButton(chooseBtn,i);
        //这里的id号就是顺序和tag
    }
    friendSetList->setExclusive(false);//显然可以多选
    //好友按钮的布局
    QGridLayout * friendLayout=new QGridLayout();
    btnList2=friendSetList->buttons();
    auto beg2=btnList2.begin();
    auto end2=btnList2.end();
    friendLayout->addWidget(friendSetMessage,0,0,3,0);
    cnt=0;
    for(auto ite=beg2;ite!=end2;ite++)
    {
        friendLayout->addWidget(*ite,cnt/3+4,cnt%3,3,2);
        cnt++;
    }

    comfirmBtn=new QPushButton("确认");
    cancelBtn=new QPushButton("取消");
    QHBoxLayout * btnLayout=new QHBoxLayout();
    btnLayout->addWidget(comfirmBtn);
    btnLayout->addWidget(cancelBtn);

    totalLayout=new QVBoxLayout;
    totalLayout->addLayout(editLayout);
    totalLayout->setMargin(50);
    totalLayout->addLayout(friendLayout);
    totalLayout->setMargin(50);
    totalLayout->addLayout(groupLayout);
    totalLayout->setMargin(50);
    totalLayout->addLayout(btnLayout);

    setLayout(totalLayout);

    connect(comfirmBtn,&QPushButton::clicked,this,[=](){

        if(!isValid())
        {
            QMessageBox::warning(this,"警告","信息不完整或有重复。");
        }
        else
        {
            emit acceptit();
             accept();
        }
    });

    connectStuff();


}

void AddmemberDialog::connectStuff()
{
    connect(cancelBtn,&QPushButton::clicked,this,&QDialog::reject);

}
