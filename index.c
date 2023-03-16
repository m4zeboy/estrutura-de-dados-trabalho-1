#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_LENGTH 233

typedef struct word {
    char *data;
    struct word *next;
} word;

int power(int x, int n) {
  if(n == 0) {
    return 1;
  } else if (n == 1) {
    return x;
  } else
    return x * power(x, n - 1);
}

unsigned int hash(char *str) {
  int i, k;
  unsigned int count = 0;
  k = 13;
  for(i = 0; str[i] != '\0'; i++) {
    count = count + (str[i] * power(k, i));
  }
  return count % TABLE_LENGTH;
}

word *newWord(char *data) {
  word *new = (word *) malloc(sizeof(word));
  if(new) {
    new->data = (char *) malloc(strlen(data + 1));
    if(new->data) {
      strcpy(new->data, data);
    }
    new->next = NULL;
  }
  return new;

}

void insertInList(word **head, char *data) {
  word *new = newWord(data);
  if(new) {
    word *p, *q;
    p = *head;
    q = (*head)->next;
    while(q && strcmp(data, q->data) > 0) {
      p = q;
      q = q->next;
    }
    new->next = q;
    p->next = new;
  }
}

void showList(word *head) {
  while(head != NULL) {
    printf("%s - %x -> ", head->data, head->next);
    head = head->next;
  }
}

void initTable(word *table[]) {
  int i;
  for (i = 0; i < TABLE_LENGTH; i++){
    table[i] = NULL;
  }
}

void insertInTable(word *table[], char *data) {
  int index = hash(data);
  if(table[index] == NULL) {
    word *head = newWord(data);
    if(head) {
      table[index] = head;
    }
  } else {
    fprintf(stderr,"Aconteceu uma colisão, não foi possível inserir a palavra %s na estrutura.\n", data);
  }
}

void showTable(word *table[]) {
  int i;
  word *current;
  for(i = 0; i < TABLE_LENGTH; i++) {
    if(table[i] == NULL) {
      printf("NULL");
    } else {
      printf("head: %s -> ", table[i]->data);
      current = table[i]->next;
      while(current) {
        printf("%s -> ",current->data);
        current = current->next;
      }
    }
    printf("\n");
  }
}


int main() {
  word *table[TABLE_LENGTH], *head;
  int h;
  initTable(table);
  insertInTable(table, "moises");
  insertInTable(table, "gabriel");
  insertInTable(table, "antonio");
  h = hash("moises");
  head = table[h];
  insertInList(&head, "gabriel");
  insertInList(&head, "antonio");
  showTable(table);
  return 0;
}