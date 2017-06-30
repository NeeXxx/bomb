#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),b()
{
    ui->setupUi(this);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(&b);
    resize(1000,1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
