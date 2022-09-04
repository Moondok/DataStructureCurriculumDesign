#include "personalinfopage.h"
extern double WIDTH_RATIO;
extern double HEIGHT_RATIO;
PersonalInfoPage::PersonalInfoPage(QVector<person>& p,QVector<Group> & g,InnerGraph * _graph,QString n,QWidget *parent) :
    QMainWindow(parent),personList(p),groupList(g),graph(_graph),name(n)

{
    this->setFixedSize(1600*WIDTH_RATIO,1000*HEIGHT_RATIO);
    textBrowser=new QTextBrowser(this);
    textBrowser->setFixedSize(440*WIDTH_RATIO,500*HEIGHT_RATIO);
    textBrowser->move(1140*WIDTH_RATIO,475*HEIGHT_RATIO);


    QLabel* message=new QLabel("详细信息",this);
    message->setFont(QFont("楷体",20*WIDTH_RATIO,15*HEIGHT_RATIO));
    message->setAlignment((Qt::AlignVCenter|Qt::AlignHCenter));
    message->setFixedSize(370*WIDTH_RATIO,80*HEIGHT_RATIO);
    message->move(1180*WIDTH_RATIO,380*HEIGHT_RATIO);

    QPushButton* returnBtn=new QPushButton("返回上页",this);
    returnBtn->setFixedSize(200*WIDTH_RATIO,70*HEIGHT_RATIO);
    returnBtn->setFont(QFont("宋体",13*WIDTH_RATIO,13*HEIGHT_RATIO));
    returnBtn->move(1250*WIDTH_RATIO,50*HEIGHT_RATIO);

    QPushButton* exitBtn=new QPushButton("退出程序",this);
    exitBtn->setFixedSize(200*WIDTH_RATIO,70*HEIGHT_RATIO);
    exitBtn->setFont(QFont("宋体",13*WIDTH_RATIO,13*HEIGHT_RATIO));
    exitBtn->move(1250*WIDTH_RATIO,165*HEIGHT_RATIO);

    connect(returnBtn,&QPushButton::clicked,this,[=](){
        emit return2lastPage();
    });
    connect(exitBtn,&QPushButton::clicked,this,&QMainWindow::close);

    id=getId();//获取这个名字是第几个

    //画出标住
    QPixmap pix1("://images//mark1.png");
    QLabel* label1=new QLabel(this);
    label1->setPixmap(pix1.scaled(30*WIDTH_RATIO,30*HEIGHT_RATIO,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label1->move(1130*WIDTH_RATIO,300*HEIGHT_RATIO);
    QLabel* labelMessage1=new QLabel("当前成员",this);
    labelMessage1->setFont(QFont("楷体",11*WIDTH_RATIO,11*HEIGHT_RATIO));
    labelMessage1->setFixedSize(90*WIDTH_RATIO,50*HEIGHT_RATIO);
    labelMessage1->move(1165*WIDTH_RATIO,290*HEIGHT_RATIO);

    QPixmap pix2("://images//mark2.png");
    QLabel* label2=new QLabel(this);
    label2->setPixmap(pix2.scaled(30*WIDTH_RATIO,30*HEIGHT_RATIO,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label2->move(1265*WIDTH_RATIO,300*HEIGHT_RATIO);
    QLabel* labelMessage2=new QLabel("认识的人",this);
    labelMessage2->setFont(QFont("楷体",11*WIDTH_RATIO,11*HEIGHT_RATIO));
    labelMessage2->setFixedSize(90*WIDTH_RATIO,50*HEIGHT_RATIO);
    labelMessage2->move(1305*WIDTH_RATIO,290*HEIGHT_RATIO);

    QPixmap pix3("://images//mark3.png");
    QLabel* label3=new QLabel(this);
    label3->setPixmap(pix3.scaled(30*WIDTH_RATIO,30*HEIGHT_RATIO,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label3->move(1400*WIDTH_RATIO,300*HEIGHT_RATIO);
    QLabel* labelMessage3=new QLabel("可能认识的人",this);
    labelMessage3->setFont(QFont("楷体",11*WIDTH_RATIO,11*HEIGHT_RATIO));
    labelMessage3->setFixedSize(135*WIDTH_RATIO,50*HEIGHT_RATIO);
    labelMessage3->move(1440*WIDTH_RATIO,290*HEIGHT_RATIO);





    //初始化关联度列表
    for(int i=0;i<personList.size();i++)
        correlationList.push_back(QPair<person,int>(personList.at(i),0));

    std::sort(correlationList.begin(),correlationList.end());

}

void PersonalInfoPage::paintEvent(QPaintEvent*)
{
    QPixmap map(1100*WIDTH_RATIO,930*HEIGHT_RATIO);
    map.fill(QColor(255,250,240));
    QPainter painter(this);
    painter.drawPixmap(20*WIDTH_RATIO,35*HEIGHT_RATIO,map.width(),map.height(),map);

    //在获取关联度之后，画图
    int num=personList.size();

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
    for(int i=0;i<personList.size();i++)
    {
        for(int j=0;j<personList.size();j++)
        {
            if(i!=j&&graph->adjMatrix[i][j])
            {
                painter3.drawLine(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),
                                  QPoint(ox+r*cos(2*PI/360*gap*j),oy+r*sin(2*PI/360*gap*j)));
            }
        }
    }


    QPen pen(Qt::white);
    pen.setWidth(2);
    QPainter painter2(this);
    painter2.setRenderHint(QPainter::HighQualityAntialiasing);
     painter2.setPen(pen);
     QBrush brush(QColor(255,106,106));
     painter2.setBrush(brush);


    for(int i=0;i<num;i++)
    {
        if(i==id)
        {

            painter2.setBrush(QColor(255,106,106)); //自己
            painter2.drawEllipse(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),R,R);
            painter2.drawText(QRectF(ox+r*cos(2*PI/360*gap*i)-l,oy+r*sin(2*PI/360*gap*i)-l,2*l,2*l),
                              Qt::AlignVCenter|Qt::AlignHCenter,personList.at(i).name);

        }
        else if(graph->adjMatrix[i][id]==true)
        {
            painter2.setBrush(QColor(152,251,152)); //好友
            painter2.drawEllipse(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),R,R);
            painter2.drawText(QRectF(ox+r*cos(2*PI/360*gap*i)-l,oy+r*sin(2*PI/360*gap*i)-l,2*l,2*l),
                              Qt::AlignVCenter|Qt::AlignHCenter,personList.at(i).name);
        }
        else
        {
            painter2.setBrush(QColor(99,184,255));  //可能认识的人
            painter2.drawEllipse(QPoint(ox+r*cos(2*PI/360*gap*i),oy+r*sin(2*PI/360*gap*i)),R,R);
            painter2.drawText(QRectF(ox+r*cos(2*PI/360*gap*i)-l,oy+r*sin(2*PI/360*gap*i)-l,2*l,2*l),
                              Qt::AlignVCenter|Qt::AlignHCenter,personList.at(i).name);
        }
    }

}

int PersonalInfoPage::getId()
{
    int cnt=0;
    for(int i=0;i<personList.size();i++)
    {
        if(personList.at(i).name==name)
        {
            cnt=i;
            break;
        }

    }
    return cnt;
}

void PersonalInfoPage::getCorrelation()
{

    int num=personList.size();
    int cor=0;
    for(int i=0;i<num;i++)
    {
        cor=0;
        if(graph->adjMatrix[i][id]||i==id)
            continue;
        for(int k=0;k<num;k++)
        {
            if(k==i||k==id)
                continue;
            if(graph->adjMatrix[i][k]==true&&graph->adjMatrix[id][k]==true)
                cor++;

        }
        //cor即为i和id的关联度数
        correlationList[i].second=cor;
    }

}

void PersonalInfoPage::editBrowser()
{

    textBrowser->append("您要查询的成员是"+name+"\n");
    person target=personList.at(id);
    if(target.primarySchool!="")
        textBrowser->append("他/她所就读的小学是: "+target.primarySchool+"\n");
    if(target.midSchool!="")
        textBrowser->append("他/她所就读的中学是: "+target.midSchool+"\n");
    if(target.university!="")
        textBrowser->append("他/她所就读的大学是: "+target.university+"\n");
    if(target.workplace!="")
        textBrowser->append("他/她的工作单位是: "+target.workplace+"\n");
    if(target.locality!="")
        textBrowser->append("他/她所在的地域是: "+target.locality+"\n");

    textBrowser->append("\n");

    getCorrelation();
   // std::sort(correlationList.begin(),correlationList.end());
    //排序：冒泡：
    for(int i=0;i<correlationList.size()-1;i++)
        for(int j=0;j<correlationList.size()-1-i;j++)
        {
            if(correlationList.at(j).second<correlationList.at(j+1).second)
            {
                QPair<person,int> tmp=correlationList[j];
                correlationList[j]=correlationList[j+1];
                correlationList[j+1]=tmp;



            }
        }

    textBrowser->append("以下是 "+name+" 可能认识的人\n");
    for(int i=0;i<=correlationList.size()-1;i++) //这里的i不是邻接矩阵中的顺序
    {
        int trueI=correlationList.at(i).first.tag;
        if(trueI!=id&&!graph->adjMatrix[trueI][id])//tag派上用场！
        {
            int commonGroupNum=0;
             for(auto const&i:groupList)
             {
                if(i.isMember.at(trueI)&&i.isMember.at(id))
                    commonGroupNum++;
             }
             textBrowser->append(correlationList.at(i).first.name+" 关联度为 "+QString::number(correlationList.at(i).second)
                                 +" ，有"+QString::number(commonGroupNum)+" 个共同群组");
        }
    }

}

bool operator<(const QPair<person,int>& a,const QPair<person,int>& b)
{
    return a.second>b.second;//比较关联度
}
