#ifndef CARD_H
#define CARD_H

typedef struct card {
    int rank;
    char suit;
    struct card *next;
} cardT;

cardT *makeCard(int rank, char suit);
cardT *addToPile(cardT *pile, cardT *card);
cardT *makeDeck(void);
int totalPile(cardT *pile);
void showPile(cardT *pile);
cardT *deal(cardT *pile);
char hitOrStand(void);
void freePile(cardT *pile);
cardT *shuffle(cardT *pile);

#endif

