#include "DelTeaDial.h"

DelTeaDial::DelTeaDial(School *sch)
{
    QDialog *del_dia = new QDialog;
    del_dia->setFixedSize(240,160);
    del_dia->setWindowIcon(QPixmap(":/delete.png"));

    QLabel *label = new QLabel("输入工号",del_dia);
    label->move(85,20);

    QLineEdit *edit = new QLineEdit(del_dia);
    edit->setPlaceholderText("请输入工号");
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
            if(sch->DelTeacher(id)) //从tea容器中删除成功
            {
                qDebug()<<"!";
                if(sch->db.open())
                {
                    QSqlQuery sql;
                    sql.exec("delete from teacher where id = '"+id+"'");    //从数据库中删除
                    QMessageBox::information(del_dia,("😀"),("删除成功"));
                }
                else
                {
                    qDebug()<<"2";
                }
            }
            else
            {
                QMessageBox::information(del_dia,("🙁"),("当前教师不存在"));
            }
        }
        else
        {
            QMessageBox::information(del_dia,("🙁"),("工号不能为空"));
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
