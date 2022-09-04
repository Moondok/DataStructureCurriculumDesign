#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include "utils.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>



class AddmemberDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddmemberDialog(QVector<person> &personList,QVector<Group>&groupList,QWidget *parent = nullptr);
    QList<QAbstractButton*> btnList2;
    QList<QAbstractButton*> btnList1;



    bool isValid()
    {
        bool tag=1;
        QString name=nameEdit->text();
        if(name=="")
            tag=false;
        else
        {
            for(auto ite=btnList2.begin();ite!=btnList2.end();ite++)//这里通过按钮数组访问
            {
                if(name==(*ite)->text())
                {
                    tag=false;
                    break;
                }
            }
        }
        return tag;
    }

    QLineEdit* nameEdit=nullptr;
    QLineEdit* primarySchoolEdit=nullptr;
    QLineEdit* midSchoolEdit=nullptr;
    QLineEdit* universityEdit=nullptr;
    QLineEdit* workplaceEdit=nullptr;
    QLineEdit * localityEdit=nullptr;

    ~AddmemberDialog()
    {
        if(nameEdit!=nullptr)
            delete nameEdit;
        if(primarySchoolEdit!=nullptr)
            delete primarySchoolEdit;
        if(midSchoolEdit!=nullptr)
            delete midSchoolEdit;
        if(universityEdit!=nullptr)
            delete universityEdit;
        if(workplaceEdit!=nullptr)
            delete workplaceEdit;
        if(localityEdit!=nullptr)
            delete localityEdit;
        if(totalLayout!=nullptr)
            delete totalLayout;
        if(comfirmBtn!=nullptr)
            delete comfirmBtn;
        if(cancelBtn!=nullptr)
            delete cancelBtn;
    }
private:
    QSize size=QGuiApplication::primaryScreen()->size();
    double WIDTH_RATIO=std::min(size.width()*1.0/2160,size.height()*1.0/1440);
    double HEIGHT_RATIO=WIDTH_RATIO;
    QVBoxLayout* totalLayout=nullptr;



    QPushButton * comfirmBtn=nullptr;
    QPushButton * cancelBtn=nullptr;

    void connectStuff();

signals:
    void acceptit();

};

#endif // ADDMEMBERDIALOG_H
