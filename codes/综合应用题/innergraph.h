#ifndef INNERGRAPH_H
#define INNERGRAPH_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QGuiApplication>
#include <QScreen>
const int MAX_NUM=30;

class InnerGraph : public QObject
{
    Q_OBJECT
public:
    explicit InnerGraph(QObject *parent = nullptr);
    int num;
    QVector<QVector<bool>> adjMatrix =QVector<QVector<bool>>(MAX_NUM,QVector<bool>(MAX_NUM)); //重要的二维数组

private:

signals:

};

#endif // INNERGRAPH_H
