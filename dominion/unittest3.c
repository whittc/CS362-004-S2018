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
    int i, functionReturn, originalCount;


    printf("*************\n");
    printf("TEST: DRAWCARD\n");

    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

#if (NOISY == 1)
    printf("Non-empty deck, non-empty discard test\n");
#endif
    //run drawCard function with testG
    functionReturn = drawCard(currentPlayer, &testG);

    //check current player gains card
#if (NOISY == 1)
    printf("Current player hand +1\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);

    //check current player deck loses card
#if (NOISY == 1)
    printf("Current player deck -1\n");
#endif
    assertTrue_int(testG.deckCount[currentPlayer], G.deckCount[currentPlayer]-1);

    //check current player got correct card
#if (NOISY == 1)
    printf("Current player new card == deck card\n");
#endif
    assertTrue_int(testG.deck[currentPlayer][testG.handCount[currentPlayer]-1],testG.deck[currentPlayer][testG.deckCount[currentPlayer]+1]);
   
    
    //check empty deck, non-empty discard handled
#if (NOISY == 1)
    printf("Empty deck, non-empty discard test\n");
#endif
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    //give current player empty hand by discarding
    originalCount = testG.handCount[currentPlayer];
    for(i = 0; i<originalCount-1; i++){
        discardCard(0, currentPlayer, &testG, 0);
    }
    testG.deckCount[currentPlayer] = 0;

    //run drawCard function with testG
    functionReturn = drawCard(currentPlayer, &testG);

    //check current player gains card
#if (NOISY == 1)
    printf("Current player hand +1\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], originalCount+1);

    //check current player deck loses card
#if (NOISY == 1)
    printf("Current player reshuffled deck -1\n");
#endif
    assertTrue_int(testG.deckCount[currentPlayer], originalCount-1);

    //check current player got correct card
#if (NOISY == 1)
    printf("Current player new card == deck card\n");
#endif
    assertTrue_int(testG.deck[currentPlayer][testG.handCount[currentPlayer]-1],testG.deck[currentPlayer][testG.deckCount[currentPlayer]+1]);


    //check empty deck, empty discard correctly handled
#if (NOISY == 1)
    printf("Empty deck, empty discard test\n");
#endif
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    //give current player empty hand
    testG.deckCount[currentPlayer] = 0;
    testG.discardCount[currentPlayer] = 0;

    //run drawCard function with testG
    functionReturn = drawCard(currentPlayer, &testG);

#if (NOISY == 1)
    printf("Empty deck returns -1\n");
#endif
    if(testG.deckCount[currentPlayer] == 0){
        assertTrue_int(functionReturn, -1);
    }

    printf("*************\n");

    return 0;
}
