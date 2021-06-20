#include "School.h"

bool School::CreateTab()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("School.db");
    //打开数据库
    if(!db.open())  //打开失败
    {
        qDebug()<<"Error:failed to connect"<<db.lastError();
        return false;
    }
    else
    {
        QSqlQuery sql(db);
        //创建student table
        QString stuTab = "create table if not exists student (id int primary key, name varchar(30),sex int,age int,score int)";
        sql.prepare(stuTab);
        if(!sql.exec())
        {
            qDebug() << "Error: Fail to create student table." << sql.lastError();
            return false;
        }
        else
        {
            qDebug() << "Student table created!";
        }
        //创建teacher table
        QString teaTab = "create table if not exists teacher (id int primary key, name varchar(30),sex int,age int,salary int)";
        sql.prepare(teaTab);
        if(!sql.exec())
        {
            qDebug() << "Error: Fail to create teacher table." << sql.lastError();
            return false;
        }
        else
        {
            qDebug() << "Teacher table created!";
        }
    }
    db.close();
    return true;
}

bool School::IsTableExist(QSqlQuery &query, QString table)
{
    QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
    query.exec(sql);
    return query.next();
}

bool School::InsertStuTable(Student &stu)
{
    QStringList List = stu.GetInfo().split(" ");   //获取学生信息,将信息进行分割，存入List中
    /*List[0] 姓名
     *List[1] 性别
     *List[2] 年龄
     *List[3] 学号
     *List[4] 分数                */

    /*student表
     *学号 姓名 性别 年龄 分数       */
    QSqlQuery sql;
    bool is_exec = sql.exec("insert into student values('"+List[3]+"','"+List[0]+"','"+List[1]+"','"+List[2]+"','"+List[4]+"')");
    if(!is_exec)
    {
        qDebug() << "Error: Fail to insert student info." << sql.lastError();
        return false;
    }
    else
    {
        qDebug() << "Insert student info succeed!";
        return true;
    }
}

bool School::InsertTeaTable(Teacher &tea)
{
    QStringList List = tea.GetInfo().split(" ");   //获取教师信息,将信息进行分割，存入List中
    /*List[0] 姓名
     *List[1] 性别
     *List[2] 年龄
     *List[3] 工号
     *List[4] 工资                */

    /*teacher表
     *工号 姓名 性别 年龄 工资       */
    QSqlQuery sql;
    bool is_exec = sql.exec("insert into teacher values('"+List[3]+"','"+List[0]+"','"+List[1]+"','"+List[2]+"','"+List[4]+"')");
    if(!is_exec)
    {
        qDebug() << "Error: Fail to insert teacher info." << sql.lastError();
        return false;
    }
    else
    {
        qDebug() << "Insert teacher info succeed!";
        return true;
    }
}

bool School::ReadDB()
{
    //打开数据库
    if(!db.open())
    {
        qDebug()<<"Error:failed to connect"<<db.lastError();
        return false;
    }
    else
    {
        QVector<Student *> vec;
        stu.swap(vec);
        QSqlQuery sql(db);
        sql.prepare("select *from student");
        if(!sql.exec())
        {
            qDebug()<<"Failed to read";
            return false;
        }
        else
        {
            while(sql.next())
            {
                //从数据库中读取数据来新建Stu对象，存入stu容器中
                Student *Stu = new Student(sql.value("name").toString(),
                                           sql.value("sex").toInt(),
                                           sql.value("age").toInt(),
                                           sql.value("id").toString(),
                                           sql.value("score").toInt());
                this->stu.push_back(Stu);
            }
        }
        QVector<Teacher *> vect;
        tea.swap(vect);
        sql.prepare("select *from teacher");
        if(!sql.exec())
        {
            qDebug()<<"Failed to read";
            return false;
        }
        else
        {
            while(sql.next())
            {
                Teacher *Tea = new Teacher(sql.value("name").toString(),
                                           sql.value("sex").toInt(),
                                           sql.value("age").toInt(),
                                           sql.value("id").toString(),
                                           sql.value("salary").toInt());
                this->tea.push_back(Tea);
            }
        }


    }
    qDebug()<<"Read successfully";
    db.close();
    return true;
}

int School::IndexStu(QString& num)
{
    for (int i = 0; i < stu.size(); i++)
    {
        if (stu[i]->GetStuNum() == num)
            return i;
    }
    return -1;
}

int School::IndexTea(QString& num)
{
    for (int i = 0; i < tea.size(); i++)
    {
        if (tea[i]->GetTeaNum() == num)
            return i;
    }
    return -1;
}

bool School::InsertStudent(Student& stu)
{
    QString num = stu.GetStuNum();
    if (GetStudentByStuNum(num) == nullptr)
    {
        this->stu.push_back(&stu);
        return true;
    }
    return false;
}

bool School::InsertTeacher(Teacher& tea)
{
    QString num = tea.GetTeaNum();
    if (GetTeacherByTeaNum(num) == nullptr)
    {
        this->tea.push_back(&tea);
        return true;
    }
    return false;
}

bool School::DelStudent(QString& stuNum)
{
    int index = IndexStu(stuNum);
    if (index != -1)
    {
        stu.erase(stu.begin()+index);
        return true;
    }
    return false;
}

bool School::DelTeacher(QString& teaNum)
{
    int index = IndexTea(teaNum);
    if (index != -1)
    {
        tea.erase(tea.begin() + index);
        return true;
    }
    return false;
}

int School::GetTotalSalarys()
{
    int sum = 0;
    for (int i = 0; i < tea.size(); i++)
    {
        sum += tea[i]->GetSalary();
    }
    return sum;
}

int School::GetStudentsAverageTotalScore()
{
    int sum = 0;
    for (int i = 0; i < stu.size(); i++)
    {
        sum += stu[i]->GetTotalScore();
    }
    return sum / stu.size();
}

Student* School::GetStudentByStuNum(QString& stuNum)
{
    int index = IndexStu(stuNum);
    if (index == -1)
        return nullptr;
    return stu[index];

}

Teacher* School::GetTeacherByTeaNum(QString& teaNum)
{
    int index = IndexTea(teaNum);
    if (index == -1)
        return nullptr;
    return tea[index];
}




