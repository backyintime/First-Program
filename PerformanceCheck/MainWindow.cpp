#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <thread>
#include "functions.h"
#include "qmath.h"

constexpr int FUNCINFO  = 0;
constexpr int ID  = 1;
constexpr int TIME  = 2;

constexpr int LEFT  = 1;
constexpr int RIGHT  = 2;

MainWindow::MainWindow(QWidget* parent)
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
    m_headerview = new MyHeaderView(2, Qt::Horizontal, this);
    ui->treeWidget->setHeader(m_headerview);
    m_index = m_headerview->m_comboBox->currentIndex();

    SetTreeWidget();
    //ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Interactive);
    //ui->treeWidget->header()->setSectionsClickable(true);
}

void MainWindow::ConnectSignalSlot()
{
    connect(m_headerview->m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBox_currentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    PerformanceCheck::Cleanup();
}


void MainWindow::comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->treeWidget->headerItem()->setText(TIME, "时间/ns");
        break;
    case 1:
        ui->treeWidget->headerItem()->setText(TIME, "时间/us");
        break;
    case 2:
        ui->treeWidget->headerItem()->setText(TIME, "时间/ms");
        break;
    case 3:
        ui->treeWidget->headerItem()->setText(TIME, "时间/s");
        break;
    case 4:
        ui->treeWidget->headerItem()->setText(TIME, "时间/min");
        break;
    }
    changeTimeUnit(m_index - index);
    m_index = index;

}

void MainWindow::SetTreeNode(BiTreeNode* node, QTreeWidgetItem* parentItem)
{
	if (!node || time_all == 0) return;

	auto* item = new QTreeWidgetItem(parentItem);
	item->setText(1, node->func_info);
	item->setText(2, QString::number(node->time));

	double percent = static_cast<double>(node->time) / static_cast<double>(time_all) * 100.0;
	item->setText(3, QString::number(percent, 'f', 2) + "%");
	for (BiTreeNode* child : node->children)
		SetTreeNode(child, item);
}

void MainWindow::SetTreeWidget()
{
	ui->treeWidget->clear();
    m_tree = PerformanceCheck::getInfoTree();

    for (int i = 0; i < m_tree.size(); ++i)
	{
        BiTreeNode* root = m_tree[i][0]; // ROOT
		if (!root || root->children.isEmpty()) continue;

		auto* topItem = new QTreeWidgetItem(ui->treeWidget);
		topItem->setText(0, root->func_info);

		BiTreeNode* entryPoint = root->children.first(); // 原来是 leftChild
		time_all = entryPoint->time;
		topItem->setText(2, QString::number(time_all));
		topItem->setText(3, "100.00%");

		for (BiTreeNode* child : root->children)
		{
			SetTreeNode(child, topItem);
		}
	}
}

void MainWindow::changeTimeUnit(int multiple)
{
	const double factor = qPow(10.0, multiple * 3);
	QTreeWidgetItemIterator it(ui->treeWidget);
	while (*it)
	{
		bool ok = false;
		double original = (*it)->text(TIME).toDouble(&ok);
		if (ok)
		{
			(*it)->setText(TIME, QString::number(original * factor, 'f', 2));
		}
		++it;
	}
}


void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint& pos)
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

