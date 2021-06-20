#ifndef SCHOOL_H
#define SCHOOL_H

#include"Student.h"
#include"Teacher.h"
#include"Headers.h"
#include<QVector>
#include<QString>

class School
{
public:
    QVector<Student *> stu;             //学生对象vector
    QVector<Teacher *> tea;             //教师对象vector

    QSqlDatabase db;                    //数据库对象
    bool CreateTab();                   //创建student表，teacher表
    bool IsTableExist(QSqlQuery &query,QString table);//判断表格是否被创建
    bool InsertStuTable(Student &stu);  //将数据插入表
    bool InsertTeaTable(Teacher &tea);
    bool SaveInDB();                    //将vector中的数据保存到数据库中
    bool ReadDB();                      //从数据库中读取数据，存入vector中

    int IndexStu(QString &num);         //根据学号查找学生
    int IndexTea(QString& num);         //根据工号查找教师
    bool InsertStudent(Student& stu);   //添加学生
    bool InsertTeacher(Teacher& tea);   //添加教师
    bool DelStudent(QString& stuNum);   //删除学生
    bool DelTeacher(QString& teaNum);   //删除教师
    int GetTotalSalarys();              //获取教师的总工资
    int GetStudentsAverageTotalScore(); //获取学生的平均成绩
    Student* GetStudentByStuNum(QString& stuNum);   //获取学生信息
    Teacher* GetTeacherByTeaNum(QString& teaNum);   //获取教师信息
};

#endif // SCHOOL_H
