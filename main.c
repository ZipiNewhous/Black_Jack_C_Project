#include<time.h>
#include<stdlib.h>
#include "User.h"
#include "CardList.h"
#include "GameLogic.h"



int main(void){
    User* player = malloc(sizeof(User)), *dealer = malloc(sizeof(User));
    Card_list *deck = malloc(sizeof(Card_list));

    int state = init_game;
    srand(time(NULL));

    while (state != exit_game){    
        switch (state)
        {
            case init_game: {
                state = initGame(player, dealer, deck);
                break;
            }
            case beeting: {
                state = bettingPhase(player, dealer);
                break;
            }
            case user_turn: {
                state = userTurnPhase(player, dealer, deck);
                break;
            }
            case dealer_turn: {
                state = dealerTurnPhase(dealer, player, deck);
                break;
            }
            case end_game: {
                state = endGamePhase(player, dealer, deck);
                break;
            }
            case reset_game: {
                state = resetGame(player, dealer, deck);
                break;
            }
            default:{
                break;
            }
        }
    }
    exitGame(player, dealer, deck);
    return 0;
}