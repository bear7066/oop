#ifndef _GRASS_H
#define _GRASS_H

#include "Creature.h"

class Grass : public Creature {
public:
    Grass(bool moved = false);
    bool move(int nextY, int nextX, Creature *map[HEIGHT][WIDTH]);
};


#endif