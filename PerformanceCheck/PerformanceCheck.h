#pragma once
#include <QString>
#include <QVector>
#include <QHash>
#include <QStack>
#include <QDebug>
#include <chrono>

#define CONSUMING_OUTPUT(a) PerformanceCheck Class(a)
#define PERF_CHECK CONSUMING_OUTPUT(Q_FUNC_INFO)

struct BiTreeNode 
{
    QString func_info;
    qint64 time = 0;
    BiTreeNode* parent = nullptr;
    QVector<BiTreeNode*> children;
};

typedef QVector<QVector<BiTreeNode*>> InfoTree;

class PerformanceCheck
{
public:
    PerformanceCheck(const QString& funcName);
    ~PerformanceCheck();

    static void ShowInfo();
    static void Cleanup();
    static InfoTree getInfoTree() {return infos_tree; }

private:
    void RecordInfo();
    static int GetOrAddThreadIndex(const QString& threadId);
    static void PrintTree(BiTreeNode* node, int depth = 0);
    static void DeleteTree(BiTreeNode* node);

private:
    QString m_funcName;
    std::chrono::high_resolution_clock::time_point m_Start, m_End;

    static inline QHash<QString, int> threadIndexMap;
    static inline InfoTree infos_tree;
};
