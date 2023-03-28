#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define string char *
#define SIZE 177

typedef struct synonym {
  string data;
  struct synonym *next;
} Synonym;

typedef struct node {
  string word;
  Synonym *list;
  struct node *next;
} Node;

int power(int x, int n) {
  if(n == 0) return 1;
  return x * power(x, n - 1);
}

unsigned int hash(string data) {
  int k, i;
  unsigned int hashValue = 0;
  k = 13;
  for(i = 0; data[i] != '\0'; i++) {
    hashValue += data[i] * power(k, i);
  }
  return hashValue % SIZE;
}

Node *createNode(string data) {
  Node *new;
  new = (Node *) malloc(sizeof(Node));
  if(new == NULL) {
    return NULL;
  }
  new->word = (string) malloc(strlen(data) + 1);
  if(new->word == NULL) {
    return NULL;
  }
  strcpy(new->word, data);
  new->list = NULL;
  new->next = NULL;
  return new;
}

unsigned int nodeLength(Node *list) {
  if(list == NULL) {
    return 0;
  } else {
    return 1 + nodeLength(list->next);
  }
}

Synonym *createSynonym(string data) {
  Synonym *new;
  new = (Synonym *) malloc(sizeof(Synonym));
  if(new == NULL) {
    return NULL;
  }
  new->data = (string) malloc(strlen(data) + 1);
  if(new->data == NULL) {
    return NULL;
  }
  strcpy(new->data, data);
  new->next = NULL;
  return new;
}

unsigned int synonymLength(Synonym *list) {
  if(list == NULL) {
    return 0;
  } else {
    return 1 + synonymLength(list->next);
  }
}

bool insertSynonymInList(Synonym **list, string synonym) {
  Synonym *new, *previous, *current;
  previous = NULL;
  current = *list;
  while(current && strncmp(synonym, current->data, strlen(synonym)) > 0) {
    previous = current;
    current = current->next;
  }
  if(current && strncmp(synonym, current->data, strlen(synonym)) == 0) {
    return false;
  }
  new = createSynonym(synonym);
  new->next = current;
  if(previous == NULL) {
    *list = new;
  } else {
    previous->next = new;
  } 
  return true;
}

void initTable(Node *table[]) {
  int i;
  for(i = 0; i < SIZE; i++) {
    table[i] = NULL;
  }
}

bool insertInTable(Node *table[], string word, string synonym) {
  int baseAddress;
  baseAddress = hash(word);
  if(table[baseAddress] == NULL) {
    Node *new;
    new = createNode(word);
    table[baseAddress] = new;
    insertSynonymInList(&(table[baseAddress]->list), synonym);
    return true;
  } else {
    Node *iterator;
    iterator = table[baseAddress];
    while(iterator->next && strcmp(iterator->word, word) != 0) {
      iterator = iterator->next;
    }
    insertSynonymInList(&(iterator->list), synonym);
    if(strcmp(iterator->word, word) != 0) {
      Node *new;
      new = createNode(word);
      iterator->next = new;
    }
    return true;
  }
}

void showSynonymList(Synonym *list) {
  while(list) {
    printf("%s\n", list->data);
    list = list->next;
  }
}

void search(Node *table[], string word) {
  int baseAddress;
  Node *iterator;
  baseAddress = hash(word);
  iterator = table[baseAddress];
  while(iterator && strcmp(word, table[baseAddress]->word) != 0) {
    iterator = iterator->next;
  }
  if(iterator == NULL) {
    printf("hein?\n");
  } else {
    printf("%s\n", iterator->word);
    showSynonymList(iterator->list);
  }
}

void deleteNode(Node **list, string word) {
  Node *previous, *current, *trash;
  previous = NULL;
  current = *list;
  while(current && strcmp(word, current->word) != 0) {
    previous = current;
    current = current->next;
  }
  trash = current;
  if(previous == NULL) {
    *list = current->next;
  } else {
    previous->next = current->next;
  }
  free(trash->word);
  free(trash);
}

unsigned int countUsedRows(Node *table[]) {
  unsigned int i, count;
  count = 0;
  for(i = 0; i < SIZE; i++) {
    if(table[i] != NULL) {
      count++;
    }
  }
  return count;
}

void showNodeList(Node *list) {
  while(list) {
    printf("%s -> ", list->word);
    list = list->next;
  }
}

void showTable(Node *table[]) {
  int i;
  for(i = 0; i < SIZE; i ++) {
    printf("| %02d |", i);
    if(table[i] == NULL) printf(" NULL |\n");
    else {
      showNodeList(table[i]);
      printf("\n");
    }
  }
}

void saveSynonym(FILE *stream, Synonym *s) {
  fprintf(stream, "%s\n", s->data);
}

void saveSynonymList(FILE *stream, Synonym *list) {
  while(list) {
    saveSynonym(stream, list);
    list = list->next;
  }
}

void saveNode(FILE *stream, Node *n) {
  Synonym *s;
  unsigned int synonyms;
  s = n->list;
  synonyms = synonymLength(s);
  fprintf(stream, "%s\n", n->word);
  fprintf(stream, "%d\n", synonyms);
  saveSynonymList(stream, s);
}

void saveNodeList(FILE *stream, Node *n) {
  unsigned int nodes;
  Node *iterator = n;
  nodes = nodeLength(n);
  fprintf(stream,"%d\n", nodes);
  while(iterator) {
    saveNode(stream, iterator);
    iterator = iterator->next;
  }
}

void save(Node *table[]) {
  FILE *file;
  file = fopen("data.data", "w");
  if(file) {
    unsigned int usedRows, i;
    usedRows = countUsedRows(table);
    fprintf(file,"%d\n", usedRows);
    for(i = 0; i < SIZE; i++) {
      if(table[i] != NULL) {
        saveNodeList(file, table[i]);
      }
    }
    fclose(file);
  }
}

void readSynonymList(FILE *stream, int synonyms, Synonym **list) {
  int k;
  for(k = 0; k < synonyms; k++) {
    char synonym[30];
    fscanf(stream,"%s\n", synonym);
    insertSynonymInList(list, synonym);
  }
}

void readNodeList(FILE *stream, int nodes, Node **nodeList, int *baseAddress) {
  int j;
  for(j = 0; j < nodes; j++) {
    char word[30];
    int synonyms;
    Node *node;
    Synonym *list;
    fscanf(stream, "%s\n", word);
    fscanf(stream,"%d\n", &synonyms);
    list = NULL;
    readSynonymList(stream, synonyms, &list);
    node = createNode(word);
    node->list = list;
    if(j == 0) {
      *baseAddress = hash(word);
      *nodeList = node;
    } else {
      node->next = (*nodeList)->next;
      (*nodeList)->next = node;
    }
  }
}

void read(Node *table[]) {
  FILE *file;
  file = fopen("data.data", "r");
  if(file) {
    int usedRows, i;
    fscanf(file,"%d\n", &usedRows);
    for(i = 0; i < usedRows; i++) {
      int nodes,baseAddress;
      Node *nodeList = NULL;
      fscanf(file, "%d\n", &nodes);
      readNodeList(file, nodes, &nodeList, &baseAddress);
      table[baseAddress] = nodeList;
    }
    fclose(file);
  }
}