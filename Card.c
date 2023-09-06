#include<stdlib.h>
#include<stdio.h>
#include "Card.h"


//create new card
Card* createCard(size_t shape, size_t value){
    Card *card = malloc(sizeof(Card));
    //encode the shape and the value to binary
    card->data = (value<<4) | (1<<shape);
    card->next = NULL;
    return card;
}



//print ta values of the card
void printCard(const Card* card){
    //decode the value
    int val = card->data>>4;
    //print the face of the value
    switch (val){
        case 1:
            printf("Ace : ");
            break;
        case 11:
            printf("Jack : ");
            break;
        case 12:
            printf("Queen : ");
            break;
        default:
            printf("%d : ", card->data>>4);
            break;
    }
    //print the shape
    switch (card->data & 0x0f){
    case 1<<heart:
        printf("%s", "heart");
        break;
    case 1<<club:
        printf("%s", "club");
        break;
    case 1<<diamond:
        printf("%s", "diamond");
        break;
    case 1<<spade:
        printf("%s", "spade");
        break;
    default:
        break;
    }
    puts("\n");
}
