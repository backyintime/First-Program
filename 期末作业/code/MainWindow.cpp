#include "MainWindow.h"
#include "ui_MainWindow.h"
#include"MyPushButton.h"
#include"Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QPixmap(":/Main.png"));
    setWindowTitle("学校");
    setFixedSize(245,360);  //设置固定大小

    QLabel *label = new QLabel("学校信息管理",this);
    label->move(20,60);
    label->setWindowIcon(QPixmap(":school.png"));
    QFont font;
    font.setFamily("华文彩云");
    font.setPointSize(20);
    label->setFont(font);

    QPushButton *stuBtn = new MyPushButton(":/stu.png");
    QPushButton *teaBtn = new MyPushButton(":/tea.png");
    stuBtn->setParent(this);
    teaBtn->setParent(this);
    stuBtn->setText("学生");
    teaBtn->setText("教师");
    font.setFamily("华文行楷");
    font.setPointSize(10);
    stuBtn->setFont(font);
    teaBtn->setFont(font);
    stuBtn->move(50,100);
    teaBtn->move(50,150);

    //数据处理
    School *sch = new School;
    if(!sch->CreateTab())   //创建表格
        return;
    sch->ReadDB();        //从数据库中读取

    //切换窗口
    stuScene = new StuScene(sch);
    teaScene = new TeaScene(sch);
    connect(stuBtn,&QPushButton::clicked,[=]()  //切换至学生场景
    {
        this->hide();
        delay(300);
        stuScene->show();
    });
    connect(teaBtn,&QPushButton::clicked,[=]()  //切换至教师场景
    {
        this->hide();
        delay(300);
        teaScene->show();
    });

    //监听返回信息,返回至主场景
    connect(stuScene,&StuScene::clickedBack,[=]()
    {
        stuScene->hide();
        delay(300);
        this->show();
    });
    connect(teaScene,&TeaScene::clickedBack,[=]()
    {
        teaScene->hide();
        delay(300);
        this->show();
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //加载图片
    QPixmap pix = QPixmap(":/bg_1.png").scaled(this->size());
    painter.drawPixmap(0,0,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

