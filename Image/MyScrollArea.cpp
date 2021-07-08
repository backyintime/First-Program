#include "MyScrollArea.h"
#include<QDebug>

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{

}

ScrollArea::~ScrollArea()
{

}

void ScrollArea::mouseMoveEvent(QMouseEvent *e)
{
    if(!mousePressed)
        return;
    QPoint currentPt = e->pos();
    int dist_y = pressPos.y() - currentPt.y();
    int dist_x = pressPos.x() - currentPt.x();
    verticalScrollBar()->setValue(verticalScrollBar()->value()+dist_y);
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()+dist_x);
    pressPos = currentPt;
}

void ScrollArea::mousePressEvent(QMouseEvent *e)
{
        mousePressed = true;
        pressPos = e->pos();
}
