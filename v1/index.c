#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 11
#define string char *

unsigned int hash(string str) {
  unsigned int hash_value, i;
  hash_value = 0;
  for(i = 0; str[i] != '\0'; i++) {
    hash_value += str[i];
  }
  return hash_value % TABLE_SIZE;
}

typedef struct word {
  string data;
  struct word *next;
} word;

word *create(string str) {
  word *new;
  new = (word *) malloc(sizeof(word));
  if(new) {
    new->data = (string) malloc(strlen(str));
    if(new->data) {
      strcpy(new->data, str);
    }
    new->next = NULL;
  }
  return new;
}

void init_table(word *table[]) {
  int i;
  for(i = 0; i < TABLE_SIZE; i++) {
    table[i] = NULL;
  }
}

void insert_in_list(word **list, string str) {
  word *new, *previous, *current;
  previous = *list;  current = (*list)->next;
  while(current != NULL && strcmp(str, current->data) > 0) {
    previous = current;
    current = current->next;
  }
  new = create(str);
  if(new) {
    new->next = current;
    previous->next = new;
  }
}

void showList(word *list) {
  if(!list) {
    printf(".");
  } else {
    printf("%s -> ", list->data);
    showList(list->next);
  }
}

void insert_in_table(word *table[], string str1, string str2) {
  unsigned int index;
  word *new;
  index = hash(str1);
  if(table[index] == NULL) {  
    new = create(str1);
    table[index] = new;
    insert_in_list(&new, str2);
  } else {
    if(strcmp(table[index]->data, str1) == 0) {
      /* o carinha já existe na tabela */
      word *head = table[index];
      insert_in_list(&head, str2);
    } else {
      /* ocupado */
      int empty, counter;
      
      
      
      if(table[try] == NULL) {
        new = create(str1);
        table[try] = new;
        insert_in_list(&new, str2);
      }
    }
  }
}

void showTable(word *table[]) {
  int i;
  for(i = 0; i < TABLE_SIZE; i++) {
    if(table[i] == NULL) {
      printf("%02d | NULL |\n", i);
    } else {
      word *iterator = table[i];
      printf("%02d | ", i);
      showList(iterator);
      printf("\n");
    }
  }
}

int main(void) { 
  word *table[TABLE_SIZE];
  
  init_table(table);
  insert_in_table(table, "carro", "veiculo");
  insert_in_table(table, "veiculo", "carro");

  insert_in_table(table, "carro", "automovel");
  insert_in_table(table, "automovel", "carro");

  insert_in_table(table, "pastel", "salgado");
  insert_in_table(table, "salgado", "pastel");


  insert_in_table(table, "camisa", "roupa");
  insert_in_table(table, "roupa", "camisa");

  insert_in_table(table, "short", "roupa");
  insert_in_table(table, "roupa", "short");

  showTable(table);
  return 0;
}