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
    int testDeck1[5] = {7, 8, 0, 4, 5};
    int testDeck2[5] = {6, 8, 0, 5, 5};
    int testDeck3[5] = {7, 8, 0, 7, 0};
    int original_treasureTally=0, test_treasureTally=0;

    printf("*************\n");
    printf("TEST: ADVENTURER\n");

    //check normal conditions
    printf("Normal conditions test\n");
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));
   
    for(i=0; i<G.handCount[currentPlayer]; i++){
        if ((G.hand[currentPlayer][i] == 4) | (G.hand[currentPlayer][i] == 5) | (G.hand[currentPlayer][i] == 6))
            original_treasureTally++;
    }

    for(i=0; i<testG.deckCount[currentPlayer]; i++){
        testG.deck[currentPlayer][i] = testDeck1[i];
    }

    //call card effect
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


    //check current player hand +2 treasure cards
#if (NOISY == 1)
    printf("Current player treasure cards +2\n");
#endif
    for(i=0; i<testG.handCount[currentPlayer]; i++){
        if ((testG.hand[currentPlayer][i] == 4) | (testG.hand[currentPlayer][i] == 5) | (testG.hand[currentPlayer][i] == 6))
            test_treasureTally++;
    }
    assertTrue_int(test_treasureTally, original_treasureTally+2);


    //check current player hand +2 cards only
#if (NOISY == 1)
    printf("Current player hand +2 cards\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]+2);


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



    //check no treasure cards in deck handled correctly 
    printf("No treasure cards test\n");
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));
  

    original_treasureTally = 0;
    test_treasureTally = 0;
    for(i=0; i<G.handCount[currentPlayer]; i++){
        if ((G.hand[currentPlayer][i] == 4) | (G.hand[currentPlayer][i] == 5) | (G.hand[currentPlayer][i] == 6))
            original_treasureTally++;
    }

    for(i=0; i<testG.deckCount[currentPlayer]; i++){
        testG.deck[currentPlayer][i] = testDeck3[i];
    }

    //call card effect
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


    //check current player hand +2 treasure cards
#if (NOISY == 1)
    printf("Current player hand same (none available)\n");
#endif
    for(i=0; i<testG.handCount[currentPlayer]; i++){
        if ((testG.hand[currentPlayer][i] == 4) | (testG.hand[currentPlayer][i] == 5) | (testG.hand[currentPlayer][i] == 6))
            test_treasureTally++;
    }
    assertTrue_int(test_treasureTally, original_treasureTally);


    //check current player hand +2 cards only
#if (NOISY == 1)
    printf("Current player hand same (no treasure cards to draw)\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]);


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

   

    //check empty deck, correctly handled
    printf("Empty deck test\n");
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);

    //check empty deck, correctly handled
    //initialize game and players
    initializeGame(numPlayers, cards, seed, &G);
    original_treasureTally = 0;
    test_treasureTally = 0;

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for(i=0; i<testG.deckCount[currentPlayer]; i++){
        testG.deck[currentPlayer][i] = testDeck2[i];
    }

    //give current player empty hand
    testG.deckCount[currentPlayer] = 0;
    for(i=0; i<G.handCount[currentPlayer]; i++){
        if ((G.hand[currentPlayer][i] == 4) | (G.hand[currentPlayer][i] == 5) | (G.hand[currentPlayer][i] == 6))
            original_treasureTally++;
    }

    //call card effect
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    //check current player hand +2 treasure cards
#if (NOISY == 1)
    printf("Current player treasure cards +2\n");
#endif
    for(i=0; i<testG.handCount[currentPlayer]; i++){
        if ((testG.hand[currentPlayer][i] == 4) | (testG.hand[currentPlayer][i] == 5) | (testG.hand[currentPlayer][i] == 6))
            test_treasureTally++;
    }
    assertTrue_int(test_treasureTally, original_treasureTally+2);


    //check current player hand +2 cards only
#if (NOISY == 1)
    printf("Current player hand +2 cards\n");
#endif
    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]+2);


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

    return 0;
}
