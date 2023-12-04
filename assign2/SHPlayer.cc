/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"


using namespace std;

const char* HandTypeName[9] = {
    "Straight flush",
    "Four of a kind",
    "Full house",
    "Flush",
    "Straight",
    "Three of a kind",
    "Two pair",
    "One pair",
    "Other"
};

// constructor
SHPlayer::SHPlayer(const char* playerName)
{
    this->playerName = playerName;
    start();
}

// initialize the number of cards to 0
void
SHPlayer::start()
{
    cardCount = 0;
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
    if(cardCount == kMaxCards) return;  //if reach kMaxCards then return
    cards[cardCount++] = newCard;       //add card to cards
}

// open the first card so it faces up
void
SHPlayer::openFirstCard()
{
    faceup = true;  //set faceup flag
}

// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
    char output[kCardWidth + 1] = {0};                  //initialize output
    for(int line = 0; line < kCardHeight; line++) {     //for each all lines
        for(int c = 0; c < cardCount; c++) {            //loop cards
            if(c) printf(" ");                          //print padding
            memcpy(output, card[c == 0 && !faceup ? 13 : cards[c].getPip()][line], kCardWidth);  //copy line to output, if faceup is false and print first card, print blank card.
            for(int i = 0; i < kCardWidth; i++) {       //foreach card line
                if(output[i] == 'x') output[i] = cardAbbrev[cards[c].getSuit()];
            }
            AnsiPrint(output, cardColor[cards[c].getSuit()], color::white);
        }
        printf("\n");   //change line
    }
}

// get the total points of the current hand
int
SHPlayer::totalPips() const
{
    int output = cardCount;     //add point difference

    //calculate total point
    for(int i = 0; i < cardCount; i++) {
        output += cards[i].getPip();
    }
    return output;
}

// judge what kind of hand type you own
// you need to have 5 cards
HandType
SHPlayer::getHandPattern() 
{
    if(cardCount != kMaxCards) return HandType::OTHER;
    sortCards();    //put to sortedCards
    if(isStraightFlush()) return HandType::STRAIGHT_FLUSH;
    if(isFourOfAKind()) return HandType::FOUR_OF_A_KIND;
    if(isFullHouse()) return HandType::FULL_HOUSE;
    if(isFlush()) return HandType::FLUSH;
    if(isStraight()) return HandType::STRAIGHT;
    if(isThreeOfAKind()) return HandType::THREE_OF_A_KIND;
    if(isTwoPair()) return HandType::TWO_PAIR;
    if(isOnePair()) return HandType::ONE_PAIR;
    return HandType::OTHER;
}

// return the number of cards at hand
int
SHPlayer::getNumCards() const
{
    return cardCount;
}

void
SHPlayer::sortCards() 
{
    for(int i = 0; i < cardCount; i++) {        //put all cards to sortedCards
        int smallestCardID = Card::kNCards;     //initial smallest card
        for(int j = 0; j < cardCount; j++) {    //compare all card
            if(cards[j].getID() < smallestCardID && (!i || cards[j].getID() > sortedCards[i - 1].getID())) {    //if cardID is smallest and big than previus sortedCard
                smallestCardID = cards[j].getID();  //update smallest card
            }
        }
        sortedCards[i].setID(smallestCardID);   //put smallest card in sortedCards
    }
}

// any five card sequence of same suit
bool 
SHPlayer::isStraightFlush() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        //check suit and pip
        if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() ||
            sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
            return false;

    return true;
}

// four cards of the same pip
bool 
SHPlayer::isFourOfAKind() const
{
    // O O O O X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[0].getPip() == sortedCards[2].getPip() )
        return true;
    // X O O O O
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() &&
            sortedCards[1].getPip() == sortedCards[3].getPip() )
        return true;

    return false;
}

// three of a kind combined with a pair
bool 
SHPlayer::isFullHouse() const
{
    // O O O X X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X X X O O
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// five cards of the same suit
bool
SHPlayer::isFlush() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
            return false;

    return true;
}

// five cards in sequence
bool 
SHPlayer::isStraight() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
            return false;

    return true;
}

// three cards of the same pip
bool 
SHPlayer::isThreeOfAKind() const
{
    for( int i = 0; i < kMaxCards - 2; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
                sortedCards[i].getPip() == sortedCards[i+2].getPip() )
            return true;

    return false;
}

// two cards of one pip, two cards of another pip
bool 
SHPlayer::isTwoPair() const
{
    // O O @ @ X
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[2].getPip() == sortedCards[3].getPip() )
        return true;
    // O O X @ @
    if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;
    // X O O @ @
    if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
            sortedCards[3].getPip() == sortedCards[4].getPip() )
        return true;

    return false;
}

// two cards of one pip
bool 
SHPlayer::isOnePair() const
{
    for( int i = 0; i < kMaxCards - 1; i++ )
        if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
            return true;

    return false;
}


