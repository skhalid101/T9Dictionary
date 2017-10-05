/*
t9.c 
SHARYAR KHALID 
CSE 374 
HW 5 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Trie.h"

int openFile(char *fileName, Node *root);
int charToInt(char letter);

char t9Number[26] = {2, 2, 2,
                     3, 3, 3,
                     4, 4, 4,
                     5, 5, 5,
                     6, 6, 6,
                     7, 7, 7, 7,
                     8, 8, 8,
                     9, 9, 9, 9};
/*
This is the main function it check to see correct number
of arguments are enetered or not and also calls the function
to open the file entered in by the user. After opening the file 
the main fuction initiates the user interaction and frees all the 
space as well 
*/
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "USAGE: /.[output file name] [dictionary name]\n");
    return 1;
  }
  Node *root = newNode();  // pointer to main root of Trie
  int value = openFile(argv[1], root);
  if (value) {
  printf("File succesfully added to Trie\n");
  userInterface(root);
  freeNode(root);
  return 0;
} else {
    return 1;
  }
}
/*
This function gets passed the name of the file that needs to be opened 
it check if the file exits and return 0 if it doesnt exits and return 1 
if it does exits and opens succefully. This also add the words in the dictionary
to the trie 
*/
int openFile(char *fileName, Node *root) {
  char word[MAX_LINE];
  FILE *dict = fopen(fileName, "r");
  if (dict == NULL) {
    fprintf(stderr, "File does not exist\n");
    return 0;
  }
  while (fgets(word, MAX_LINE, dict) != NULL) {
    insertWord(root, word);
  } fclose(dict);

  return 1;
}
/*
takes a letter and return the number that 
letter corresponds to it also uses t9Number 
array to select the correct number 
*/
int charToInt(char letter) {
    int index = (int)letter - 'a';  // 'a' corresponds to 97
    return t9Number[index];
}
