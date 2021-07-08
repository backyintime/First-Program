#include "Image.h"

void Image::initUi()
{
    //设置菜单栏
    menubar = new QMenuBar(this);
    menu = new QMenu("菜单(&F)",this);
    openFile = new QAction("打开文件",this);
    openFolder = new QAction("打开文件夹",this);

    //设置缩略图显示区
    imageList = new QListWidget(this);

    //设置图片显示区
    right_scrollArea = new ScrollArea(this);
    right_widget = new QWidget(this);
    label_text = new QLabel("图片查看区域",this);

    //设置按钮
    enlargeBtn = new QPushButton("放大",this);
    restoreBtn = new QPushButton("还原",this);
    narrowBtn = new QPushButton("缩小",this);

    //设置布局
    center_layout = new QGridLayout();
    btn_layout = new QHBoxLayout();
    right_layout = new QVBoxLayout();
    splitter = new QSplitter();

    //按钮组件布局
    btn_layout->addWidget(enlargeBtn);
    btn_layout->addWidget(restoreBtn);
    btn_layout->addWidget(narrowBtn);

    //右侧区域布局
    right_layout->addWidget(right_scrollArea);
    right_layout->addLayout(btn_layout);
    right_layout->setContentsMargins( 2, 0, 1, 2);
    right_widget->setLayout(right_layout);

    splitter->addWidget(imageList);
    splitter->addWidget(right_widget);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,3);
    splitter->setChildrenCollapsible(false);

    center_layout->addWidget(menubar, 0, 0, 1, 2,Qt::AlignTop);
    center_layout->addWidget(splitter,1, 0, 45, 2);
    center_layout->setContentsMargins( 2, 0, 1, 2);
    center_layout->setColumnStretch(0, 1);
    center_layout->setColumnStretch(1, 3);

    this->setLayout(center_layout);

    //设置样式
    right_scrollArea->setStyleSheet(("background-color:rgb(255, 255, 255)"));

    //设置菜单栏
    menubar->addMenu(menu);
    menu->addAction(openFile);
    menu->addAction(openFolder);

    imageList->setViewMode(QListView::ListMode);    //设置QListWidget的显示模式
    imageList->setIconSize(QSize(150,150));         //设置QListWidget中单元项的图片大小
    imageList->setSpacing(3);                       //设置QListWidget中单元项的间距
    imageList->setResizeMode(QListWidget::Adjust);  //设置自动适应布局调整
    //    imageList->setBatchSize(200);
    //    imageList->setLayoutMode(QListWidget::Batched); //批处理
    imageList->setMovement(QListWidget::Static);    //设置不能移动

    right_scrollArea->setWidget(label_text);
    right_scrollArea->setAlignment(Qt::AlignCenter);
}

void Image::connect_Signal_Slot()
{
    //点击 打开文件
    connect(openFile,&QAction::triggered,this,[=](){
        emit OpenFile_Clicked();
    });
    connect(this,&Image::OpenFile_Clicked,this,&Image::OpenFile);

    //点击 打开文件夹
    connect(openFolder,&QAction::triggered,this,[=](){
        emit OpenFolder_Clicked();
    });
    connect(this,&Image::OpenFolder_Clicked,this,&Image::OpenFolder);

    //点击 放大
    connect(enlargeBtn,&QPushButton::clicked,this,[=](){
        emit Enlarge_Clicked();
    });
    connect(this,&Image::Enlarge_Clicked,this,&Image::Enlarge);

    //点击 还原
    connect(restoreBtn,&QPushButton::clicked,this,[=](){
        emit Restore_Clicked();
    });
    connect(this,&Image::Restore_Clicked,this,&Image::Restore);

    //点击 缩小
    connect(narrowBtn,&QPushButton::clicked,this,[=](){
        emit Narrow_Clicked();
    });
    connect(this,&Image::Narrow_Clicked,this,&Image::Narrow);

    //双击缩略图
    connect(imageList,&QListWidget::itemDoubleClicked,this,[=](){
        emit Item_DoubleClicked();
    });
    //将缩略图加载到右侧滚动区
    connect(this,&Image::Item_DoubleClicked,this,&Image::Image_Selected);
}

Image::Image(QWidget *parent): QWidget(parent)
{
    this->resize(580,360);
    this->setWindowTitle("图片查看器");          //设置标题
    this->setWindowIcon(QPixmap(":/view.png"));

    initUi();
    connect_Signal_Slot();
    fileinfo = nullptr;
}

void Image::OpenPix(const QString &path)
{
    if(path!="")
    {
        origin_pix.load(path);                          //导入图片到 origin_pix
        label_image.resize(origin_pix.width(),origin_pix.height());
        label_image.setPixmap(origin_pix);              //加载图片到 label_image
        right_scrollArea->setWidget(&label_image);       //加载 label_image到scrollArea
        right_scrollArea->setAlignment(Qt::AlignCenter); //设置中心对齐
        new_pix = origin_pix;                           //将原图传递给加载图
    };
}

