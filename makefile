CC = gcc
CFLAGS = -Wall -Wextra -g


test_liste_chainee : liste_chainee.c main.c liste_chainee.h
	$(CC) $(CFLAGS) liste_chainee.c main.c -o test_liste_chainee

test: test_liste_chainee
	./test_liste_chainee

clean:
	rm -f test_liste_chainee

.PHONY: test clean