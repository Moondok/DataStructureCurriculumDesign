#ifndef NONDELABEL_H
#define NONDELABEL_H

#include <QWidget>
#include <QPushButton>
#include<QString>
#include <QLabel>

class NondeLabel : public QPushButton
{
    Q_OBJECT
public:
    explicit NondeLabel(double rate=1,int index=1,QString normalImg="://image//nodeimage1.png" ,QString pressImg="://image//nodeimage2.png");

    void focused();
    void released();
private:
    QLabel label;
    QString picPath1;
    QString picPath2;
    QPixmap pix;
    double shrinkRate=0;
    const int index;

signals:

};

#endif // NONDELABEL_H
