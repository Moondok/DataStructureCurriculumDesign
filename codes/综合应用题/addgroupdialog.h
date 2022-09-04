#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QWidget>
#include <QDialog>
#include "utils.h"
#include <QLabel>
#include <QString>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>


class AddGroupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddGroupDialog(QVector<person>&personList,QVector<Group>&groupList,QWidget *parent = nullptr);
    QButtonGroup* btns=nullptr;
    QList<QAbstractButton*> lst;

    bool isValid(QVector<Group>&groupList)
    {
        bool tag=1;
        QString name=groupedit->text();
        if(name=="")
            tag=false;
        else
        {
            for(auto ite=groupList.begin();ite!=groupList.end();ite++)//这里通过按钮数组访问
                if(name==(*ite).groupname)
                {
                    tag=false;
                    break;
                }
        }
        return tag;
    }

    QLineEdit * groupedit=nullptr;
    ~AddGroupDialog()
    {
        if(btns!=nullptr)
            delete btns;

        if(groupedit!=nullptr)
            delete groupedit;
    }

private:
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;

signals:

};

#endif // ADDGROUPDIALOG_H
