#pragma once

#include<QWidget>
#include"Headers.h"
//#include"MyWidget.h"
#include"MyScrollArea.h"

class Image : public QWidget
{
    Q_OBJECT

private:
    QMenuBar *menubar;   //菜单栏
    QMenu *menu;         //菜单项
    QAction *openFile;   //打开文件选项
    QAction *openFolder; //打开文件夹选项

    QScrollArea *right_scrollArea;  //主滚动区

    QPushButton *enlargeBtn;        //放大按钮
    QPushButton *restoreBtn;        //还原按钮
    QPushButton *narrowBtn;         //缩小按钮

    QWidget *right_widget;          //右侧widget

    QGridLayout *center_layout;     //中心布局
    QVBoxLayout *right_layout;      //右侧布局
    QHBoxLayout *btn_layout;        //按钮布局
    QVBoxLayout *v_layout;          //垂直布局
    QSplitter *splitter;            //切分窗口

    QLabel label_image;             //图片展示
    QPixmap origin_pix;             //原始图片
    QPixmap new_pix;                //加载图片

    QLabel *label_text;             //文本提示

    QListWidget *imageList;         //图表
    QList<QFileInfo> *fileinfo;     //文件信息表


//    QLabel *text_label;
//    QStringList m_filename;
//    QStringList _m_filename;
private:
    void initUi();                  //初始化界面信息
    void connect_Signal_Slot();     //连接信号和槽
private:
//    bool mousePressed;             //鼠标按下标志
//    QPoint pressPos;               //鼠标按下位置

public:
//    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件
//    void mousePressEvent(QMouseEvent *);//鼠标按下事件

public:
    Image(QWidget *parent = nullptr);
    void OpenPix(const QString &path);  //双击缩略图打开
    void loadPix(int i);
    ~Image();

signals:
    void OpenFile_Clicked();    //点击 打开文件
    void OpenFolder_Clicked();  //点击 打开文件夹
    void Enlarge_Clicked();     //点击 放大
    void Restore_Clicked();     //点击 还原
    void Narrow_Clicked();      //点击 缩小
    void Item_DoubleClicked();  //双击 缩略图

public slots:
    void OpenFile();            //打开文件
    void OpenFolder();          //打开文件夹
    void Enlarge();             //放大
    void Restore();             //还原
    void Narrow();              //缩小
    void Image_Selected();      //图片选中
    void ScrollBar_moved(int v);

};
