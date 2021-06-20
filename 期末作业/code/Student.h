#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include"Score.h"

class Student : public Person
{
public:
    Student(QString name, int sex, int age, QString id,int Chinese=0, int math=0);
    QString GetStuNum();//获取学生学号
    int GetTotalScore();//获取总成绩
    QString GetInfo();//获取学生的姓名、性别、年龄、学号、总成绩，以空格分开

private:
    QString m_stuNum;//学号
    Score   m_score;//成绩
};

#endif // STUDENT_H
