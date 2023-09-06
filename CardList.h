#pragma once
#include "card.h"

typedef struct Card_list
{
    Card* head;
    size_t len;
} Card_list;


void initDeck(Card_list* deck);

void addCard(Card_list* list, Card* card);

Card* takeOutRandomCard(Card_list* dec);

void printCardList(const Card_list* deck, const char* title);

void resetCards(Card_list* listToReset, Card_list* deck);

void freeCardList(Card* head);

