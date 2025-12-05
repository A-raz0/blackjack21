#include <time.h>
#include <stdio.h>
#include "card.h"
#include <stdlib.h>

int main(void) {
    srand((unsigned int)time(NULL));

    cardT *deck;
    cardT *player = NULL;
    cardT *dealer = NULL;
    cardT *card;
    int i;
    int playerTotal;
    int dealerTotal;
    char choice;

    deck = makeDeck();

    for (i = 0; i < 7; i++) {
        deck = shuffle(deck);
    }

    card = deal(deck);
    dealer = addToPile(dealer, card);
    printf("Dealer:");
    showPile(dealer);

    card = deal(deck);
    player = addToPile(player, card);

    card = deal(deck);
    player = addToPile(player, card);

    printf("Player:");
    showPile(player);

    while (1) {

        playerTotal = totalPile(player);

        if (playerTotal == 21) break;
        if (playerTotal > 21) {
            printf("Lost!\n");
            freePile(deck); freePile(player); freePile(dealer);
            return 0;
        }

        choice = hitOrStand();

        if (choice == 'h') {
            card = deal(deck);
            player = addToPile(player, card);
            printf("Player:");
            showPile(player);
        } else {
            break;
        }
    }

    playerTotal = totalPile(player);
    if (playerTotal > 21) {
        printf("Lost!\n");
        freePile(deck); freePile(player); freePile(dealer);
        return 0;
    }

    dealerTotal = totalPile(dealer);

    while (dealerTotal < 17) {
        card = deal(deck);
        dealer = addToPile(dealer, card);
        printf("Dealer:");
        showPile(dealer);
        dealerTotal = totalPile(dealer);
    }

    if (dealerTotal > 21) {
        printf("Won!\n");
    } else {
        if (playerTotal > dealerTotal)
            printf("Won!\n");
        else
            printf("Lost!\n");
    }

    freePile(deck);
    freePile(player);
    freePile(dealer);

    return 0;
}
