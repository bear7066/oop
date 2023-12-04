#ifndef _WORLD_H
#define _WORLD_H

#include "Creature.h"
#include "RandomNum.h"

#define WIDTH 35
#define HEIGHT 20

class World {
public:
    World(int pass, int seed);
    ~World();
    void mainLoop(int displayInterval);

private:
    int pass;
    Creature *map[HEIGHT][WIDTH];
    RandomNum randomNum;

    void show();
};

#endif