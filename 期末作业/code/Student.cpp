#include "Student.h"

Student::Student(QString name, int sex, int age, QString id, int Chinese, int math)
{
    SetInfo(name, sex, age);
    m_stuNum = id;
    m_score.SetScore(Chinese,math);
}

QString Student::GetStuNum()
{
    return m_stuNum;
}

int Student::GetTotalScore()
{
    return m_score.GetScore();
}

QString Student::GetInfo()
{
    QString stuInfo = QString("%1 %2 %3").arg(Person::GetInfo()).arg(m_stuNum).arg(m_score.GetScore());
    return  stuInfo;
}
