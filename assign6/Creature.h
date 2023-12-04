#ifndef _CREATURE_H
#define _CREATURE_H

#define WIDTH 35
#define HEIGHT 20

class Creature {
public:
    char getShowChar();
    virtual bool move(int nextY, int nextX, Creature *map[HEIGHT][WIDTH]) = 0;
    void reset();
    int getAge();
    bool moved = false;
protected:
    char showChar = ' ';
    int age = 0;
};

#endif