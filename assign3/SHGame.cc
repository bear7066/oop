/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHGame.h"
#include "SHPlayer.h"
#include <iostream>
using namespace std;


// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
SHGame::SHGame(SHPlayer& shp, SHDealer& shd)
    : menu(sizeof(menuItems)/sizeof(char*), menuItems), player(shp), dealer(shd)
{
    playerCredit = dealerCredit = initCredit;
    restart();
}


// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
bool
SHGame::oneRun()
{
    player.showCards();
    dealer.showCards();
    menu.print();
    switch(menu.getAnswer()) {
        case ONE_MORE:
            moreCard();
            break;
        case GIVE_UP:
            giveUp();
            break;
        case RESTART:
            restart();
            break;
        case QUIT:
            return false;
    }
    return true;
}


// give the player and dealer one more card
// check if we can do that first.
// and judge who has win the round if the player have 5 cards
void
SHGame::moreCard()
{
    if(gameover) {
        cout << "GAME OVER!\n";
        return;
    }

    player.addCard(Card(dealer.giveCard()));
    dealer.addCard();

    //game end
    if(player.getNumCards() == 5) {
        showResult(dealer.judge(player));
    }
}


// give up this round,
// and you'll lose your credit
// the bet is equivalent to the number of card you keep
void
SHGame::giveUp()
{
    if(gameover) {
        cout << "GAME OVER!\n";
        return;
    }
    showResult(WIN);
}


// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void
SHGame::restart()
{
    if(!(playerCredit > 0 && dealerCredit > 0)) {
        cout << "Sorry. Game over. No loan here.\n";
        return;
    }
    if(!gameover) {
        cout << "Game is not over yet. Choose 'give up' to end a game\n";
        return;
    }
    
    gameover = false;

    //initialize player and dealer
    dealer.start();
    player.start();

    //draw card
    player.addCard(Card(dealer.giveCard()));
    dealer.addCard();
    player.addCard(Card(dealer.giveCard()));
    dealer.addCard();

    player.openFirstCard();
}

void 
SHGame::showResult(Result result)
{
    gameover = true;
    dealer.openFirstCard();
    switch(result) {
        case WIN:   //dealer win
            playerCredit -= player.getNumCards() * betCredit;
            dealerCredit += player.getNumCards() * betCredit;
            cout << "I win. Try again.";
            break;
        case TIE:
            cout << "Tie.";
            break;
        case LOSE:  //player win
            playerCredit += player.getNumCards() * betCredit;
            dealerCredit -= player.getNumCards() * betCredit;
            cout << "You win. Good job.";
            break;
    }

    cout << "(You have " << playerCredit << " points, I Have " << dealerCredit << " points.)\n";
}
