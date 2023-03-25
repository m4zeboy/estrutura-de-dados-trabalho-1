#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define string char *
#define SIZE 10

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

void insertInNodeList(Node **list, string word) {
  Node *new;
  new = createNode(word);
  new->next = (*list)->next;
  (*list)->next = new;
}

bool insertInTable(Node *table[], string word) {
  unsigned int base_address = hash(word);
  Node *new = createNode(word);
  if(new == NULL) {
    fprintf(stderr, "Can't Alocate memory for Node with word '%s'\n", word);
    return false;
  }
  if(table[base_address] == NULL) {
    table[base_address] = new;
    return true;
  } else if(strcmp(table[base_address]->word, word) != 0) {
    Node *list;
    list = table[base_address];
    insertInNodeList(&list, word);
  }
  return false;
}

void initTable(Node *table[]) {
  int i;
  for(i = 0; i < SIZE; i++) {
    table[i] = NULL;
  }
}

void showList(Node *list) {
  if(list) {
    printf(" %x - %s ->", list->list, list->word);
    list = list->next;
  }
}

void showTable(Node *table[]) {
  int i;
  for(i = 0; i < SIZE; i ++) {
    printf("| %02d |", i);
    if(table[i] == NULL) printf(" NULL |\n");
    else {
      showList(table[i]);
      printf("\n");
    }
  }
}

int main(void) {
  Node *table[SIZE];
  initTable(table);
  insertInTable(table, "Moises");
  insertInTable(table, "Gabriel");
  insertInTable(table, "Vilmar");
  insertInTable(table, "Maria");
  insertInTable(table, "Antonio");
  printf("%s\n",table[6]->next->word);
  return 0;
}