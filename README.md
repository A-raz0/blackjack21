# Blackjack21 - C Program Project

This project implements a simplified Blackjack game in the terminal. C language based the game used dynamic memory allocation and linked lists to represent cards, hands, and the deck. Players interact through hitting or standing and can play multiple rounds in a single exceution.

## Overview

Each card is represented as a struct card with a rank, suit, and pointer to the next card.

A full deck of 52 cards is created using linked-list structures.

The deck is shuffled using a custom shuffle function.

Cards are dealt from the bottom of the deck.

Player and dealer hands are maintained as linked lists and updated dynamically.

The game follows basic Blackjack rules:

Player receives two cards; dealer receives one.

Player chooses to hit or stand.

Dealer hits until the total is at least 17.

Totals over 21 result in a loss.

Ties go to the dealer.

The game runs three rounds per session and tracks wins and losses.

### Compilation
make
./blackjack
