#include "utils.h"
#include <QDebug>
void drawArrow(QPainter& painter,int x1,int y1,int x2,int y2)
{

    double len=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    double l=len/8;

    QPoint midPoint=QPoint(8.0/9*x2+1.0/9*x1,8.0/9*y2+1.0/9*y1);
    QPoint unitVec(-1.0*(y2-y1)*1000,1.0*(x2-x1)*1000);

    double newx1,newx2,newy1,newy2;

    newx1=midPoint.x()+1.0*unitVec.x()/1000/len*l*0.4;
    newx2=midPoint.x()-1.0*unitVec.x()/1000/len*l*0.4;

    newy1=midPoint.y()+1.0*unitVec.y()/1000/len*l*0.4;
    newy2=midPoint.y()-1.0*unitVec.y()/1000/len*l*0.4;

   painter.drawLine(newx1,newy1,x2,y2);
   painter.drawLine(x1,y1,x2,y2);
   painter.drawLine(newx2,newy2,x2,y2);


}
