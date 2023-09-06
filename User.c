#include<stdlib.h>
#include "User.h"



//init the curenet user to hand of null and cash 0
void initUser(User* user, Card_list* deck, int cash){
    user->cash = cash;
    user->hand = malloc(sizeof(Card_list));
    user->hand->head = NULL;
    user->hand->len = 0;
}


//calculate the sum of the hand value according to the rools
//Queen and Jack = 10, Ace = 1 and +10 if it want cous bust
int calculateHandValue(Card_list* hand){
    int sum = 0, countAce = 0;

    for (Card* c = hand->head; c != NULL; c = c->next)
    {
        //decode the value of the card 
        int val = c->data>>4;
        if (val>=10) { sum+=10; }
        else if (val != 1) { sum += val; }
        else{  
            sum++;
            countAce++;
        }
    }

    if(countAce>0 && sum+10 < 21){ sum += 10; }
    return sum;
}
