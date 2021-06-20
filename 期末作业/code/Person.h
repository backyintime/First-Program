#ifndef PERSON_H
#define PERSON_H
#include<QString>

class Person
{
private:
    enum Sex
    {
        Male,
        Female
    }m_sex;          //性别
    QString m_name;  //姓名
    int m_age;       //年龄
public:
    virtual void SetInfo(QString name, int sex, int age); //设置信息
    virtual QString GetInfo();   //获取信息
};

#endif // PERSON_H
