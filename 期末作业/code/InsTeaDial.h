#ifndef INSTEADIAL_H
#define INSTEADIAL_H

#include <QWidget>
#include"School.h"

class InsTeaDial : public QWidget
{
    Q_OBJECT
public:
    explicit InsTeaDial(School *sch);
    ~InsTeaDial();

signals:

};

#endif // INSTEADIAL_H
