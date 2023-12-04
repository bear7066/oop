#include "Creature.h"

char Creature::getShowChar() {
    return showChar;
}

int Creature::getAge() {
    return age;
}

void Creature::reset() {
    moved = false;
}