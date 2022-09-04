#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QVector>

typedef struct Group
{
    QString groupname="";
    QVector<bool> isMember=QVector<bool>();
    int num=0;
    Group()
    {}
    Group(QString n):groupname(n)
    {}
}Group;

typedef struct person
{
    QString name="";
    QString primarySchool="";
    QString midSchool="";
    QString university="";
    QString workplace="";
    QString locality="";
    int tag;//独一无二的标志

    person()
    {}
    person(QString n,QString p,QString m,QString u,QString w,QString l=""):
        name(n),primarySchool(p),midSchool(m),university(u),workplace(w),locality(l)
    {}

} person;


#endif // UTILS_H
