#pragma once

#include <QMainWindow>
#include "performancecheck.h"
#include"myheaderview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QTreeWidgetItem;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetTreeNode(BiTreeNode *node,QTreeWidgetItem* parentItem);
    void SetTreeWidget();
    void changeTimeUnit(int multiple);
private:
    void InitUi();
    void ConnectSignalSlot();

private slots:
    void comboBox_currentIndexChanged(int index);

    //void on_radioButton_2_toggled(bool checked);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

private:
    QVector<QVector<BiTreeNode*>> m_tree;

    Ui::MainWindow *ui;   
    MyHeaderView *m_headerview = nullptr;

    QTreeWidgetItem* headerItem = nullptr;
    QTreeWidgetItem *topItem = nullptr;
    QTreeWidgetItem* item = nullptr;
    int m_index = 0;
    double time_all = 0;
};
