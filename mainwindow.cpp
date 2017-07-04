#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),b(),
    ui(new Ui::MainWindow)
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


void MainWindow::paintEvent(QPaintEvent *)
{
    //qDebug()<<"angry!"<<endl;
    //绘制地图底板
    QPainter painter(this);
    //painter.translate(20,100);
    QPixmap tground;
    tground.load(":/image/images/ground.png");
    painter.drawPixmap(0,0,900,900,tground);
    //绘制前的定义
    std::map<aboveSubstance,QString> aM;
    std::map<underSubstance,QString> uM;
    aM[player1]="player1.png";
    aM[player2]="player2.png";
    aM[wood]="wood.png";
    aM[sBomb]="bomb.png";
    aM[arrowDown]=aM[arrowLeft]=aM[arrowRight]=aM[arrowUp]="flame.png";
    uM[house]="hosue.png";
    uM[tree]="tree.png";
    uM[water]=uM[ground]=uM[bridge]="blank.png";
    QString name, full_name;
    //绘制每格元素
    b.countMapForDraw();
    QPixmap pix;
    for (int i=1;i<10;i++)
    {
        for (int j=1;j<10;j++)
        {
            substance judge=b.mapForDraw[i][j];
            if (judge.as!=air)
            {
                name=aM[judge.as];
            }
            else
            {
                name=uM[judge.us];
            }
            full_name=":/image/images/"+name;
            pix.load(full_name);
            painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
        }
    }
}
//*/
