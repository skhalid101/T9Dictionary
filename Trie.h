/*
Trie.h 
SHARYAR KHALID 
CSE 374 
HW 5 
contains all the struct declerations 
used by Trie.c and function
prototypes as well used
*/
#ifndef TRIE_H
#define TRIE_H

struct Trie_t* newNode();
struct Words* wordList(char* word);

// define a struct words for linked list called word list
typedef struct Words {
  char* word;
  struct Words* next;
}WordList;

// defines the struct trie called Node
typedef struct Trie_t {
  WordList *front;
  struct Trie_t* children[10];
}Node;
/*function prototypes*/
void freeNode(Node* root);
void freeWordList(WordList* front);
void insertWord(Node* head, char* word);
int charToInt(char letter);
void userInterface(Node* root);
void searchTrie(Node* root, char* numEntered);
#define MAX_LINE 100  // maximum character for a single line

#endif
