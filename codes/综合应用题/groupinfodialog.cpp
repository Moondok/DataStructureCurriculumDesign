#include "groupinfodialog.h"
GroupInfoDialog::GroupInfoDialog(const QVector<person>&memberList,const QVector<Group>&groupList,QWidget *parent) : QDialog(parent)
{

    setMinimumSize(600*WIDTH_RATIO,1000*HEIGHT_RATIO);
    QLabel *title = new QLabel("以下为各个群组人员情况");
    title->setFont(QFont("隶书",12*WIDTH_RATIO,12*WIDTH_RATIO));
    title->setFixedSize(300*WIDTH_RATIO,60*HEIGHT_RATIO);
    title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QVBoxLayout* totallayout=new QVBoxLayout;

    totallayout->addWidget(title);
    for(auto const & i: groupList)
    {
        QGridLayout * newGroupLayout=new QGridLayout ;
        QLabel * groupName=new QLabel(i.groupname+"  共有"+QString::number(i.num)+"人");
        groupName->setFont(QFont("楷体",9*WIDTH_RATIO,9*HEIGHT_RATIO));
        newGroupLayout->addWidget(groupName,0,0,3,5);

        int cnt=0;
        for(int j=0;j<i.isMember.size();j++)
        {
            if(i.isMember.at(j)==true)
            {
                QLabel * newMember=new QLabel(memberList.at(j).name);
                newGroupLayout->addWidget(newMember,cnt/3+3,cnt%3,2,2);
                cnt++;
            }
        }
        totallayout->addLayout(newGroupLayout);
        //totallayout->setSpacing(45);
    }

    QPushButton * exitBtn=new QPushButton("返回");
    totallayout->addWidget(exitBtn);

    setLayout(totallayout);

    connect(exitBtn,&QPushButton::clicked,this,&QDialog::close);


}
