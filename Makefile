# HW 5
# MAKEFILE
# SHARYAR KHALID
# CSE 374
#default target
talk: t9.o Trie.o
	gcc -Wall -g -std=c11 -o talk t9.o Trie.o
Trie.o: Trie.h Trie.c
	gcc -Wall -g -std=c11 -c Trie.c
t9.o: Trie.h t9.c
	gcc -Wall -g -std=c11 -c t9.c
# "phony" target to remove built files and backups
clean:
	rm -f *.o talk *~
