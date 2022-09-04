#include "binarytree.h"
#include <queue>  //通过层次建立二叉树要用到队列
#include <QDebug>
#include <cmath>
#include <stack>

BinaryTree::BinaryTree(const int num):layerNum(num)
{

}

void BinaryTree::buildTree()
{
    int tag=0;
    int nodes=pow(2,layerNum-1)-1;
    root=new treeNode(tag);
    root->isLeaf=false;  //根结点默认不是叶子
     double rate=getLayer()/3.0*1.75;
    std::queue<treeNode*> q;
    q.push(root);
    NondeLabel * label=new NondeLabel(rate,0);
    node2label.insert(root,label);
    label2node.insert(label,root);

    node2label.insert(root,label);
    while(!q.empty())
    {
        treeNode * tmp=q.front();
        tmp->lchild=new treeNode(++tag);
        tmp->rchild=new treeNode(++tag);
        tmp->lchild->parent=tmp;
        tmp->rchild->parent=tmp;
        tmp->isLeaf=false; //不再是叶结点！


        //在这里将label和node 绑定
        NondeLabel * label1=new NondeLabel(rate,tag-1);

        node2label.insert(tmp->lchild,label1);
        label2node.insert(label1,tmp->lchild);
        connect(label1,&QPushButton::clicked,this,[&](){

        });
        NondeLabel * label2=new NondeLabel(rate,tag);
        node2label.insert(tmp->rchild,label2);
        label2node.insert(label2,tmp->rchild);

        q.pop();
        nodes--;
        if(nodes==0)
            break;
        q.push(tmp->lchild);

        q.push(tmp->rchild);

    }
    emit signal_buildtree();
}


int BinaryTree::getNodeNum(treeNode* r)
{
    if(r==nullptr)
        return 0;
    else
        return getNodeNum(r->lchild)+getNodeNum(r->rchild)+1;
}//返回结点数目

//先序遍历
void BinaryTree::preOrderTraverse()
{
    preOrderTraverseKernel(root);
}
void BinaryTree::preOrderTraverseKernel(treeNode * r)
{
    if(r!=nullptr)
    {
        emit signal_traverse(r);
        preOrderTraverseKernel(r->lchild);
        preOrderTraverseKernel(r->rchild);
    }
}

//中序遍历
void BinaryTree::midOrderTraverse()
{
    midOrderTraverseKernel(root);
}
void BinaryTree::midOrderTraverseKernel(treeNode * r)
{
    if(r!=nullptr)
    {
        midOrderTraverseKernel(r->lchild);
        emit signal_traverse(r);

        midOrderTraverseKernel(r->rchild);



    }
}

//后序遍历
void BinaryTree::postOrderTraverse()
{
    postOrderTraverseKernel(root);
}
void BinaryTree::postOrderTraverseKernel(treeNode * r)
{
    if(r!=nullptr)
    {
        postOrderTraverseKernel(r->lchild);
        postOrderTraverseKernel(r->rchild);
        emit signal_traverse(r);
    }
}

//清除线索
void BinaryTree::clearThread()
{
    std::stack<treeNode*>s;
    if(root==nullptr)
        return;
    s.push(root);
    while(!s.empty())
    {
        treeNode* node=s.top();
        s.pop();
        if(node->lchild!=nullptr&&node->ltag==0)  //正经结点而不是线索
        {

            s.push(node->lchild);

        }
        if(node->lchild!=nullptr&&node->ltag==1)
        {
            node->ltag=0;
            node->lchild=nullptr;
        }

        if(node->rchild!=nullptr&&node->rtag==0)  //正经结点而不是线索
        {

            s.push(node->rchild);

        }
        if(node->rchild!=nullptr&&node->rtag==1)
        {
            node->rtag=0;
            node->rchild=nullptr;
        }

    }
}

void BinaryTree::preOrderThread()
{
    treeNode *pre=nullptr;
    preOrderThreadKernel(root,pre);
}
void BinaryTree::preOrderThreadKernel(treeNode *root,treeNode * &pre)
{
    if(root)
    {
        if(root->lchild==nullptr)
        {
            root->ltag=1;
            root->lchild=pre;
        }
        else
            root->ltag=0;
        if(pre!=nullptr&&pre->rchild==nullptr)
        {
            pre->rtag=1;
            pre->rchild=root;
        }
        else
            root->rtag=0;

        pre=root;
        if(root->ltag==0)
            preOrderThreadKernel(root->lchild,pre);
        if(root->rtag==0)
            preOrderThreadKernel(root->rchild,pre);
    }

}

void BinaryTree::midOrderThread()
{
    treeNode *pre=nullptr;
    midOrderThreadKernel(root,pre);
}
void BinaryTree::midOrderThreadKernel(treeNode *root,treeNode * &pre)
{
    if(root)
    {
        if(root->ltag==0)
            midOrderThreadKernel(root->lchild,pre);
        if(root->lchild==nullptr)
        {
            root->ltag=1;
            root->lchild=pre;
        }
        else
            root->ltag=0;
        if(pre!=nullptr&&pre->rchild==nullptr)
        {
            pre->rtag=1;
            pre->rchild=root;
        }
        else
            root->rtag=0;

        pre=root;

        if(root->rtag==0)
            midOrderThreadKernel(root->rchild,pre);
    }
}

void BinaryTree::postOrderThread()
{
    treeNode *pre=nullptr;
    postOrderThreadKernel(root,pre);
}
void BinaryTree::postOrderThreadKernel(treeNode *root,treeNode * &pre)
{
    if(root)
    {
        if(root->ltag==0)
            postOrderThreadKernel(root->lchild,pre);
        if(root->rtag==0)
            postOrderThreadKernel(root->rchild,pre);
        if(root->lchild==nullptr)
        {
            root->ltag=1;
            root->lchild=pre;
        }
        else
            root->ltag=0;
        if(pre!=nullptr&&pre->rchild==nullptr)
        {
            pre->rtag=1;
            pre->rchild=root;
        }
        else
            root->rtag=0;

        pre=root;


    }
}

void BinaryTree::preOrderThreadTraverse()
{
    treeNode * p=root;
    while(p!=nullptr)
    {
        emit signal_traverse(p);
        if(p->ltag==0)
            p=p->lchild;
        else
            p=p->rchild;
    }
}

void BinaryTree::midOrderThreadTraverse()
{
    treeNode *p=root;
    while(p->ltag==0)
        p=p->lchild; //找到了起点

    while(p!=nullptr)
    {
        emit signal_traverse(p);
        //找下一个

        if(p->rtag==0&&p->rchild!=nullptr)
        {
            p=p->rchild;
            while(p->ltag==0)
                p=p->lchild; //找到了起点

        }
        else //无论是p->rchild=nulllptr(结束），或者是为线索，直接找到右孩子即可
        {
            p=p->rchild;
        }
    }
}

void BinaryTree::setLayer(int i)
{
    layerNum=i;
}

void BinaryTree::destroy()
{
    std::stack<BinaryTree::treeNode*> s;
    if(root==nullptr)
        return;
    s.push(root);

    while(!s.empty())
    {
        BinaryTree::treeNode * node=s.top();
        s.pop();
        if(node->lchild!=nullptr)
        {
            s.push(node->lchild);

        }
        if(node->rchild!=nullptr)
        {
            s.push(node->rchild);

        }

        NondeLabel * label=node2label[node];
        label2node.remove(label);
        delete label;
        node2label.remove (node);
        delete node;
    }
}

BinaryTree::~BinaryTree()
{
    destroy();
}

