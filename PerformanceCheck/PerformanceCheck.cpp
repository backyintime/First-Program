#include "PerformanceCheck.h"

QVector < QVector<BiTreeNode* >>* PerformanceCheck::infos_tree = new QVector < QVector<BiTreeNode* >>;
QVector<BiTreeNode*>* PerformanceCheck::node_group = new QVector<BiTreeNode*>;;
BiTreeNode* PerformanceCheck::current = nullptr;
BiTreeNode* PerformanceCheck::root;

int PerformanceCheck::func_id = 0;

PerformanceCheck::PerformanceCheck(const QString& message)
{
    m_Message = new QString(message/* + "," + QString::number(func_id++)*/);

    RecordInfo();    //存储信息

    m_Start = std::chrono::high_resolution_clock::now();    //设置开始时间
    m_End = m_Start;
}

PerformanceCheck::~PerformanceCheck()
{
    m_End = std::chrono::high_resolution_clock::now();
    //*m_Message += "," + QString::number(std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count());

    int i = FindThread(*thread_id);
    if (i != -1)
    {
        current = (*infos_tree)[i][CURRENT];
        current->time = std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count();
        //root->time += current->time;
        if (current->parent != nullptr)
        {
            current = current->parent;
            (*infos_tree)[i][CURRENT] = current;
        }
    }

}

void PerformanceCheck::RecordInfo()
{
    BiTreeNode* new_node = new BiTreeNode;
    new_node->func_info = m_Message;

    thread_id = new QString(QString::number(GetCurrentThreadId()));
    int i = FindThread(*thread_id);
    if (i != -1)
    {
        current = (*infos_tree)[i][CURRENT];
        if (current->leftChild != nullptr)
        {
            current = current->leftChild;
            while (current->rightChild != nullptr)
            {
                current = current->rightChild;
            }
            current->rightChild = new_node;
             new_node->parent = current->parent;
        }
        else
        {
            current->leftChild = new_node;
            new_node->parent = current;
        }
        current = new_node;
        (*infos_tree)[i][CURRENT] = current;
    }
    else     //新线程
    {
        root = new BiTreeNode;
        root->func_info = thread_id;
        root->time = 0;
        root->leftChild = new_node;
        new_node->parent = root;
        current = new_node;

        node_group->clear();

        node_group->push_back(root);
        node_group->push_back(new_node);
        infos_tree->push_back(*node_group);
    }
}

int PerformanceCheck::FindThread(const QString &message)
{
    for (int i = 0; i < infos_tree->size(); i++)
    {
        if (*(*infos_tree)[i][ROOT]->func_info == message)
            return i;
    }
    return -1;
}

void PerformanceCheck::InOrder(BiTreeNode *subTree)
{
    QStack<BiTreeNode*> S;
    BiTreeNode* t;
    S.push(subTree);    //根节点进栈
    while (!S.empty())  //当栈不为空
    {
        t = S.top();    //p先记住栈顶元素，然后栈顶出栈
        S.pop();
        qDebug() << *t->func_info << " ";    //访问元素
        if (t->rightChild != NULL)      //右孩子不为空，右孩子进栈
        {
            S.push(t->rightChild);
        }
        if (t->leftChild != NULL)       //左孩子不为空，左孩子进栈
        {
            S.push(t->leftChild);
        }
    }
}

void PerformanceCheck::ShowInfo()
{
    for (int i = 0; i < infos_tree->size(); ++i)
        InOrder((*infos_tree)[i][ROOT]);
}

QVector<QVector<BiTreeNode*>> *&PerformanceCheck::GetRoot()
{
    return infos_tree;
}

void PerformanceCheck::DelTree(BiTreeNode *node)
{
    if (node != nullptr)
    {
        DelTree(node->leftChild);
        DelTree(node->rightChild);
        delete  node->func_info;
        delete node;
        node = nullptr;
    }
}

void PerformanceCheck::DelVector()
{
    for (int i = 0; i < infos_tree->size(); ++i)
        DelTree((*infos_tree)[i][ROOT]);

    delete node_group;
    delete infos_tree;
}

