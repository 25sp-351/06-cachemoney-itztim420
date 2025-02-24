CC = gcc
CFLAGS = -Wall -Wextra -O2

all: moneytext

moneytext: main.o cache.o
	$(CC) $(CFLAGS) -o moneytext main.o cache.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

cache.o: cache.c
	$(CC) $(CFLAGS) -c cache.c

clean:
	rm -f moneytext main.o cache.o