#include <iostream>
#include <cstdlib>
#include "Goat.h"
#include "Grass.h"
#include "World.h"
using namespace std;

World::World(int pass, int seed): pass(pass) {
    randomNum = RandomNum(seed);
    int x, y;

    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            map[y][x] = nullptr;
        }
    }
    
    for(int i = 0; i < 5; i++) {
        while(1) {
            x = randomNum.getRandomNum(0, WIDTH);
            y = randomNum.getRandomNum(0, HEIGHT);
            if(map[y][x] == nullptr) break;
        }
        map[y][x] = new Goat();
    }

    for(int i = 0; i < 10; i++) {
        while(1) {
            x = randomNum.getRandomNum(0, WIDTH);
            y = randomNum.getRandomNum(0, HEIGHT);
            if(map[y][x] == nullptr) break;
        }
        map[y][x] = new Grass();
    }
}

World::~World() {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            if(map[y][x] != nullptr) free(map[y][x]);
        }
    }
}

void World::mainLoop(int displayInterval) {
    show();
    int y, x, r;
    for(int l = 0; l < pass; l++) {
        for(y = 0; y < HEIGHT; y++) {
            for(x = 0; x < WIDTH; x++) {
                if(map[y][x] == nullptr || map[y][x]->moved) continue;

                r = randomNum.getRandomNum(0, 3);
                if(map[y][x]->move(y + ((r & 2) - 1) * (r & 1), x + ((r & 2) - 1) * (~r & 1), map)) {
                    if(!map[y][x]->moved) {
                        free(map[y][x]);    //death
                    }
                    map[y][x] = nullptr;    //move
                }
            }
        }

        //reset ground
        for(y = 0; y < HEIGHT; y++) {
            for(x = 0; x < WIDTH; x++) {
                if(map[y][x]) map[y][x]->reset();
            }
        }

        if(l && l % displayInterval == 0) {
            show();
        }
    }
}

void World::show() {
    int x, y;

    cout << " ";
    for(x = 0; x < WIDTH; x++) {
        cout << " " << (x % 10);
    }
    cout << endl;

    for(y = 0; y < HEIGHT; y++) {
        cout << (y % 10);
        for(x = 0; x < WIDTH; x++) {
            if(map[y][x] != nullptr) {
                cout << " " << (char)map[y][x]->getShowChar();
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    cout << "-";
    for(x = 0; x < WIDTH; x++) {
        cout << "--";
    }
    cout << endl;
}
