#include "paintboard.h"
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>


PaintBoard::PaintBoard(QWidget *parent,const int width,const int height) : QWidget(parent),w(width),h(height)
{
    setFixedSize(w,h);
}

void PaintBoard::paintEvent(QPaintEvent*)
{
    map=new QPixmap(w,h);
    map->fill(Qt::white);
    QPainter painter(this);
    painter.drawPixmap(0,0,*map);

}

PaintBoard::~PaintBoard()
{
    if(map!=nullptr)
        delete map;
}
