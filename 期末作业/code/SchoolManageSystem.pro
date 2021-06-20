QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DelStuDial.cpp \
    DelTeaDial.cpp \
    Functions.cpp \
    InsStuDial.cpp \
    InsTeaDial.cpp \
    MyPushButton.cpp \
    Person.cpp \
    School.cpp \
    Score.cpp \
    StuScene.cpp \
    Student.cpp \
    TeaScene.cpp \
    Teacher.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DelStuDial.h \
    DelTeaDial.h \
    Functions.h \
    Headers.h \
    InsStuDial.h \
    InsTeaDial.h \
    MainWindow.h \
    MyPushButton.h \
    Person.h \
    School.h \
    Score.h \
    StuScene.h \
    Student.h \
    TeaScene.h \
    Teacher.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/res.qrc
