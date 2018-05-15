#include "world.h"
#include "icon.h"
#include<QPainter>
#include<QTime>
#include<QTimer>
static int fl,step,total;
void World::initWorld(string mapFile){

    //TODO 下面这部分逻辑应该是读入地图文件，生成地图上的对象
    //player 5 5

    this->_monster.initObj("monster");
    this->_monster.setPosX(4);
    this->_monster.setPosY(5);

    this->_player.initObj("player");
    this->_player.setPosX(2);
    this->_player.setPosY(1);

    RPGObj obj3,m,obj4,obj5;
    RPGObj s[9][9];
    RPGObj t[20];
    int i,j;
    for (i=2;i<=9;i++)
    {
        for (j=2;j<=9;j++)
        {
            f[i][j]=1;
        }
    }
    for (i=0;i<=5;i++)
    {
        t[i].initObj("tree2");
        t[i].setPosX(i*2);
        t[i].setPosY(0);
    }
    for (i=1;i<=4;i++)
    {
        t[i+11].initObj("tree1");
        t[i+11].setPosX(0);
        t[i+11].setPosY(i*2);
    }
    for (i=1;i<=4;i++)
    {
        t[i+15].initObj("tree1");
        t[i+15].setPosX(10);
        t[i+15].setPosY(i*2);
    }
    for (i=0;i<=5;i++)
    {
        t[i+6].initObj("tree2");
        t[i+6].setPosX(i*2);
        t[i+6].setPosY(10);
    }

    for (i=0;i<=6;i++)
    {
        j=3;
        s[i][j].initObj("stone");
        s[i][j].setPosX(i+2);
        s[i][j].setPosY(j);
        f[i+2][j]=0;
        this->_objs.push_back(s[i][j]);
    }
    for (i=0;i<=6;i++)
    {
        j=6;
        s[i][j].initObj("stone");
        s[i][j].setPosX(i+3);
        s[i][j].setPosY(j);
        this->_objs.push_back(s[i][j]);
        f[i+3][j]=0;
    }

    obj3.initObj("fruit");
    obj3.setPosX(2);
    obj3.setPosY(8);
    f[2][8]=2;
    this->_objs.push_back(obj3);

    obj4.initObj("fruit");
    obj4.setPosX(5);
    obj4.setPosY(5);
    f[5][5]=2;
    this->_objs.push_back(obj4);

    obj5.initObj("fruit");
    obj5.setPosX(5);
    obj5.setPosY(10);
    f[5][10]=2;
    this->_objs.push_back(obj5);

    obj3.initObj("fruit");
    obj3.setPosX(2);
    obj3.setPosY(8);
    f[2][8]=2;
    this->_objs.push_back(obj3);

    m.initObj("monster");
    m.setPosX(6);
    m.setPosY(9);
    f[6][9]=3;
    this->_objs.push_back(m);


    for (i=0;i<=19;i++)
    {
        this->_objs.push_back(t[i]);
    }


    //if (||!collidingItems().isEmpty())


}
/*QPainterPath world::shape()
{
    QpainterPath path;
    path.addRect(3,3,6,6);
    return path;
}*/
void World::delete_(int x,int y)
{
    RPGObj obj;
    obj.initObj("blank");
    obj.setPosX(x);
    obj.setPosY(y);
    this->_objs.push_back(obj);
}

void World::show(QPainter * painter){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        (*it).show(painter);
    }
    this->_monster.show(painter);
    if (flag==0)
    {
        this->_player.show(painter);
    }
}

void World::handlePlayerMove(int direction, int steps){
    int xx,yy;
    //flag=1;
    xx=_player.getPosX();
    yy=_player.getPosY();
    switch (direction){
        case 1:
            yy -= steps;
            break;
        case 2:
            yy += steps;
            break;
        case 3:
            xx -= steps;
            break;
        case 4:
            xx += steps;
            break;
    }
    if (xx<0||yy<0||xx>=12||yy>=12||yy+1<0||yy+1>=12)
       return;
    if (f[xx][yy+1]==1)
        this->_player.move(direction, steps);
    else if (f[xx][yy+1]==0)
        return;
    else if (f[xx][yy+1]==2)
    {
        int x=xx;
        int y=yy+1;
        auto it=_objs.begin();
        auto the_it=it;
        bool g=0;
        while (it!=_objs.end())
        {
            if (it->canEat())
            {
                int x1=it->getPosX(),x2=x1+it->getWidth();
                int y1=it->getPosY(),y2=y1+it->getHeight();
                if (x1<=x&&x2>x&&y>=y1&&y<y2)
                {
                    the_it=it;
                    g=1;
                    break;
                }
            }
            ++it;
        }
        if (g)
        {
            _objs.erase(the_it);
        }
        this->_player.move(direction, steps);
    }
    else if (f[xx][yy+1]==3)
    {
        flag=1;
    }

}
void World::handleMonsterMove(int direction, int steps){
    int xx,yy;
    //flag=1;
    xx=_monster.getPosX();
    yy=_monster.getPosY();
    switch (direction){
        case 1:
            yy -= steps;
            break;
        case 2:
            yy += steps;
            break;
        case 3:
            xx -= steps;
            break;
        case 4:
            xx += steps;
            break;
    }
    if (xx<0||yy<0||xx>=12||yy>=12||yy+1<0||yy+1>=12)
       return;
    if (f[xx][yy]==1)
        this->_monster.move(direction, steps);
    else if (f[xx][yy]==0)
        return;
    else if (f[xx][yy]==2)
    {
        int x=xx;
        int y=yy;
        auto it=_objs.begin();
        auto the_it=it;
        bool g=0;
        while (it!=_objs.end())
        {
            if (it->canEat())
            {
                int x1=it->getPosX(),x2=x1+it->getWidth();
                int y1=it->getPosY(),y2=y1+it->getHeight();
                if (x1<=x&&x2>x&&y>=y1&&y<y2)
                {
                    the_it=it;
                    g=1;
                    break;
                }
            }
            ++it;
        }
        if (g)
        {
            _objs.erase(the_it);
        }
        this->_monster.move(direction, steps);
    }
    else if (f[xx][yy]==3)
    {
        flag=1;
    }

}


