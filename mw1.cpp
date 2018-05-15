#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include<QTime>
#include<QTimer>

#include <map>
#include <iostream>

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    //timer2 = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(movement()));//timeoutslot()为自定义槽
    timer->start(100);
    //init game world
    _game.initWorld("");//TODO 应该是输入有效的地图文件
}
void MW1::movement()
{
    int d[4]={1,2,3,4};
    srand(time(0));
    int k=d[rand()%4];
    this->_game.handleMonsterMove(k, 1);
    this->update();
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}

void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
    }
    this->repaint();
}
