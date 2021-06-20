#include "InsStuDial.h"

InsStuDial::InsStuDial(School *sch)
{
    QDialog *dia = new QDialog;
    dia->setWindowTitle("插入信息");
    dia->setWindowIcon(QPixmap(":/Insert.png"));
    dia->setFixedSize(300,300);

    QLabel *Name = new QLabel("姓名",dia);
    QLabel *Id = new QLabel("学号",dia);
    QLabel *Age = new QLabel("年龄",dia);
    QLabel *chinese = new QLabel("语文成绩",dia);
    QLabel *math = new QLabel("数学成绩",dia);

    Name->move(20,24);
    Id->move(20,64);
    Age->move(20,144);
    chinese->move(20,184);
    math->move(144,184);

    QLineEdit *edit_1 = new QLineEdit(dia);
    QLineEdit *edit_2 = new QLineEdit(dia);
    edit_1->setPlaceholderText("请输入姓名");
    edit_2->setPlaceholderText("请输入学号");
    edit_1->move(55,20);
    edit_2->move(55,60);

    QRadioButton *man = new QRadioButton("男", dia);
    QRadioButton *woman = new QRadioButton("女", dia);
    man->move(55,100);
    woman->move(115,100);
    man->setChecked(true);

    QSpinBox *sel_age = new QSpinBox(dia);
    QSpinBox *sel_ch = new QSpinBox(dia);
    QSpinBox *sel_ma = new QSpinBox(dia);
    sel_age->move(55,140);
    sel_ch->move(83,180);
    sel_ma->move(207,180);

    sel_age->setValue(18);
    sel_ch->setValue(70);
    sel_ma->setValue(70);

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
        //学号，姓名不为空
        if(!edit_1->text().isEmpty()&&!edit_2->text().isEmpty())
        {
            Student *Stu = new Student(edit_1->text(),
                                       man->isChecked()?0:1,
                                       sel_age->value(),
                                       edit_2->text(),
                                       sel_ch->value(),
                                       sel_ma->value());
            if(sch->InsertStudent(*Stu))//学号不重复时，将stu对象存入stu容器中
            {
                if(sch->db.open())
                {
                    sch->InsertStuTable(*Stu);
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

InsStuDial::~InsStuDial()
{
    delete this;
}
