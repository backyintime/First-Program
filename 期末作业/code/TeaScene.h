#ifndef TEACHERSCENE_H
#define TEACHERSCENE_H

#include <QWidget>
#include"Headers.h"
#include"School.h"
#include"InsTeaDial.h"
#include"DelTeaDial.h"

class TeaScene : public QWidget
{
    Q_OBJECT
public:
    explicit TeaScene(School *sch,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    InsTeaDial *insDialog;
    DelTeaDial *delDialog;
signals:
    void clickedBack();
};

#endif // TEACHERSCENE_H
