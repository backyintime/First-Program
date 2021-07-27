#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    /*---------------------test--------------------------*
    */std::thread thr_1(test);                          /*
    */thr_1.join();                                     /*
    */std::thread thr_2(func_2);                        /*
    */thr_2.join();                                     /*
    *---------------------------------------------------*/
    InitUi();
    ConnectSignalSlot();

}

void MainWindow::InitUi()
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(4);
    myheaderview = new MyHeaderView(2,Qt::Horizontal,this);
    ui->treeWidget->setHeader(myheaderview);
    m_index = myheaderview->m_comboBox->currentIndex();

    SetTreeWidget();
    //ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Interactive);
    //ui->treeWidget->header()->setSectionsClickable(true);
}

void MainWindow::ConnectSignalSlot()
{
    connect(myheaderview->m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBox_currentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    PerformanceCheck::DelVector();
}


void MainWindow::comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->treeWidget->headerItem()->setText(TIME,"时间/ns");
        break;
    case 1:
        ui->treeWidget->headerItem()->setText(TIME,"时间/us");
        break;
    case 2:
        ui->treeWidget->headerItem()->setText(TIME,"时间/ms");
        break;
    case 3:
        ui->treeWidget->headerItem()->setText(TIME,"时间/s");
        break;
    case 4:
        ui->treeWidget->headerItem()->setText(TIME,"时间/min");
        break;
    }
    changeTimeUnit(m_index - index);
    m_index = index;

}

void MainWindow::SetTreeNode(BiTreeNode *node,QTreeWidgetItem* parentItem)
{
    if(node!=nullptr)
    {
        item = new QTreeWidgetItem;
        item->setText(1,*node->func_info);
        item->setText(2,QString::number(node->time));
        item->setText(3,QString::number(node->time/time_all*100) + "%");
        parentItem->addChild(item);
        SetTreeNode(node->leftChild,item);
        SetTreeNode(node->rightChild,parentItem);
    }
}

void MainWindow::SetTreeWidget()
{
    v = PerformanceCheck::GetRoot();
    for (int i = 0; i < v->size(); ++i)
    {
        BiTreeNode* root = (*v)[i][ROOT];
        if(root!=nullptr)
        {
            topItem =  new QTreeWidgetItem(ui->treeWidget);
            if(root->leftChild!=nullptr)
            {
                topItem->setText(0,*root->func_info);

                time_all = root->leftChild->time;

                topItem->setText(TIME,QString::number(time_all));
                //topItem->setText(4,QString::number(root->leftChild->time/root->time));
            }

            SetTreeNode(root->leftChild,topItem);
            SetTreeNode(root->rightChild,topItem);
        }
    }
}

void MainWindow::changeTimeUnit(int multiple)
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
        (*it)->setText(TIME,QString::number((*it)->text(TIME).toDouble()*qPow(10,multiple*3)));
        ++it;
    }
}


void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
//    QTreeWidgetItem* curItem=ui->treeWidget->itemAt(pos);  //获取当前被点击的节点
//       if(curItem==NULL)return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
//       QVariant var = curItem->data(0,Qt::UserRole);
//       if(0 == var)      //data(...)返回的data已经在之前建立节点时用setdata()设置好
//       {
//          QMenu *popMenu =new QMenu(this);//定义一个右键弹出菜单

//          popMenu->addAction(ui-);//往菜单内添加QAction   该action在前面用设计器定义了
//          popMenu->addAction(ui->action_openDB);
//          popMenu->addAction(ui->action_delDB);
//          popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
//       }
//       else
//       {
//           QMenu *popMenu =new QMenu(this);//定义一个右键弹出菜单

//           popMenu->addAction(ui->action_newTable);//往菜单内添加QAction   该action在前面用设计器定义了
//           popMenu->addAction(ui->action_openTable);
//           popMenu->addAction(ui->action_designTable);
//           popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
//       }
}

