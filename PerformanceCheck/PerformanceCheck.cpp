#include "performancecheck.h"
#include <QThread>

PerformanceCheck::PerformanceCheck(const QString& funcName)
    : m_funcName(funcName), m_Start(std::chrono::high_resolution_clock::now()) 
{
    RecordInfo();
}

PerformanceCheck::~PerformanceCheck() 
{
    m_End = std::chrono::high_resolution_clock::now();
    qint64 elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count();

    QString threadId = QString::number(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    int idx = GetOrAddThreadIndex(threadId);
    BiTreeNode*& current = infos_tree[idx][1];
    current->time = elapsed;

    if (current->parent) 
    {
        current = current->parent;
        infos_tree[idx][1] = current;
    }
}

void PerformanceCheck::RecordInfo() 
{
    auto* newNode = new BiTreeNode;
    newNode->func_info = m_funcName;

    QString threadId = QString::number(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    int idx = GetOrAddThreadIndex(threadId);

    BiTreeNode*& current = infos_tree[idx][1];
    BiTreeNode* parent = current;
    parent->children.append(newNode);
    newNode->parent = parent;
    infos_tree[idx][1] = newNode;
}

int PerformanceCheck::GetOrAddThreadIndex(const QString& threadId)
{
    if (threadIndexMap.contains(threadId)) {
        return threadIndexMap[threadId];
    }

    auto* root = new BiTreeNode;
    root->func_info = QString("Thread %1").arg(threadId);
    root->time = 0;

    BiTreeNode* current = root;

    QVector<BiTreeNode*> group;
    group.append(root); 
    group.append(current);

    int index = infos_tree.size();
    infos_tree.append(group);
    threadIndexMap[threadId] = index;
    return index;
}

void PerformanceCheck::ShowInfo() {
    for (const auto& group : infos_tree) {
        PrintTree(group[0]);
    }
}

void PerformanceCheck::PrintTree(BiTreeNode* node, int depth) 
{
    if (!node) return;

    qDebug().noquote() << QString(depth * 2, ' ') << node->func_info << ": " << node->time << "ns";
    for (auto* child : node->children) 
    {
        PrintTree(child, depth + 1);
    }
}

void PerformanceCheck::Cleanup()
{
    for (auto& group : infos_tree)
        DeleteTree(group[0]);
    
    infos_tree.clear();
    threadIndexMap.clear();
}

void PerformanceCheck::DeleteTree(BiTreeNode* node) 
{
    if (!node) return;
    for (auto* child : node->children) 
        DeleteTree(child);
   
    delete node;
}
