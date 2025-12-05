#include <stdio.h>
#include <stdlib.h>
#include "card.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

cardT *makeCard(int rank, char suit) {
    if (rank < 1 || rank > 13) return NULL;
    if (suit != 'C' && suit != 'D' && suit != 'H' && suit != 'S') return NULL;

    cardT *newCard = (cardT *)malloc(sizeof(cardT));
    if (newCard == NULL) return NULL;

    newCard->rank = rank;
    newCard->suit = suit;
    newCard->next = NULL;
    return newCard;
}

cardT *addToPile(cardT *pile, cardT *card) {
    if (card == NULL) return pile;
    card->next = pile;
    return card;
}

cardT *makeDeck(void) {
    cardT *deck = NULL;
    char suits[4] = {'C','D','H','S'};
    int i, r;

    for (i = 0; i < 4; i++) {
        for (r = 1; r <= 13; r++) {
            cardT *newCard = makeCard(r, suits[i]);
            if (newCard == NULL) return deck;
            deck = addToPile(deck, newCard);
        }
    }
    return deck;
}

int totalPile(cardT *pile) {
    int total = 0;
    cardT *current = pile;
    while (current != NULL) {
        if (current->rank >= 11)
            total += 10;
        else
            total += current->rank;
        current = current->next;
    }
    return total;
}

void showPile(cardT *pile) {
    cardT *curr;

    if (pile == NULL) {
        printf("(empty)\n");
        return;
    }

    curr = pile;
    while (curr != NULL) {
        printf("┌────┐ ");
        curr = curr->next;
    }
    printf("\n");

    curr = pile;
    while (curr != NULL) {
        const char *color = (curr->suit == 'H' || curr->suit == 'D') ? RED : RESET;
        printf("│%s%-2d%s  │ ", color, curr->rank, RESET);
        curr = curr->next;
    }
    printf("\n");

    curr = pile;
    while (curr != NULL) {
        const char *color = (curr->suit == 'H' || curr->suit == 'D') ? RED : RESET;
        printf("│  %s%c%s │ ", color, curr->suit, RESET);
        curr = curr->next;
    }
    printf("\n");

    curr = pile;
    while (curr != NULL) {
        printf("└────┘ ");
        curr = curr->next;
    }
    printf("\n");
}

cardT *deal(cardT *pile) {
    if (pile == NULL) return NULL;
    if (pile->next == NULL) return pile;

    cardT *current = pile;
    cardT *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    prev->next = NULL;
    return current;
}

char hitOrStand(void) {
    char word[100];

    while (1) {
        printf("Hit or stand? (h/s): ");
        fflush(stdout);

        if (scanf("%99s", word) != 1) {
            continue;
        }

        char c = word[0];

        if (c == 'h' || c == 'H') {
            return 'h';
        }

        if (c == 's' || c == 'S') {
            return 's';
        }

        printf("Please enter h or s.\n");
    }
}

cardT *shuffle(cardT *pile) {
    if (pile == NULL) {
        return NULL;
    }

    int count = 0;
    cardT *current = pile;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    cardT **array = (cardT **)malloc(count * sizeof(cardT *));
    if (array == NULL) {
        return pile;
    }

    current = pile;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        cardT *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[count - 1]->next = NULL;

    cardT *newHead = array[0];
    free(array);

    return newHead;
}

void freePile(cardT *pile) {
    cardT *current = pile;
    cardT *nextCard;
    while (current != NULL) {
        nextCard = current->next;
        free(current);
        current = nextCard;
    }
}

