#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main(){
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G, testG;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    int handpos = 0;
    int i;


    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    //call card effect
    cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus); 



    printf("*************\n");
    printf("TEST: SEA HAG\n");

    for(i=0; i< numPlayers; i++){
        if (i != currentPlayer){
            //check other players have one less card in deck
#if (NOISY == 1)
            printf("Other players deck -1\n");
#endif
            assertTrue_int(testG.deckCount[i], G.deckCount[i]-1);


            //check other players have one more discarded card
#if (NOISY == 1)
            printf("Other players discard +1\n");
#endif
            assertTrue_int(testG.discardCount[i], G.discardCount[i]+1);

    
            //check other players have curse as top card
#if (NOISY == 1)
            printf("Other players top=curse\n");
#endif
            assertTrue_int(testG.deck[i][testG.deckCount[i]-1], curse);
            }
         }
  
    
    //check no state change for current player (hand, deck, discard)
#if (NOISY == 1)
    printf("Current player no change (hand, deck, discard)\n");
#endif
    assertTrue_array(testG.hand[currentPlayer], G.hand[currentPlayer]);
    assertTrue_array(testG.deck[currentPlayer], G.deck[currentPlayer]);
    assertTrue_array(testG.discard[currentPlayer], G.discard[currentPlayer]);
    
    //check no state change for victory or kingdom card piles
#if (NOISY == 1)
    printf("Victory/kingdom card piles no change\n");
#endif
    assertTrue_array(testG.supplyCount, G.supplyCount);

    printf("*************\n");

    return 0;
}
