#ifndef INSSTUDIAL_H
#define INSSTUDIAL_H

#include"Headers.h"
#include"School.h"
#include"Student.h"

class InsStuDial:public QWidget
{
    Q_OBJECT
public:
    InsStuDial(School *sch);
    ~InsStuDial();

signals:
};

#endif // INSSTUDIAL_H
