#ifndef STUDENTSCENE_H
#define STUDENTSCENE_H

#include <QWidget>
#include"School.h"
#include"Headers.h"
#include"InsStuDial.h"
#include"DelStuDial.h"

class StuScene : public QWidget
{
    Q_OBJECT
public:
    explicit StuScene(School *sch,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    InsStuDial *insDialog;
    DelStuDial *delDialog;
signals:
    void clickedBack();
};

#endif // STUDENTSCENE_H
