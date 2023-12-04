#include <cstdlib>
#include "Goat.h"

#include <iostream>
using namespace std;

Goat::Goat(bool moved) {
    showChar = 'X';
    this->moved = moved;
}

bool Goat::move(int nextY, int nextX, Creature *map[HEIGHT][WIDTH]) {
    age++;    
    food--;
    if(age == 70 || food == 0) return true;  //die
    
    moved = true;
    if(nextY >= 0 && nextY < HEIGHT && nextX >= 0 && nextX < WIDTH) {
        if(age >= 50 && age <= 55) {
            if(map[nextY][nextX] == nullptr) {
                map[nextY][nextX] = new Goat(true);
            } else if(map[nextY][nextX]->getShowChar() == 'I' && (!map[nextY][nextX]->moved || map[nextY][nextX]->getAge())) {
                free(map[nextY][nextX]);
                map[nextY][nextX] = nullptr;
                food += 5;
            }
        } else if(map[nextY][nextX] == nullptr || (map[nextY][nextX]->getShowChar() == 'I' && (!map[nextY][nextX]->moved || map[nextY][nextX]->getAge()))) {
            if(map[nextY][nextX] != nullptr) {
                free(map[nextY][nextX]);
                food += 5;
            }

            map[nextY][nextX] = this;
            return true;
        }
    }
    

    return false;
}
