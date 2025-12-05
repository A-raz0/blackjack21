CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: blackjack

blackjack: main.o card.o
	$(CC) $(CFLAGS) -o blackjack main.o card.o

main.o: main.c card.h
	$(CC) $(CFLAGS) -c main.c

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

clean:
	rm -f *.o blackjack

