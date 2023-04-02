#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int main(void) {
  Node *table[SIZE];
  char input[73], op[12], word[30], synonym[30];
  initTable(table);
  read(table);
  do {
    int inputCount;
    fgets(input, sizeof(input), stdin);
    inputCount = sscanf(input, "%s %s %s", op, word, synonym);
    if(strcmp(op, "insere") == 0) {
      /* Insere o primeiro par - cria uma lista para a word e adiciona synonym como sinonimo */
      insertInTable(table, word, synonym);
      /* Insere o segundo par - cria uma lista para a synonym e adiciona word como sinonimo */
      insertInTable(table, synonym, word);
    } else if(strcmp(op, "busca") == 0) {
      search(table, word);
    } else if(strcmp(op,"remove") == 0) {
      if(inputCount == 2) {
        /* Remover a palavra str1 e sua lista de sinonimos da estrutura */
        int index = hash(word);
        if(table[index] == NULL) {
          printf("hein?\n");
        } else {
          deleteNode(&(table[index]), word);
        }
      } else if(inputCount == 3) {
        /* Remover str2 da lista de sinonimos de str1, e remover str1 da lista de sinonimos de str2 */
        int index;
        Node *previous, *current, *trash;
        index = hash(word);
        previous = NULL;
        current = table[index];
        while(current && strcmp(current->word, word) != 0) {
          previous = current;
          current = current->next;
        };
        if(current) {
          deleteSynonym(&(current->list), synonym);
          if(current->list == NULL) {
          if(previous == NULL) {
            trash = current;
            table[index] = current->next;
            free(trash->word);
            free(trash);
          } else {
            trash = current;
            previous->next = current->next;
            free(trash->word);
            free(trash);
          }
        }
        } else {
          printf("hein?\n");
        }
      
      } 
    } else if(strcmp(op, "fim") == 0) {
      break;
    }
  } while(strcmp(op ,"fim") != 0);


  save(table);
  freeTable(table);
  return 0;
}