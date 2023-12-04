/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

#include <iostream>
#include <cassert>
#include "Card.h"
#include "SHPlayer.h"
#include "AnsiPrint.h"

using namespace std;


/**
 * Print my ID
 */
void
PrintMyID(const char* studId)
{
    char *str = new char[sizeof(studId) + 5];
    sprintf(str, "ID: %s", studId);
    AnsiPrint(str, yellow, red, true, true);
    cout << endl << endl;
    delete [] str;
}


/**
 * print the usage
 */
void
PrintUsage(const char* progName)
{
    assert(progName);
    cout << "Usage: " << progName << " [Seed] [ShowFirst(0/1)]" << endl;
}

int
main(int argc, char** argv)
{
    bool showFirst = false;
    long seed = 0;

    if( argc > 3 ) {
        PrintUsage(argv[0]);
        exit(-1);
    }
    if( argc == 3 ) {
        showFirst = atoi(argv[2]);      // the third argument shows the first card
    }
    if( argc > 1 ) {
        seed = atoi(argv[1]);
    }
    srand(seed);

    SHPlayer shplayer("Player");

    // put your code here

    //initialize deck
    Card deck[Card::kNCards];
    for(int i = 0; i < Card::kNCards; i++) {
        deck[i].setID(i);
    }

    //shuffle the deck
    for(int i = 0; i < 1000; i++) {
        int a = rand() % 52, b = rand() % 52;   //random get two positions

        //swap cards
        Card buffer = deck[a];
        deck[a] = deck[b];
        deck[b] = buffer;
    }

    //put card to player
    for(int i = 0; i < 5; i++) {
        shplayer.addCard(deck[i]);
    }

    //show first card
    if(showFirst)shplayer.openFirstCard();
    
    //print result
    shplayer.showCards();
    printf("It's %s\n", HandTypeName[shplayer.getHandPattern()]);
    printf("Total points: %d\n", shplayer.totalPips());

    PrintMyID("110703066");

    return 0;
}

