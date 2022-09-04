#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include <QWidget>

class PaintBoard : public QWidget
{
    Q_OBJECT
public:
    explicit PaintBoard(QWidget *parent = nullptr,const int width=750,const int height=720);
    void paintEvent(QPaintEvent *event) ;
    ~PaintBoard();
private:
    int w=0;
    int h=0;
    QPixmap * map=nullptr;

signals:

};

#endif // PAINTBOARD_H
