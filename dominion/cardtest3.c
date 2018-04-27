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

    for(i=0; i<testG.deckCount[currentPlayer]; i++){
        testG.deck[currentPlayer][i] = 7;
    }
    for(i=0; i<testG.handCount[currentPlayer]; i++){
        testG.hand[currentPlayer][i] = 10;
    }


    //call card effect
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    testG.discardCount[currentPlayer]++;  


    printf("*************\n");
    printf("TEST: SMITHY\n");

    //check drew cards from deck
#if (NOISY == 1)
    printf("Current player deck -3\n");
#endif
    assertTrue_int(testG.deckCount[currentPlayer], G.deckCount[currentPlayer]-3);
    
    //check added cards to hand
#if (NOISY == 1)
    printf("Current player hand +3 cards -1 discard\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]+3-1);

    //check discarded from hand
#if (NOISY == 1)
    printf("Current player discard +1 \n");
#endif
    assertTrue_int(testG.discardCount[currentPlayer], G.discardCount[currentPlayer]+1);
  

    //check cards came from deck
#if (NOISY == 1)
    printf("Current drawn cards came from deck \n");
#endif
    for(i=0; i<3; i++){
        assertTrue_int(testG.deck[currentPlayer][testG.deckCount[currentPlayer] -1 + i], testG.hand[currentPlayer][testG.handCount[currentPlayer]-1-i]);
    }


    //check no changes to state of other players
    for(i=0; i< numPlayers; i++){
        if ( i != currentPlayer){
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
