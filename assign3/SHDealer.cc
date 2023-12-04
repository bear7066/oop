/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHDealer.h"
#include <cstdlib>
#include <iostream>
using namespace std;


// constructor
SHDealer::SHDealer(): self(SHPlayer("Dealer"))
{
    for(int i = 28; i < 56; i++) {
        deck[i - 28].setID(i % 52);
    }
}


// destructor
SHDealer::~SHDealer()
{

}


// distribute a card to the player
int
SHDealer::giveCard()
{
    return deck[deck_id++].getID();
}


// give the dealer a card
void
SHDealer::addCard()
{
    self.addCard(Card(giveCard()));
}


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
    HandType self_ht = self.getHandPattern(), player_ht = player.getHandPattern();

    //check hand type
    if(self_ht == player_ht) {
        if(self.totalPips() == player.totalPips()) {
            return TIE;
        }
        //check total points
        return self.totalPips() > player.totalPips() ? WIN : LOSE;
    }
    return self_ht < player_ht ? WIN : LOSE;
}


// start a new game(round)
// before starting a new game(round), you should have
// a new deck, and then shuffle it.
// The deck only has pips A, 8, 9, 10, J, Q, K.
void
SHDealer::start()
{
    shuffle();
    deck_id = 0;
    self.start();
}


// shuffle the deck of cards
void
SHDealer::shuffle()
{
    for(int l = 0; l < 1000; l++) {
        int a = rand() % 28, b = rand() % 28;
        int buffer_id = deck[a].getID();
        deck[a].setID(deck[b].getID());
        deck[b].setID(buffer_id);
    }
}


// open the dealer's first card
void
SHDealer::openFirstCard()
{
    self.openFirstCard();
}


// show the dealer's hand to the screen
void
SHDealer::showCards() const
{
    self.showCards();
}
