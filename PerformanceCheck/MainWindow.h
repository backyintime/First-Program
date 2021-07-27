#pragma once

#include"Headers.h"
#include"MyHeaderView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
    QVector<QVector<BiTreeNode*>> *v;

    Ui::MainWindow *ui;   
    MyHeaderView *myheaderview;

    QTreeWidgetItem* headerItem;
    QTreeWidgetItem *topItem;
    QTreeWidgetItem* item;
    int m_index;
    double time_all;
};
