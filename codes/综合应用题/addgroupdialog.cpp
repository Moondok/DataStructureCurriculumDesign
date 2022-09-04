#include "addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QVector<person>&personList,QVector<Group>&groupList,QWidget *parent) : QDialog(parent)
{


    setWindowTitle("添加新群组");
    setFixedSize(400*WIDTH_RATIO,600*HEIGHT_RATIO);
    QLabel * groupmessage=new QLabel("群组姓名");
    groupedit=new QLineEdit();

    QHBoxLayout * editLayout=new QHBoxLayout();
    editLayout->addWidget(groupmessage);
    editLayout->addWidget(groupedit);


    QLabel* chooseMemberMessage=new QLabel("以下哪些既有成员属于该群组");
    btns=new QButtonGroup(this);
    for(int i=0;i<personList.size();i++)
    {
        QRadioButton* btn=new QRadioButton(personList.at(i).name);
        btns->addButton(btn,i);
    }
    btns->setExclusive(false);
    QGridLayout* memberLayout=new QGridLayout;
    lst=btns->buttons();
    auto beg=lst.begin();
    auto end=lst.end();
    int cnt=0;
    for(auto ite=beg;ite!=end;ite++)
    {
        memberLayout->addWidget(*ite,cnt/4+3,cnt%4,3,2);
        cnt++;
    }
    memberLayout->addWidget(chooseMemberMessage,0,0,2,2);

    QPushButton * comfirmBtn=new QPushButton("确定");

    QPushButton * cancelBtn=new QPushButton("取消");
    QHBoxLayout * btnLayout=new QHBoxLayout();
    btnLayout->addWidget(comfirmBtn);
    btnLayout->addWidget(cancelBtn);

    connect(cancelBtn,&QPushButton::clicked,this,&QDialog:: reject);

    connect(comfirmBtn,&QPushButton::clicked,this,[&](){

        if(!isValid(groupList))
        {
            QMessageBox::warning(this,"警告","信息不完整或有重复。");
        }
        else
        {
             accept();
        }
    });



    QVBoxLayout* totalLayout=new QVBoxLayout;
    totalLayout->addLayout(editLayout);
    totalLayout->setMargin(30*HEIGHT_RATIO);
    totalLayout->addLayout(memberLayout);
    totalLayout->setMargin(30*HEIGHT_RATIO);
    totalLayout->addLayout(btnLayout);

    setLayout(totalLayout);
}
