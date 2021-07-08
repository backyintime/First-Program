#pragma once

#include <QWidget>
#include<QScrollArea>
#include<QScrollBar>
#include<QMouseEvent>

class ScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea();
    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件
    void mousePressEvent(QMouseEvent *);//鼠标按下事件

    bool mousePressed;             //鼠标按下标志
    QPoint pressPos;               //鼠标按下位置

signals:

};

