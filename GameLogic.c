#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "GameLogic.h"


//initial all the game items and return the next phase = beeting
int initGame(User* player, User* dealer, Card_list* deck){
    initDeck(deck);
    initUser(player, deck, 1000);
    initUser(dealer, deck, 0);
    return beeting;
}






//get bett from the user (if he has) and move the bet to the pot, 
//return the next phase = user_turn or end_game if the user doesnt have enouth for betting
int bettingPhase(User* player, User* dealer){
    size_t bett = 0;
    printf("your cash: %d\npot: %d\n", player->cash, dealer->cash);
    if(dealer->cash == 0 && player->cash<10){
        puts("you are out of cash");
        return end_game;
    }
    bett = scanBett(player->cash, dealer->cash);
    player->cash -= bett;
    dealer->cash += bett;
    return user_turn;
}



//give to the player the option of hiting
int userTurnPhase(User* player, User*dealer, Card_list* deck){
    int sum = calculateHandValue(player->hand);
    char choice[6] = "";
    //initial the new deal
    initDeal(player, dealer, deck);

    //display the hands of the player and the user
    printCardList(player->hand, "your hand: ");
    puts("dealer hand:");
    puts("===========");
    printCard(dealer->hand->head);
    puts("???????");

    //check case of Black Jack
    if(sum == 21){
        puts("Black Jack!!!!");
        player->cash += (int)(1.5 * dealer->cash);
        dealer->cash = 0;
        return reset_game;
    }

    while(sum < 21){
        scanChoice(choice);
        if(!strcmp(choice, "HIT")){
            addCard(player->hand, takeOutRandomCard(deck));
            sum = calculateHandValue(player->hand);
            printCardList(player->hand, "your hand: ");
        }
        else if (!strcmp(choice, "STAND"))
        {
            return dealer_turn;
        }

    }

    return end_game;
}




//dealer hit till her sum value is more then the player or then 17
int dealerTurnPhase(User* dealer, User* player, Card_list* deck){
    int sumDealerValue = calculateHandValue(dealer->hand);
    int sumPlayerValue = calculateHandValue(player->hand);

    while (sumDealerValue < 17 && sumDealerValue <= sumPlayerValue)
    {
        addCard(dealer->hand, takeOutRandomCard(deck));
        sumDealerValue = calculateHandValue(dealer->hand);
    }

    return end_game;
}


//calculate the winner and add amount of cash according to the rules
int endGamePhase(User* player, User* dealer, Card_list* deck){
    int playerSum = calculateHandValue(player->hand);
    int dealerSum = calculateHandValue(dealer->hand);
    printCardList(dealer->hand, "dealer hand: ");
    printf("player score: %d\n", playerSum);
    printf("dealer score: %d\n", dealerSum);
    
    if(playerSum > 21){
        puts("bust");
        dealer->cash = 0;
    }
    else if (dealerSum > 21)
    {
        puts("dealer bust");
        player->cash += 2 *  dealer->cash;    
        dealer->cash = 0;
    }
    else if (playerSum > dealerSum)
    {
        puts("you win !!!");
        player->cash += 2 *  dealer->cash;    
        dealer->cash = 0;
    }
    else if (dealerSum >playerSum)
    {
        puts("dealer wins");
        dealer->cash = 0;
    }
    else{
        puts("tie :)");
    }
    return reset_game;
}



//reset the hands and ask the player for another game
int resetGame(User* player, User* dealer, Card_list* deck){
    //initial with template char
    char choice = 't';

    resetCards(player->hand, deck);
    resetCards(dealer->hand, deck);
    //scan choice from the user until valied input and return the next phase according to the choice
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        printf("Do you wish to bet again?(y/n).");
        scanf(" %c", &choice);
        
        if(choice == 'y' || choice == 'Y'){ return beeting;}
        if(choice == 'n' || choice == 'N'){ return exit_game;}

        printf("ener valid choice");
    }
    
}


//release all the menory of the game items
void exitGame(User* player, User* dealer, Card_list* deck){
    freeCardList(deck->head);
    freeCardList(player->hand->head);
    freeCardList(dealer->hand->head);
    free(player);
    free(dealer);
    free(deck);
}








//=======================================================
//fanctions that helps to the main functionf of the logic
//=======================================================



//initial all the lists with 2 random cards
void initDeal(User* player, User* dealer, Card_list* deck){
    addCard(player->hand, takeOutRandomCard(deck));
    addCard(player->hand, takeOutRandomCard(deck));
    addCard(dealer->hand, takeOutRandomCard(deck));
    addCard(dealer->hand, takeOutRandomCard(deck));
}



//return the input of hit or stand in upperCase
void scanChoice(char* choice){
    printf("HIT or STAND ?");
    scanf("%s", choice);
    
    // Convert the choice to uppercase
    for (size_t i = 0; choice[i]; i++) {
        choice[i] = toupper(choice[i]);
    }

}


//scan bett till it posible bett
size_t scanBett(int cash, int pot){
    int bett = cash + 1;
    while (bett<0 || bett%10 || bett>cash || (bett==0 && pot<10))
    {
        printf("How much you are willing to add to the pot? ");
        scanf("%d", &bett);
        //if bett is not posible - display why
        if (bett<0)
        {
            puts("+ Bets can't be negative");
        } 
        if (bett%10)
        {
            puts("+ Bets must be made in multiples of 10");
        }
        if (bett > cash)
        {
            puts("+ You dont have enough cahs for this bett");
        }
        if (bett==0 && pot==0)
        {
            puts("+ Bets can't be 0 now becous the pot is empty");
        }
    }
    return bett;
}