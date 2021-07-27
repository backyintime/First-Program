#include "MyHeaderView.h"

MyHeaderView::MyHeaderView(int combColumnIndex, Qt::Orientation orientation, QWidget *parent)
    :QHeaderView(orientation,parent)
{
    m_comboBoxColumnIndex = combColumnIndex;
    m_comboBox = new QComboBox(this);
    label = new QLabel(this);
    m_comboBox->setStyleSheet(("background-color:rgb(245, 250, 250)"));
    setDefaultAlignment(Qt::AlignLeft);
    //setSectionsClickable(true);
    m_comboBox->addItems(QStringList()<<"时间/ns"<<"时间/us"<<"时间/ms"<<"时间/s"<<"时间/min");
    //connect(m_comboBox, &, parent, SLOT(HeadViewCheckStateChanged(int)));

}

MyHeaderView::~MyHeaderView()
{

}

void MyHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if(m_comboBoxColumnIndex == logicalIndex)
    {
        m_comboBox->setGeometry(rect);
    }
//    else if(logicalIndex == 3)
//    {
//        label->setText("d");
//        label->setGeometry(rect);
//    }
    else
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }
}

