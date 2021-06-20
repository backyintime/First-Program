#include "InsTeaDial.h"

InsTeaDial::InsTeaDial(School *sch)
{
    QDialog *dia = new QDialog;
    dia->setWindowTitle("插入信息");
    dia->setWindowIcon(QPixmap(":/Insert.png"));
    dia->setFixedSize(300,300);

    QLabel *Name = new QLabel("姓名",dia);
    QLabel *Id = new QLabel("工号",dia);
    QLabel *Age = new QLabel("年龄",dia);
    QLabel *salary = new QLabel("工资",dia);

    Name->move(20,24);
    Id->move(20,64);
    Age->move(20,184);
    salary->move(20,104);

    QLineEdit *edit_1 = new QLineEdit(dia);
    QLineEdit *edit_2 = new QLineEdit(dia);
    QLineEdit *edit_3 = new QLineEdit(dia);
    edit_1->setPlaceholderText("请输入姓名");
    edit_2->setPlaceholderText("请输入学号");
    edit_3->setPlaceholderText("请输入工资");
    edit_1->move(55,20);
    edit_2->move(55,60);
    edit_3->move(55,100);

    QRadioButton *man = new QRadioButton("男", dia);
    QRadioButton *woman = new QRadioButton("女", dia);
    man->move(55,140);
    woman->move(115,140);
    man->setChecked(true);

    QSpinBox *sel_age = new QSpinBox(dia);
    sel_age->move(55,180);

    sel_age->setValue(25);

    QPushButton *y_btn = new QPushButton("确定", dia);
    QPushButton *n_btn = new QPushButton("取消", dia);
    y_btn->move(40,240);
    n_btn->move(150,240);

    //样式修改
    dia->setStyleSheet("QDialog{background-image:url(:/bg_3.png)}"
                       "QPushButton{background-image:url(:/bg_6.png)}"
                       "QLineEdit{background-image:url(:/bg_7.png)}"
                       "QSpinBox{background-color:rgb(230,210,180)}");

    //点击确定
    connect(y_btn,&QPushButton::clicked,[=]()
    {
        //工号，姓名不为空
        if(!edit_1->text().isEmpty()&&!edit_2->text().isEmpty())
        {
            Teacher *Tea = new Teacher(edit_1->text(),
                                       man->isChecked()?0:1,
                                       sel_age->value(),
                                       edit_2->text(),
                                       edit_3->text().toInt());
            if(sch->InsertTeacher(*Tea))//工号不重复时，将stu对象存入stu容器中
            {
                if(sch->db.open())
                {
                    sch->InsertTeaTable(*Tea);
                    QMessageBox::information(dia,("😀"),"插入成功");
                }
            }
            else
            {
                QMessageBox::warning(dia,("🙁"),("学号重复"));
            }
        }
        else
        {
            QMessageBox::warning(dia,("🙁"),("姓名或学号不能为空"));
        }
    });

    //点击取消
    connect(n_btn,&QPushButton::clicked,[=]()
    {
        dia->close();
        sch->db.close();
        delete dia;
    });
    dia->exec();
}

InsTeaDial::~InsTeaDial()
{
    delete this;
}
