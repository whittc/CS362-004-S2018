#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int checkCard(int currentPlayer, struct gameState *testG, int handPos, int n){
    int r, i, card;
    struct gameState G;
    memcpy(&G, testG, sizeof(struct gameState));

    printf("ITERATION %d\n", n);

    card = 0;
    G.numActions = G.numActions+2;
    G.deckCount[currentPlayer]--;
    G.handCount[currentPlayer]++;
    G.discardCount[currentPlayer]++;
        G.hand[currentPlayer][handPos] = G.hand[currentPlayer][G.handCount[currentPlayer]-1];
        G.hand[currentPlayer][G.handCount[currentPlayer]-1] = -1;
    G.handCount[currentPlayer]--;

    r = refactorVillage(card, testG, handPos);
    printf("Card effect returned 0\n");
    assertTrue_int(r, 0);
    if (memcmp(&G, testG, sizeof(struct gameState)) ==  0)
        printf("Pre and post same, ALL PASSED\n");
    else{ 
        for(i=0; i< G.numPlayers; i++){
            if (i == currentPlayer){ 
                //check current player has +2 actions
                printf("Current player actions +2\n");
                assertTrue_int(testG->numActions, G.numActions);

                if(G.deckCount[i] != 0){
                    //check drew card from deck
                    printf("Current player deck -1\n");
                    assertTrue_int(testG->deckCount[i], G.deckCount[i]);
                }

                //check discarded
                printf("Current player discard +1\n");
                assertTrue_int(testG->discardCount[i], G.discardCount[i]);

            }
            else{      
                //check no changes to state of other players
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
    int n, i, currentPlayer, handPos;
    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf("*************\n");
    printf("TEST: VILLAGE CARD\n");

    for(n=0; n<300; n++){
        for(i=0;i<sizeof(struct gameState); i++){
            ((char *)&G)[i] = Random() * 256;
        }
        G.numPlayers = (Random() * MAX_PLAYERS);
        currentPlayer = (Random() * G.numPlayers);
        G.deckCount[currentPlayer] = (Random() * MAX_DECK);
        G.discardCount[currentPlayer] = (Random() * MAX_DECK);
        G.handCount[currentPlayer] = (Random() * MAX_HAND);
        handPos = (Random() * G.handCount[currentPlayer]);
        G.playedCardCount = Random() * MAX_DECK;
        G.whoseTurn = currentPlayer;

        checkCard(currentPlayer, &G, handPos, n); 
    }
    printf("*************\n");
    return 0;
}
