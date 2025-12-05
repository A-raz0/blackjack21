#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

int playRound(void);

int main(void) {
    int playerWins = 0;
    int dealerWins = 0;

    srand((unsigned int)time(NULL));

    for (int round = 1; round <= 3; round++) {
        printf("\n===== Round %d =====\n", round);

        int playerWon = playRound();
        if (playerWon) {
            playerWins++;
        } else {
            dealerWins++;
        }

        printf("Score after round %d: Player %d - Dealer %d\n",
               round, playerWins, dealerWins);
    }

    printf("\n===== Final Score =====\n");
    printf("Player wins: %d\n", playerWins);
    printf("Dealer wins: %d\n", dealerWins);

    return 0;
}

int playRound(void) {
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
    printf("Dealer:\n");
    showPile(dealer);

    card = deal(deck);
    player = addToPile(player, card);

    card = deal(deck);
    player = addToPile(player, card);

    printf("Player:\n");
    showPile(player);

    while (1) {
        playerTotal = totalPile(player);

        if (playerTotal == 21) {
            break;
        }

        if (playerTotal > 21) {
            printf("Lost!\n");
            freePile(deck);
            freePile(player);
            freePile(dealer);
            return 0;
        }

        choice = hitOrStand();

        if (choice == 'h') {
            card = deal(deck);
            player = addToPile(player, card);
            printf("Player:\n");
            showPile(player);
        } else {
            break;
        }
    }

    playerTotal = totalPile(player);
    if (playerTotal > 21) {
        printf("Lost!\n");
        freePile(deck);
        freePile(player);
        freePile(dealer);
        return 0;
    }

    dealerTotal = totalPile(dealer);

    while (dealerTotal < 17) {
        card = deal(deck);
        dealer = addToPile(dealer, card);
        printf("Dealer:\n");
        showPile(dealer);
        dealerTotal = totalPile(dealer);
    }

    if (dealerTotal > 21) {
        printf("Won!\n");
        freePile(deck);
        freePile(player);
        freePile(dealer);
        return 1;
    } else {
        if (playerTotal > dealerTotal) {
            printf("Won!\n");
            freePile(deck);
            freePile(player);
            freePile(dealer);
            return 1;
        } else {
            printf("Lost!\n");
            freePile(deck);
            freePile(player);
            freePile(dealer);
            return 0;
        }
    }
}

