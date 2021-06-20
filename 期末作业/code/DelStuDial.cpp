#include "DelStuDial.h"

DelStuDial::DelStuDial(School *sch)
{
    QDialog *del_dia = new QDialog;
    del_dia->setFixedSize(240,160);
    del_dia->setWindowIcon(QPixmap(":/delete.png"));

    QLabel *label = new QLabel("输入学号",del_dia);
    label->move(85,20);

    QLineEdit *edit = new QLineEdit(del_dia);
    edit->setPlaceholderText("请输入学号");
    edit->move(35,50);

    QPushButton *y_btn = new QPushButton("确定",del_dia);
    QPushButton *n_btn = new QPushButton("取消",del_dia);
    y_btn->resize(60,30);
    n_btn->resize(60,30);
    y_btn->move(40,120);
    n_btn->move(140,120);

    //样式修改
    del_dia->setStyleSheet("QDialog{background-image:url(:/bg_3.png)}"
                       "QPushButton{background-image:url(:/bg_6.png)}"
                       "QLineEdit{background-image:url(:/bg_7.png)}"
                       "QSpinBox{background-color:rgb(230,210,180)}");

    //点击确定，执行删除
    connect(y_btn,&QPushButton::clicked,[=]()
    {
        QString id = edit->text();
        if(!id.isEmpty())
        {
            if(sch->DelStudent(id)) //从stu容器中删除成功
            {
                if(sch->db.open())
                {
                    QSqlQuery sql;
                    sql.exec("delete from student where id = '"+id+"'");    //从数据库中删除
                    QMessageBox::information(del_dia,("😀"),("删除成功"));
                }
            }
            else
            {
                QMessageBox::information(del_dia,("🙁"),("当前学生不存在"));
            }
        }
        else
        {
            QMessageBox::information(del_dia,("🙁"),("学号不能为空"));
        }
    });

    //点击取消
    connect(n_btn,&QPushButton::clicked,[=]()
    {
        del_dia->close();
        sch->db.close();
        delete del_dia;
    });
    del_dia->exec();
}
