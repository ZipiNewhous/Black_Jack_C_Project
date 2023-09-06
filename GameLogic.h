#pragma once
#include "user.h"
#include "cardList.h"


enum State {init_game, beeting, user_turn, dealer_turn, end_game, reset_game, exit_game};


int initGame(User* player, User* dealer, Card_list* deck);

void initDeal(User* player, User* dealer, Card_list* deck);

int bettingPhase(User* player, User* dealer);

int userTurnPhase(User* player, User*dealer, Card_list* deck);

int dealerTurnPhase(User* dealer, User* player, Card_list* deck);

int endGamePhase(User* player, User* dealer, Card_list* deck);

int resetGame(User* player, User* dealer, Card_list* deck);

void exitGame(User* player, User* dealer, Card_list* deck);

//===============================================================

void scanChoice(char* choice);

size_t scanBett(int cash, int pot);