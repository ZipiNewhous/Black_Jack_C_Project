#pragma once
#include "cardList.h"

typedef struct User
{
    Card_list* hand;
    int cash;
} User;


void initUser(User* user, Card_list* deck, int cash);

int calculateHandValue(Card_list* hand);

