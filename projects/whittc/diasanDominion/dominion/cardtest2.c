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
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus); 



    printf("*************\n");
    printf("TEST: VILLAGE\n");

    for(i=0; i< numPlayers; i++){
        if ( i == currentPlayer){
            //check current player has +2 actions
#if (NOISY == 1)
            printf("Current player actions +2\n");
#endif
            assertTrue_int(testG.numActions, G.numActions+2);

            if(G.deckCount[i] != 0){
                //check drew card from deck
#if (NOISY == 1)
                printf("Current player deck -1\n");
#endif
                assertTrue_int(testG.deckCount[i], G.deckCount[i]-1);
            }

            //check discarded adventurer card
#if (NOISY == 1)
            printf("Current player last card=-1\n");
#endif
            assertTrue_int(testG.hand[i][testG.handCount[i]], -1);
       
        }
        else{      
            //check no changes to state of other players
#if (NOISY == 1)
            printf("Other player no change (hand, deck, discard)\n");
#endif
            assertTrue_array(testG.hand[i], G.hand[i]);
            assertTrue_array(testG.deck[i], G.deck[i]);
            assertTrue_array(testG.discard[i], G.discard[i]);
        }
    }
    //check no state change to victory or kingdom card piles
#if (NOISY == 1)
    printf("Victory/kingdom card piles no change\n");
#endif
    assertTrue_array(testG.supplyCount, G.supplyCount);
    
    printf("*************\n");

    return 0;
}
