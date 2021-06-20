#include "Teacher.h"

Teacher::Teacher(QString name, int sex, int age, QString id, int salary)
{
    SetInfo(name, sex, age);
    m_salary = salary;
    m_teaNum = id;
}

QString Teacher::GetTeaNum()
{
    return m_teaNum;
}

int Teacher::GetSalary()
{
    return m_salary;
}

QString Teacher::GetInfo()
{
    QString teaInfo = QString("%1 %2 %3 ").arg(Person::GetInfo()).arg(m_teaNum).arg(m_salary);
    return  teaInfo;
}
