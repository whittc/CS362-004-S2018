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
    int i, originalCount;
    int handPos[5] = {4, 0, 2, 0, 1};


    printf("*************\n");
    printf("TEST: DISCARDCARD\n");

    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

#if (NOISY == 1)
    printf("Discarding hand\n");
#endif
    originalCount = testG.handCount[currentPlayer];
    for(i=0; i<originalCount; i++){
        //check discard function
        discardCard(handPos[i], currentPlayer, &testG, 0);

        //check current player hand count -1
#if (NOISY == 1)
        printf("Current player hand -1\n");
#endif
        assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]-1-i);


        //check played card count +1
#if (NOISY == 1)
        printf("Played card count +1\n");
#endif
        assertTrue_int(testG.playedCardCount, G.playedCardCount+1+i);

        //check discard card count +1
#if (NOISY == 1)
        printf("Discard card count +1\n");
#endif
        assertTrue_int(testG.discardCount[currentPlayer], G.discardCount[currentPlayer]+1);
    }

    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    //check trashing function
#if (NOISY == 1)
    printf("Trashing card\n");
#endif
    discardCard(handPos[0], currentPlayer, &testG, 1);

    //check current player hand count -1
#if (NOISY == 1)
    printf("Current player hand -1\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]-1);


    printf("*************\n");

    return 0;
}
