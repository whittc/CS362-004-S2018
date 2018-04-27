#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main(){
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
    int i, j, jdiscardCount, jhandCount;


    printf("*************\n");
    printf("TEST: ENDTURN FUNCTION\n");

    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));


    for(j=0; j<numPlayers; j++){
        jdiscardCount = testG.discardCount[j];
        jhandCount = testG.handCount[j];
        //run endTurn function with testG
        endTurn(&testG);


        //check current player discarded cards
#if (NOISY == 1)
        printf("Current player hand 0 cards\n");
#endif
        assertTrue_int(testG.handCount[j], 0);

#if (NOISY == 1)
        printf("Current player cards in hand disabled\n");
#endif
        for (i=0; i<G.handCount[j]; i++){
            assertTrue_int(testG.hand[j][i], -1);
        }

#if (NOISY == 1)
        printf("Current player discard = discard  + cards in hand\n");
#endif
        assertTrue_int(testG.discardCount[j], jdiscardCount+ jhandCount);

        //check turn advanced to next player
#if (NOISY == 1)
        printf("Next players turn\n");
#endif
        if(j == numPlayers-1){
            //if j is last player, go back to first player
            assertTrue_int(testG.whoseTurn, 0);
        }
        else{
            //if j is not last player, go to next player
            assertTrue_int(testG.whoseTurn, G.whoseTurn+1);
        }

        //check next player's hand
#if (NOISY == 1)
        printf("Next player's hand initialized\n");
#endif
        assertTrue_int(testG.handCount[testG.whoseTurn], 5);

        //check game state reset for next player
#if (NOISY == 1)
        printf("Game reset (outpostPlayer, phase, numActions, numBuys, playedCardCount)\n");
#endif
        assertTrue_int(G.outpostPlayed, 0);
        assertTrue_int(G.phase, 0);
        assertTrue_int(G.numActions, 1);
        assertTrue_int(G.numBuys, 1);
        assertTrue_int(G.playedCardCount, 0);
    }

    printf("*************\n");

    return 0;
}
