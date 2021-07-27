#pragma once

#include <QHeaderView>
#include<QComboBox>
#include<QLabel>

class MyHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    MyHeaderView(int combColumnIndex,
                 Qt::Orientation orientation,
                 QWidget *parent = nullptr);
    ~MyHeaderView();

    QComboBox* m_comboBox;
    QLabel *label;
private:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

private:
    int m_comboBoxColumnIndex = -1;

signals:

};

