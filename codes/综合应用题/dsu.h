#ifndef DSU_H
#define DSU_H

#include <QObject>
#include "innergraph.h"

class DSU : public QObject
{
    Q_OBJECT
public:
    explicit DSU(QObject *parent = nullptr);
   QVector<int> par=QVector<int>(MAX_NUM);

signals:


//我们需要一个结构将不同的群组和其中的一个（只需要一个，因为有DSU）关联起来

};

#endif // DSU_H
