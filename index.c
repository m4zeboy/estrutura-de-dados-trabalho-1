#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_LENGTH 13

typedef struct word {
    char *data;
    struct word *next;
} word;

typedef struct list {
   word *head;
}list;

int power(int x, int n) {
  if(n == 0) {
    return 1;
  } else if (n == 1) {
    return x;
  } else
    return x * power(x, n - 1);
}

unsigned int hash(const char *str) {
  int i, k;
  long count;
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

void initTable(word *table[]) {
  int i;
  for (i = 0; i < TABLE_LENGTH; i++){
    table[i] = NULL;
  }
}

void showTable(word *table[]) {
  int i;
  for(i = 0; i < TABLE_LENGTH; i++) {
    printf("%x\n", table[i]);
  }
}

void showList(word *head) {
  while(head != NULL) {
    printf("%s - %x -> ", head->data, head->next);
    head = head->next;
  }
}

int main() {
  word *head = newWord("NOVA LISTA");
  insertInList(&head, "vilmar");
  insertInList(&head, "maria");
  insertInList(&head, "moises");
  insertInList(&head, "antonio");
  insertInList(&head, "gabriel");
  showList(head);
  return 0;
}