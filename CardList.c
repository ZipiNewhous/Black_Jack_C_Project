#include<stdlib.h>
#include<stdio.h>
#include "CardList.h"
#define MAX_VALU 13


//int the dack whith all the optionals cards
void initDeck(Card_list* deck){
    deck->len = 0;
    deck->head = NULL;
    //looping all the shapes
    for(size_t Ishape = heart; Ishape<=spade; Ishape++){
        //looping all the values
        for(size_t Ivalue = 1; Ivalue<=MAX_VALU; Ivalue++){
            Card *card = createCard(Ishape, Ivalue);
            addCard(deck, card);
        }
    }

}


//add card to list
void addCard(Card_list* list, Card* card){
    card->next = list->head;
    list->head = card; 
    list->len++;
}


//take out card from random place of the the list
Card* takeOutRandomCard(Card_list* dec){
    //create random number
    size_t index = rand() % dec->len;
    Card* prevCard = NULL;
    Card* currCard = dec->head;
    while (index--)
    {
        prevCard = currCard;
        currCard = currCard->next;
    }
    if(prevCard == NULL){
        dec->head = currCard->next;
    }
    else{
        prevCard->next = currCard->next;
    }
    dec->len--;
    return currCard;    
}


//print the values of list of cars
void printCardList(const Card_list* deck, const char* title){
    Card* c = deck->head;
    //can get title for printing before values
    puts(title);
    puts("===========");
    for(size_t i = 0; i<deck->len && c != NULL; i++, c = c->next){
        printCard(c);
    }    

}


//reset list from all the cards, the cards will go back to the deck
void resetCards(Card_list* listToReset, Card_list* deck){
    Card* temp = listToReset->head;
    //go to the end of the list
    while (temp->next != NULL){
        temp = temp->next;
    }
    //concat the head of the deck to the end of the list
    temp->next = deck->head;
    //move tha fall list into the deck
    deck->head = listToReset->head;
    //reset the list
    listToReset->head = NULL;
    //take care of the lens of the lists
    deck->len += listToReset->len;
    listToReset->len = 0;
}


//releas card list memory
void freeCardList(Card* head){
    Card* temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}