#ifndef GROUPINFODIALOG_H
#define GROUPINFODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "utils.h"
#include <QGuiApplication>
#include <QScreen>

class GroupInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GroupInfoDialog(const QVector<person>&memberList,const QVector<Group>&groupList, QWidget *parent = nullptr);
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;

signals:

};

#endif // GROUPINFODIALOG_H
