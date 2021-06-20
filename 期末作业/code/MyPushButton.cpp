#include "MyPushButton.h"

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    normalImg_path = normalImg;
    pressImg_path = pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    setFixedSize(150,100);
    //设置不规则图片的样式
    setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    setIcon(pix);
    //设置图标大小
    setIconSize(QSize(50,100));
}
