#pragma once
#include<chrono>
#include<QVector>
#include<QStack>
#include<QString>
#include<QDebug>
#include<windows.h>

#define CONSUMING_OUTPUT(a) PerformanceCheck Class(a)
#define PERF_CHECK CONSUMING_OUTPUT(Q_FUNC_INFO)

#define ROOT    0
#define CURRENT 1
typedef long long ll;

struct BiTreeNode
{
    QString* func_info;
    ll time;

    BiTreeNode* leftChild = nullptr, * rightChild = nullptr, * parent = nullptr;                                                                    //左子树和右子树
};

class PerformanceCheck
{
public:
    PerformanceCheck(const QString& message);
    ~PerformanceCheck();


    void RecordInfo();                                      //记录信息
    int FindThread(const QString& message);                 //查找线程
    static void InOrder(BiTreeNode* subTree);               //先序遍历二叉树
    static void ShowInfo();                                 //显示信息
    static QVector<QVector<BiTreeNode*>> *& GetRoot();      //获取根结点
    static void DelTree(BiTreeNode *node);                 //删除信息树
    static void DelVector(/*QVector<QVector<BiTreeNode*>> *&*/);//删除容器

private:
    std::chrono::high_resolution_clock::time_point m_Start; //起始时间
    std::chrono::high_resolution_clock::time_point m_End;   //结束时间

    QString *thread_id;                                     //线程 id
    QString* m_Message;

    static QVector<QVector<BiTreeNode*>>* infos_tree;       //信息树
    static QVector<BiTreeNode*>* node_group;                //当前结点和根结点
    static BiTreeNode* current;                             //当前结点
    static BiTreeNode* root;                                //根结点

    static int func_id;                                     //函数 id
};
