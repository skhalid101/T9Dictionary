/*
Trie.c 
SHARYAR KHALID 
CSE 374 
HW 5 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Trie.h"

/*
initializeTrie Function
This function creates a new trie, and allocates
memory for the trie also initializes the trie to NULL 
return the Trie it initialized
*/
Node* newNode() {
  Node *trie = (struct Trie_t*)malloc(sizeof(struct Trie_t));
  if (trie) {
    for (int i = 0; i < 10; i++) {
    trie->children[i] = NULL;
  }
    trie->front = NULL;
  } else {
    fprintf(stderr, "Memory could not be allocated for a new node");
  }
  return trie;
}


/*
This function takes the word in the dictionary and 
add it to the end of the trie after assigning a sequence of numbers 
to the children. Doesnt return anything
*/
void insertWord(Node* head, char* word) {
  WordList* temp;
    for (int i = 0; i < strlen(word)-1; i++) {
    int key = charToInt(word[i]);
    if (head->children[key] != NULL) {
      head = head->children[key];
    } else {
      head->children[key] = newNode();
      head = head->children[key];
    }
    if (i == strlen(word)-2) {
      if (head->front == NULL) {
        head->front = wordList(word);
      } else {
        temp = head->front;
        while (temp->next != NULL) {
          temp = temp->next;
        }
        temp->next = wordList(word);
      }
    }
  }
}
/*
This function (called by insert word) takes a word 
creates a new word list assigns memory to it then 
adds the word to it. It also adds the '\0' to the end 
to indicate end of word. It returns the wordlist of the 
corresponding word
*/
WordList* wordList(char* word) {
  WordList* list = (struct Words*)malloc(sizeof(struct Words));
  list->word = (char*)malloc(sizeof(char)*strlen(word));
  strncpy(list->word, word, strlen(word));
  list->word[strlen(word) - 1] = '\0';
  list->next = NULL;
  return list;
}
/*
This function is called after the trie has been build
it allows the user to interact with the program and 
enter numbers to find the word. It get the trie as the 
inout to it. Doesnt return anything 
*/
void userInterface(Node* root) {
  char numEntered[MAX_LINE];
  printf("Please enter a sequence of numbers\n");
  printf("ranging from 2 to 9 followed by \"#\" \n");
  printf("OR enter \"exit\" to quit.\n");
  while (fgets(numEntered, MAX_LINE, stdin)) {
    searchTrie(root, numEntered);
    printf("Enter Key Sequence (or \"#\" for next word):\n");
  }
}
/*
This function is used to traverse through the trie looking 
for the word associated wit the sequence of number entered 
by the user. It receieves the trie and the input by the user
*/
void searchTrie(Node* root, char *numEntered) {
  /*
  creates new pointer of type Node to keep track of 
  where we are at
  */
  Node* current;
  /*
  the following two commands creates a pointer list of type 
  Wordlist and initializes it to NULL
  */
  WordList* list = (struct Words*)malloc(sizeof(struct Words));
  list = NULL;
  int pound = 0;  // to keep track if the user entered '#'
  current = root;  // starts from the top
  int finish = 0;
    if (strstr(numEntered, "exit") != NULL) {
        exit(1);
      }
    /******************************************/
    /*******The following is to check**********/
    /*******if the user only entered **********/
    /*******a pound sign and not number********/
    /******************************************/
    if (numEntered[0] == '#') {
        finish = 1;
      if (list != NULL && list->next != NULL) {
          list = list->next;
          printf("%s\n", list->word);
    } else {
        printf("Sorry there are no more T9onyms\n");
      }
    /******************************************/
  } else {
      list = current->front;
    /*******************************************/
    /****The following goes through the*********/
    /****sequence entered to check what*********/
    /****number on the node it mathches*********/
    /****at which point current goes down*******/
    /**************that node********************/
     for (int i = 0; i < strlen(numEntered)-1; i++) {
       if (current != NULL) {
        if (numEntered[i] == '2')
            current = current->children[2];
        else if (numEntered[i] == '3')
            current = current->children[3];
        else if (numEntered[i] == '4')
            current = current->children[4];
        else if (numEntered[i] == '5')
            current = current->children[5];
        else if (numEntered[i] == '6')
            current = current->children[6];
        else if (numEntered[i] == '7')
            current = current->children[7];
        else if (numEntered[i] == '8')
            current = current->children[8];
        else if (numEntered[i] == '9')
            current = current->children[9];
        else if (numEntered[i] == '#') {
          if (pound == 0)
            list = current->front;
          pound++;
        } else {
          fprintf(stderr, "ERROR: Sequence needs to be between 2-9 or \"#\"\n");
        }
    /************************************************/
       } else {
          if (finish == 0) {
          finish = 1;
          printf("Sorry not found in current dictionary.\n");
         }
       }
    }
    }
    if (current != NULL && current->front != NULL && pound == 0) {
        list = current->front;
        printf("%s\n", list->word);
    } else if (pound > 0) {  // if the user inputs #
        while (list != NULL && list->next != NULL && pound > 0) {
        list = list->next;
        pound--;
      }
    /***********************************************************/
    /**************Used to check if the user entered************/
    /**************pound with the sequence of number************/
    /***********************************************************/
      if (pound == 0) {
        printf("%s\n", list->word);
    } else {
        if (finish == 0) {
          finish = 1;
          printf("Sorry not found in current dictionary.\n");
        }
    /***********************************************************/
      }
    } else {
      if (finish == 0) {
        printf("Sorry not found in current dictionary.\n");
      }
    }
}
/*
This function is used to free the memory allocated to the 
nodes previously 
*/
void freeNode(Node* root) {
  if (!root)
    return;
  // check the children and free of needed
  for (int i = 0; i < 10; i++) {
    if (root->children[i]) {
        freeNode(root->children[i]);
    }
  }
  // delete linked list of node
  if (root->front) {
    freeWordList(root->front);
  }
  // delete the node it self
  free(root);
}

/*
This function is used to free all the memory 
which was previously allocated to the linked lists 
*/
void freeWordList(WordList* front) {
  if (!front)
      return;
  WordList *current = NULL;
  if (front) {
    current = front->next;
    free(front->word);
    free(front);
    front = current;
  }
}
