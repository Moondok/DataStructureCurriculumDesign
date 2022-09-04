#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<QObject>
#include<QMap>
#include "nondelabel.h"
#include <QTimer>

class BinaryTree:public QObject
{


    Q_OBJECT
private:
    int layerNum=0;


public:
    typedef struct treeNode
    {
        int data=0;
        treeNode * lchild=nullptr;
        treeNode * rchild=nullptr;
        treeNode * parent=nullptr;
        bool ltag=0;
        bool rtag=0;
        bool isLeaf=true;

        treeNode(const int i):data(i)
        {

        }
        treeNode(){}
    } treeNode;
    BinaryTree(const int layNum=4); //注意此处默认满二叉树
    int getLayer()
    {
        return layerNum;
    }
    void buildTree();
    int getNodeNum(treeNode*r);  //返回结点数目

    void preOrderTraverse();  //先序遍历
    void preOrderTraverseKernel(treeNode*r);  //先序遍历

    void midOrderTraverse();
    void midOrderTraverseKernel(treeNode*r);  //中序遍历

    void postOrderTraverse(); //后序遍历
    void postOrderTraverseKernel(treeNode*r);  //后序遍历

    void clearThread();//清理线索化痕迹
    void preOrderThread();// 先序线索化
    void preOrderThreadKernel(treeNode *root,treeNode * &pre);
    void midOrderThread(); //中序线索化
    void midOrderThreadKernel(treeNode *root,treeNode * &pre);
    void postOrderThread();
     void postOrderThreadKernel(treeNode *root,treeNode * &pre);

    void preOrderThreadTraverse(); //先序线索化遍历
    void midOrderThreadTraverse();
    ~BinaryTree();
    void destroy();
    void setLayer(int i);


    treeNode *root=nullptr;  //二叉树根结点

    QVector<NondeLabel> uiList;  //这里存储着所有的label
    QMap<treeNode*,NondeLabel*> node2label;
    QMap<NondeLabel*,treeNode*> label2node;

signals:
    void signal_buildtree();
    void signal_traverse(treeNode* node);
};


#endif // BINARYTREE_H
