#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include<QString>

class Teacher : public Person
{
public:
    Teacher(QString name, int sex, int age, QString id,int salary);
    QString GetTeaNum(); //获取老师工号
    int GetSalary();     //获取老师工资
    QString GetInfo();   //获取老师的信息，将老师的姓名、性别、年龄、工号、工资
private:
    QString m_teaNum;    //工号
    int   m_salary;      //工资
};

#endif // TEACHER_H
