#include "Person.h"

void Person::SetInfo(QString name, int sex, int age)
{
    m_name = name;
    m_sex = (enum Sex)sex;
    m_age = age;
}

QString Person::GetInfo()
{
    QString perInfo = QString("%1 %2 %3").arg(m_name).arg(m_sex).arg(m_age);
    return perInfo;
}
