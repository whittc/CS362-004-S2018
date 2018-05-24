#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int checkCard(int n, int currentPlayer, struct gameState *testG){
    int i, r;
    struct gameState G;
    memcpy(&G, testG, sizeof(struct gameState));

    printf("ITERATION %d\n", n);

    for(i=0; i<G.numPlayers; i++){
        if(i != currentPlayer){
            G.discard[i][G.discardCount[i]-1] = G.deck[i][G.deckCount[i]-1];
            G.deckCount[i]--;
            G.discardCount[i]++;
            G.deck[i][G.deckCount[i]-1] = curse;
        }
    }

    r = sea_hagEffect(currentPlayer, testG);
    printf("Card effect returned 0\n");
    assertTrue_int(r, 0);
    if(memcmp(&G, testG, sizeof(struct gameState) == 0))
        printf("Pre and post same, ALL PASSED\n");
    else{
        for(i=0; i< G.numPlayers; i++){
            if (i != currentPlayer){
                //check other players have one less card in deck
                printf("Other players deck -1\n");
                assertTrue_int(testG->deckCount[i], G.deckCount[i]);


                //check other players have one more discarded card
                printf("Other players discard +1\n");
                assertTrue_int(testG->discardCount[i], G.discardCount[i]);


                //check other players have curse as top card
                printf("Other players top=curse\n");
                assertTrue_int(testG->deck[i][testG->deckCount[i]-1], curse);
            }
        }

        //check no state change for current player (hand, deck, discard)
        printf("Current player no change (hand, deck, discard)\n");
        assertTrue_array(testG->hand[currentPlayer], G.hand[currentPlayer]);
        assertTrue_array(testG->deck[currentPlayer], G.deck[currentPlayer]);
        assertTrue_array(testG->discard[currentPlayer], G.discard[currentPlayer]);

        //check no state change for victory or kingdom card piles
        printf("Victory/kingdom card piles no change\n");
        assertTrue_array(testG->supplyCount, G.supplyCount);
    }

    return 0;
}


int main(){
    int n, i, j, currentPlayer;
    struct gameState G;


    SelectStream(2);
    PutSeed(3);

    printf("*************\n");
    printf("TEST: SEA HAG CARD\n");

    for(n=0; n<300; n++){
        for(i=0;i<sizeof(struct gameState); i++){
            ((char *)&G)[i] = Random() * 256;
        }
        G.numPlayers = 1 + (Random() * MAX_PLAYERS);
        currentPlayer = (Random() * G.numPlayers);
        for(j=0; j<G.numPlayers; j++){
            G.deckCount[j] = Random() * MAX_DECK;
            G.discardCount[j] = Random() * MAX_DECK;
        }

        checkCard(n,currentPlayer, &G); 
    }
    printf("*************\n");
    return 0;
}
