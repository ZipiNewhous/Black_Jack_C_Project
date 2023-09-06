#pragma once
#include<inttypes.h>


enum Shape {heart = 0, club, diamond, spade};

typedef struct Card Card;
struct Card 
{
    uint8_t data;
    Card* next;
};


Card* createCard(size_t shape, size_t value);
void printCard(const Card* card);
