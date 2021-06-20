#include "TeaScene.h"

TeaScene::TeaScene(School *sch,QWidget *parent) : QWidget(parent)
{
    //界面搭建
    setFixedSize(560,360);
    setWindowTitle("教师信息");
    setWindowIcon(QPixmap(":/tea.png"));

    //下拉框 查询方式
    QComboBox *select = new QComboBox(this);
    QStringList list = {"按工号查询","按姓名查询"};
    select->addItems(list);
    select->resize(120,26);
    select->move(25,32);

    //输入框
    QLineEdit *edit = new QLineEdit(this);
    edit->resize(315,30);
    edit->move(150,30);
    edit->setPlaceholderText("请输入查询信息");

    //查询
    QPushButton *sel_btn = new QPushButton("查询",this);
    QPushButton *ins_btn = new QPushButton("插入信息",this);
    QPushButton *show_btn = new QPushButton("显示信息",this);
    QPushButton *del_btn = new QPushButton("删除信息",this);
    QPushButton *back_btn = new QPushButton("返回",this);

    sel_btn->resize(75,28);
    ins_btn->resize(100,30);
    show_btn->resize(100,30);
    del_btn->resize(100,30);
    back_btn->resize(75,28);

    sel_btn->move(width() - sel_btn->width()-5,31);
    ins_btn->move(25,325);
    show_btn->move(150,325);
    del_btn->move(275,325);
    back_btn->move(width() - back_btn->width()-5,height() - back_btn->height()-5);

    //浏览视图
    QTableView *view = new QTableView(this);
    view->setGeometry(20,70,450,220);

    QSqlQueryModel *model = new QSqlQueryModel();//引入模型

    //样式修改
    this->setStyleSheet("QPushButton{background-image:url(:/bg_6.png)}"
                        "QLineEdit{background-image:url(:/bg_7.png)}"
                        "QComboBox{background-image:url(:/bg_6.png)}"
                        "QTableView{background-image:url(:/bg_7.png)}"
                        "QHeaderView::section{background-image:url(:/bg_7.png);border: 1px}"
                        "QTableCornerButton::section{background-color:rgb(230,230,230)}");

    //点击插入教师信息
    connect(ins_btn,&QPushButton::clicked,[=]()
    {
        insDialog = new InsTeaDial(sch);
    });

    //点击显示教师信息
    connect(show_btn,&QPushButton::clicked,[=]()
    {
        sch->ReadDB();
        if(sch->db.open())
        {
            //通过模型将数据库导出到 TableView上
            model->setQuery("select * from teacher", sch->db);
            /*  ---设置表头---   */
            model->setHeaderData(0,Qt::Horizontal,"工号");
            model->setHeaderData(1,Qt::Horizontal,"姓名");
            model->setHeaderData(2,Qt::Horizontal,"性别");
            model->setHeaderData(3,Qt::Horizontal,"年龄");
            model->setHeaderData(4,Qt::Horizontal,"工资");
            view->setModel(model);  //设置为model模型
            //修改列宽
            view->setColumnWidth(0,WIDTH);
            view->setColumnWidth(1,WIDTH);
            view->setColumnWidth(2,WIDTH);
            view->setColumnWidth(3,WIDTH);
            view->setColumnWidth(4,WIDTH);
            sch->db.close();
        }
    });

    //点击查询
    connect(sel_btn,&QPushButton::clicked,[=]()
    {
        if(sch->db.open())
        {
            QSqlQuery sql;
            if(select->currentIndex() == 0)//按工号方式进行查询
            {
                if(!edit->text().isEmpty())//输入框有键入
                {
                    bool is_exec = sql.exec("select *from teacher where id = '"+edit->text()+"'");
                    if(!is_exec)
                    {
                        qDebug()<<"查询失败"<<sql.lastError();
                    }
                    else
                    {
                        model->setQuery(sql);
                        view->setModel(model);
                    }
                }
                else
                {
                    QMessageBox::warning(this,("🙁"),"请输入查询信息！");
                }
            }
            else if(select->currentIndex() == 1)//按姓名方式进行查询
            {
                if(!edit->text().isEmpty())//输入框有键入
                {
                    bool is_exec = sql.exec("select *from teacher where name = '"+edit->text()+"'");
                    if(!is_exec)
                    {
                        qDebug()<<"查询失败"<<sql.lastError();
                    }
                    else
                    {
                        model->setQuery(sql);
                        view->setModel(model);
                    }
                }
                else
                {
                    QMessageBox::warning(this,("🙁"),"请输入查询信息！");
                }
            }
            sch->db.close();
        }
    });

    //点击删除
    connect(del_btn,&QPushButton::clicked,[=]()
    {
        delDialog = new DelTeaDial(sch);
    });

    //点击返回
    connect(back_btn,&QPushButton::clicked,[=]()
    {
        emit clickedBack();
    });
}

void TeaScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //加载图片
    QPixmap pix = QPixmap(":/bg_2.png").scaled(this->size());
    painter.drawPixmap(0,0,pix);
}
