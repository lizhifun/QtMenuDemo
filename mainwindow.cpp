#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //由于创建菜单栏和工具栏的时候就把动作加进去，所以这里需要先创建动作Action
    CreateActions();//创建动作Action
    CreatMenuBar();//创建菜单栏
    CreateToolbar();//创建工具栏
    fileTool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//设置工具栏中图标显示在文字上方
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateActions()//实例化下拉菜单功能
{
    const QIcon readActIcon =QIcon(":/imgs/read.png");
    readAct = new QAction(readActIcon, QStringLiteral("读取文件(&O)"),this);
    readAct->setStatusTip(QStringLiteral("读取文件"));
    readAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(readAct, &QAction::triggered, this, &MainWindow::ReadFile);

    const QIcon writeActIcon =QIcon(":/imgs/write.png");
    writeAct = new QAction(writeActIcon, QStringLiteral("写入文件(&N)"), this);
    writeAct->setStatusTip(QStringLiteral("写入文件"));
    writeAct->setShortcuts(QKeySequence::New);//创建快捷键
    connect(writeAct, &QAction::triggered, this, &MainWindow::WriteFile);

    const QIcon updateActIcon =QIcon(":/imgs/update.png");
    updateAct = new QAction(updateActIcon, QStringLiteral("更新文件(&U)"), this);
    updateAct->setStatusTip(QStringLiteral("更新文件"));
    connect(updateAct, &QAction::triggered, this, &MainWindow::UpdateFile);

    const QIcon exitActIcon =QIcon(":/imgs/exit.png");
    exitAct = new QAction(exitActIcon, QStringLiteral("退出系统(&E)"), this);
    exitAct->setStatusTip(QStringLiteral("退出系统"));
    exitAct->setShortcuts(QKeySequence::Close);//退出系统快捷键
    connect(exitAct, &QAction::triggered, this, &MainWindow::ExitProgram);
}

void MainWindow::CreatMenuBar()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("文件").trimmed()+tr("(&F)"));//实例化一个菜单栏
    operaMenu = menuBar()->addMenu(QStringLiteral("操作").trimmed()+tr("(&A)"));//实例化一个菜单栏
    fileMenu->addAction(readAct);
    fileMenu->addAction(writeAct);
    fileMenu->addAction(updateAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::CreateToolbar()//实例化工具栏
{
    fileTool = addToolBar(QStringLiteral("文件"));
    fileTool->addAction(readAct);
    fileTool->addAction(writeAct);
    fileTool->addAction(updateAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::ReadFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);//调用QSettings操作ini文件
    QString lang = settings->value("content","").toString();//读出ini文件中保存的内容，默认为空
    ui->textEdit->setText(lang);//将读出的内容显示到窗口中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("读取成功!"));
}

void MainWindow::WriteFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setValue("content","hello, this is a file!");//将内容写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("写入成功!"));
}

void MainWindow::UpdateFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setValue("content",ui->textEdit->toPlainText());//将当前选择的语言写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("更新成功!"));
}

void MainWindow::ExitProgram()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}

