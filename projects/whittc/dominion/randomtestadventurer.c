#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int checkCard(int drawntreasure, struct gameState *testG, int currentPlayer, int n){
    int r, i, original_treasureTally, test_treasureTally;
    struct gameState G;
    memcpy(&G, testG, sizeof(struct gameState));

    original_treasureTally = 0;
    test_treasureTally = 0;
    
    printf("ITERATION %d\n", n);
/*
    if (G.deckCount[currentPlayer] <1){
        memcpy(G.deck[currentPlayer], testG->deck[currentPlayer], sizeof(int)*G.deckCount[currentPlayer]);
        G.deckCount[currentPlayer] = testG->deckCount[currentPlayer];
        memcpy(G.discard[currentPlayer], testG->discard[currentPlayer], sizeof(int)*G.discardCount[currentPlayer]);
        G.discardCount[currentPlayer] = testG->discardCount[currentPlayer];
    }
    */
    for(i=0; i<G.handCount[currentPlayer]; i++){
        if ((G.hand[currentPlayer][i] == 4) | (G.hand[currentPlayer][i] == 5) | (G.hand[currentPlayer][i] == 6))
            original_treasureTally++;
    }
    original_treasureTally = original_treasureTally+2;
    G.handCount[currentPlayer] = G.handCount[currentPlayer]+2;
    G.hand[currentPlayer][G.handCount[currentPlayer]-1] = testG->hand[currentPlayer][testG->handCount[currentPlayer]-1]; 
    G.hand[currentPlayer][G.handCount[currentPlayer]-2] = testG->hand[currentPlayer][testG->handCount[currentPlayer]-2];

    r = adventurerEffect(drawntreasure, testG, currentPlayer);
    printf("Card effect returned 0\n");
    assertTrue_int(r, 0);
    memcpy(G.discard[currentPlayer], testG->discard[currentPlayer], sizeof(int)*G.discardCount[currentPlayer]);
    G.discardCount[currentPlayer] = testG->discardCount[currentPlayer];
    memcpy(G.deck[currentPlayer], testG->deck[currentPlayer], sizeof(int)*G.deckCount[currentPlayer]);
    G.deckCount[currentPlayer] = testG->deckCount[currentPlayer];
    if(memcmp(&G, testG, sizeof(struct gameState) == 0))
        printf("Pre and post same, ALL PASSED\n");
    else{
        for(i=0; i<testG->handCount[currentPlayer]; i++){
            if ((testG->hand[currentPlayer][i] == 4) | (testG->hand[currentPlayer][i] == 5) | (testG->hand[currentPlayer][i] == 6))
                test_treasureTally++;
        }
        //check current player hand +2 treasure cards
        printf("Current player treasure cards +2\n");
        assertTrue_int(test_treasureTally, original_treasureTally);

        //check current player hand +2 cards only
        printf("Current player hand +2 cards\n");
        assertTrue_int(testG->handCount[currentPlayer], G.handCount[currentPlayer]);


        //check current player cards came from deck
        printf("Current player deck\n");
        assertTrue_int(testG->deckCount[currentPlayer], G.deckCount[currentPlayer]);


        //check hands are as expected
        printf("Current player hand\n");
        assertTrue_array(testG->hand[currentPlayer], G.hand[currentPlayer]);

        //check no changes to state of other players
        for(i=0; i< G.numPlayers; i++){
            if ( i != currentPlayer){
                printf("Other player no change (hand, deck, discard)\n");
                assertTrue_array(testG->hand[i], G.hand[i]);
                assertTrue_array(testG->deck[i], G.deck[i]);
                assertTrue_array(testG->discard[i], G.discard[i]);
            }
        }

        //check no state change to victory or kingdom card piles
        printf("Victory/kingdom card piles no change\n");
        assertTrue_array(testG->supplyCount, G.supplyCount);


    }
    return 0;
}


int main(){
    int n, i, index, currentPlayer, drawntreasure;
    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf("*************\n");
    printf("TEST: ADVENTURER CARD\n");

    for(n=0; n<300; n++){
        for(i=0;i<sizeof(struct gameState); i++){
            ((char *)&G)[i] = Random() * 256;
        }
        G.numPlayers = (Random() * MAX_PLAYERS);
        currentPlayer = (Random() * G.numPlayers);
        G.deckCount[currentPlayer] = (Random() * MAX_DECK);
        G.discardCount[currentPlayer] = (Random() * MAX_DECK);
        G.handCount[currentPlayer] = (Random() * MAX_HAND);
        drawntreasure = 0;

        for(i=0; i<2; i++){
            index = Random() * G.deckCount[currentPlayer];
            G.deck[currentPlayer][index] = 4 + (Random() * 3);
        }

        checkCard(drawntreasure, &G, currentPlayer, n); 
    }
    printf("*************\n");
    return 0;
}
