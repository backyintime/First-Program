#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include"Headers.h"

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImg,QString pressImg = "");
    QString normalImg_path;
    QString pressImg_path;

//    //弹跳特效
//    void zoom();
//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);

signals:

};

#endif // MYPUSHBUTTON_H
