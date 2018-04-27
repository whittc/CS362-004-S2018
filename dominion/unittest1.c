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
    int testCards[11] = {council_room, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, adventurer, gardens};
    int i, j, k;


    printf("*************\n");
    printf("TEST: GAINCARD FUNCTION \n");

    for (k=0; k<11; k++){
        for (j=0; j<3; j++){
            //initialize game and players
            initializeGame(numPlayers, cards, seed, &G);

            //copy game state to test game
            memcpy(&testG, &G, sizeof(struct gameState));

            printf("Card number %d\n", testCards[k]);

            //run gainCard function with testG
            gainCard(testCards[k], &testG, j, currentPlayer);

            if(supplyCount(testCards[k], &testG) < 1){
                //  check no changes if card not available
#if (NOISY == 1)
                printf("Card not available, current player no change (hand, deck, discard)\n");
#endif
                assertTrue_array(testG.hand[currentPlayer], G.hand[currentPlayer]);
                assertTrue_array(testG.deck[currentPlayer], G.deck[currentPlayer]);
                assertTrue_array(testG.discard[currentPlayer], G.discard[currentPlayer]);
            }

            else{
                if (j == 1){
                    // check current player deck +1
#if (NOISY == 1)
                    printf("Add to deck, current player deck +1\n");
#endif
                    assertTrue_int(testG.deckCount[currentPlayer], G.deckCount[currentPlayer]+1);
#if (NOISY == 1)
                    printf("Added correct card to deck\n");
#endif
                    assertTrue_int(testG.deck[currentPlayer][testG.deckCount[currentPlayer]-1], testCards[k]);
#if (NOISY == 1)
                    printf("Supply deck -1\n");
#endif
                    assertTrue_int(testG.supplyCount[testCards[k]], G.supplyCount[testCards[k]]-1);
                }

                if (j == 2){
                    // check current player hand +1
#if (NOISY == 1)
                    printf("Add to hand, current player hand +1\n");
#endif
                    assertTrue_int(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
#if (NOISY == 1)
                    printf("Added correct card to hand\n");
#endif
                    assertTrue_int(testG.hand[currentPlayer][testG.handCount[currentPlayer]-1], testCards[k]);
#if (NOISY == 1)
                    printf("Supply deck -1\n");
#endif
                    assertTrue_int(testG.supplyCount[testCards[k]], G.supplyCount[testCards[k]]-1);
                }

                if (j == 0){
                    // check current player discarded card
#if (NOISY == 1)
                    printf("Add to discard, current player discard +1\n");
#endif
                    assertTrue_int(testG.discardCount[currentPlayer], G.discardCount[currentPlayer]+1);
#if (NOISY == 1)
                    printf("Discarded correct card\n");
#endif
                    assertTrue_int(testG.discard[currentPlayer][testG.discardCount[currentPlayer]-1], testCards[k]);
                }
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

        }
    }

    printf("*************\n");

    return 0;
}
