#include "Image.h"

#include <QApplication>
#include<QSettings>

//QString appPath;
//QString className("Myasm");                       // 自定义的类别
//QString ext(".png");                              // 关联的文件类型
//QString extDes("");                               // 该文件类型描述

//void  func(QString appPath,QString className,QString ext,QString extDes)
//{
//    QString baseUrl("HKEY_CURRENT_USER\\Software\\Classes");    // 要添加的顶层目录
//    QSettings settingClasses(baseUrl, QSettings::NativeFormat);
//    settingClasses.setValue("/" + className + "/Shell/Open/Command/.", "\"" + appPath + "\" \"%1\"");
//    settingClasses.setValue("/" + className + "/.", extDes);
//    settingClasses.setValue("/" + className + "/DefaultIcon/.", appPath + ",0");
//    // 关联ext 和 类别
//    settingClasses.setValue("/" + ext + "/OpenWithProgIds/" + className, "");
//    // 立即保存该修改
//    settingClasses.sync();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Image i;
    QString path;

    if(argc>1)
    {
        path = QString::fromLocal8Bit(argv[1],512);
        i.OpenPix(path);
       //func(path,"className",".png","");
    }

    i.show();
    return a.exec();
}
