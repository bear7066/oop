#include "Grass.h"

Grass::Grass(bool moved) {
    showChar = 'I';
    this->moved = moved;
}

bool Grass::move(int nextY, int nextX, Creature *map[HEIGHT][WIDTH]) {
    age++;
    if(age == 6) {
        return true;    //die
    } else if(age >= 3 && age <= 5) {
        if(nextY >= 0 && nextY < HEIGHT && nextX >= 0 && nextX < WIDTH && map[nextY][nextX] == nullptr) //valid position and no creature at there
            map[nextY][nextX] = new Grass(true);    //new Grass
    }

    moved = true;
    return false;
}