#ifndef _GOAT_H
#define _GOAT_H

#include "Creature.h"

class Goat : public Creature {
public:
    Goat(bool moved = false);
    bool move(int nextY, int nextX, Creature *map[HEIGHT][WIDTH]);
private:
    int food = 20;
};

#endif