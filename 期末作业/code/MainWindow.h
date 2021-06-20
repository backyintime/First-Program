#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include"Headers.h"
#include"School.h"
#include"StuScene.h"
#include"TeaScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    StuScene *stuScene;
    TeaScene *teaScene;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
