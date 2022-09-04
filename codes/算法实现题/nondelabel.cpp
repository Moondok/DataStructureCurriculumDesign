#include "nondelabel.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QString>

NondeLabel::NondeLabel(double rate,int i,QString normalImg ,QString pressImg):
    picPath1(normalImg),picPath2(pressImg),shrinkRate(rate),index(i)
{
    bool ret=pix.load(normalImg);
    if(!ret)
           qDebug()<<"图片无法加载！";

    this->setFixedSize(pix.width()/shrinkRate,pix.height()/shrinkRate);

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()/shrinkRate,pix.height()/shrinkRate));

    label.setFixedSize(this->width(),this->height());
    label.setText(QString::number(index));
    label.setParent(this);
    label.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label.show();
}

void NondeLabel::focused()
{
    pix.load(picPath2);

    this->setFixedSize(pix.width()/shrinkRate,pix.height()/shrinkRate);

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(this->pix.width()/this->shrinkRate,this->pix.height()/shrinkRate));
}

void NondeLabel::released()
{
    pix.load(picPath1);

    this->setFixedSize(pix.width()/shrinkRate,pix.height()/shrinkRate);

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(this->pix.width()/this->shrinkRate,this->pix.height()/shrinkRate));
}
