#ifndef FUNCTIONALPAGE_H
#define FUNCTIONALPAGE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QMessageBox>
#include <QGridLayout>
#include <QList>
#include <QVBoxLayout>
#include "utils.h"
#include "addmemberdialog.h"
#include "addgroupdialog.h"
#include "innergraph.h"
#include "groupinfodialog.h"

const int MAX_MEMBER_NUM=25;
const int MAX_GROUP_NUM=18;


class FunctionalPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit FunctionalPage(QWidget *parent = nullptr);

    ~FunctionalPage()
    {
        if(textBrowser!=nullptr)
            delete textBrowser;
        if(graph!=nullptr)
            delete graph;
    }
private:
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;

    QTextBrowser * textBrowser=nullptr;
    void paintEvent(QPaintEvent*);

    QVector<Group> groupList=QVector<Group>();//这个Qvector里面包含了所有的群组

    QVector<person> memberList=QVector<person>();

   //槽函数，设置一个对话框
    void getMemberInfo();

    void getGroupInfo();

    void getChooseInfo();

    void initMember();

    void initGroup();

    InnerGraph *graph=nullptr;

    //根据名字找寻可能认识的人
    void showInfo(const QString &name);

    void showGroupInfo();

signals:
    void return2mainpage();


};

#endif // FUNCTIONALPAGE_H
