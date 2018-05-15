#ifndef MONSTER_H
#define MONSTER_H
#include "rpgobj.h"

class Monster :public RPGObj
{
public:
    Monster(){}
    ~Monster(){}
     void move(int direction, int steps=1);
};

#endif // MONSTER_H