void Image::loadPix(int i)
{
    if(imageList->item(i)!=nullptr)
    {
        return;
    }
    QPixmap pix;
    QString filename;
    int fontSize;
    QListWidgetItem *item = new QListWidgetItem;
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *pix_label = new QLabel;
    QLabel *text_label = new QLabel;
    pix.load(fileinfo->at(i).filePath());
    pix_label->setPixmap(pix.scaled(90,90,Qt::KeepAspectRatio));
    filename = fileinfo->at(i).fileName();
    fontSize = fontMetrics().width(filename);

    if(fontSize>imageList->width())
    {
        filename = fontMetrics().elidedText(filename,Qt::ElideLeft,imageList->width()-30);
    }
    text_label->setText(filename);
    layout->addWidget(pix_label);
    layout->addWidget(text_label);
    widget->setLayout(layout);
    layout->setContentsMargins(0,0,0,0);

    pix_label->setAlignment(Qt::AlignCenter);
    text_label->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);

    imageList->addItem(item);
    item->setSizeHint(QSize(120,115));
    widget->setCursor(Qt::PointingHandCursor);
    imageList->setItemWidget(item,widget);
}

Image::~Image()
{
    if(fileinfo!=nullptr)
    {
        delete fileinfo;
    }
}

void Image::OpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "打开文件",
                                                    "/",
                                                    "image file(*.png *.jpg *jpeg)");
    if(filename!="")
    {
        origin_pix.load(filename);                      //导入图片到 origin_pix
        label_image.resize(origin_pix.width(),origin_pix.height());
        label_image.setPixmap(origin_pix);              //加载图片到 label_image
        right_scrollArea->setWidget(&label_image);       //加载 label_image到scrollArea
        right_scrollArea->setAlignment(Qt::AlignCenter); //设置中心对齐
        new_pix = origin_pix;                           //将原图传递给加载图
    };
}

void Image::OpenFolder()
{
    //获取路径
    QString pathname = QFileDialog::getExistingDirectory(this,
                                                         "打开文件夹",
                                                         "/");
    if(pathname!="")//路径不为空
    {
        imageList->clear();

        //设置过滤器
        QStringList filter;
        filter << "*.jpg" << "*.png" << "*.jpeg";

        //获取文件名列表
        QDir dir = QDir(pathname);

        if(fileinfo!=nullptr)
        {
            delete fileinfo;
        }

        fileinfo = new QList<QFileInfo>(dir.entryInfoList(filter));

        imageList->verticalScrollBar()->setMaximum(fileinfo->count());
        for(int i = 0;i<STEP; i++)
        {
            if(i>=fileinfo->count())
                break;
            loadPix(i);
        }
        connect(imageList->verticalScrollBar(),&QScrollBar::valueChanged,this,&Image::ScrollBar_moved);
    }
}

void Image::Enlarge()
{
    if(!origin_pix.isNull())
    {
        int width = new_pix.width()*1.6;
        int height = new_pix.height()*1.6;

        if(width<origin_pix.width()*8)
        {
            new_pix = origin_pix.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            label_image.resize(width,height);
            label_image.setPixmap(new_pix);
            right_scrollArea->setWidget(&label_image);
        }
        else
        {
            QMessageBox::warning(this,"警告","超出限制");
        }
    }
    else
    {
        QMessageBox::information(this,"提示","没有图片");
    }
}

void Image::Restore()
{
    if(!origin_pix.isNull())
    {
        new_pix = origin_pix;
        label_image.resize(new_pix.width(),new_pix.height());
        label_image.setPixmap(new_pix);
        right_scrollArea->setWidget(&label_image);
        right_scrollArea->scrollBarWidgets(Qt::AlignLeft|Qt::AlignTop);
    }
    else
    {
        QMessageBox::information(this,"提示","没有图片");
    }
}

void Image::Narrow()
{
    if(!origin_pix.isNull())
    {
        int width = new_pix.width()*0.625;
        int height = new_pix.height()*0.625;

        if(width>1&&height>1)
        {
            new_pix = origin_pix.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            label_image.resize(width,height);
            label_image.setPixmap(new_pix);
            right_scrollArea->setWidget(&label_image);
        }
        else
        {
            QMessageBox::warning(this,"警告","尺寸过小");
        }
    }
    else
    {
        QMessageBox::information(this,"提示","没有图片");
    }
}

void Image::Image_Selected()
{
    origin_pix.load(fileinfo->at(imageList->currentRow()).filePath());
    label_image.resize(origin_pix.width(),origin_pix.height());
    label_image.setPixmap(origin_pix);              //加载图片到 label_image
    right_scrollArea->setWidget(&label_image);       //加载 label_image到scrollArea
    right_scrollArea->setAlignment(Qt::AlignCenter); //设置中心对齐
    new_pix = origin_pix;                           //将原图传递给加载图
}

void Image::ScrollBar_moved(int v)
{
    qDebug()<<v;
    for(int i = v;i < v+STEP; i++)
    {
        if(i<fileinfo->count())
        {
            loadPix(i);
        }
    }

}

