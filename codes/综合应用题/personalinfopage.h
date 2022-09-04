#ifndef PERSONALINFOPAGE_H
#define PERSONALINFOPAGE_H

#include <QMainWindow>
#include <QVector>
#include "utils.h"
#include "innergraph.h"
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QPair>
#include <stdlib.h>
#include <QGuiApplication>
#include <QScreen>


const double PI=3.1415926;
class PersonalInfoPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit PersonalInfoPage(QVector<person>& p,QVector<Group> & g,InnerGraph * _graph,QString n,QWidget *parent = nullptr);
    void editBrowser();

    ~PersonalInfoPage()
    {
        if(textBrowser!=nullptr)
            delete textBrowser;
    }

private:
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;

    QVector<person>& personList;
    QVector<Group> & groupList;
    InnerGraph * graph=nullptr;

    void paintEvent(QPaintEvent*);
    QString name;
    QTextBrowser * textBrowser=nullptr;
    QVector<QPair<person,int>> correlationList;

    int id;
    int getId();

    void getCorrelation();




signals:
    void return2lastPage();


};

bool operator<(const QPair<person,int>& a,const QPair<person,int>& b);


#endif // PERSONALINFOPAGE_H
