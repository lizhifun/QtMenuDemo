#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CreateActions();//创建下拉菜单函数
    void CreatMenuBar();//创建菜单栏函数
    void CreateToolbar();//创建工具栏函数

    void ReadFile();//读取文件函数
    void WriteFile();//写文件函数
    void UpdateFile();//更新文件函数
    void ExitProgram();//退出程序

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;//声明菜单栏
    QMenu *operaMenu;//声明菜单栏

    QToolBar *fileTool;//声明工具栏

    QAction *readAct;//声明读文件菜单
    QAction *writeAct;//声明写文件菜单
    QAction *updateAct;//声明更新文件菜单
    QAction *exitAct;//声明推出程序菜单
};
#endif // MAINWINDOW_H
