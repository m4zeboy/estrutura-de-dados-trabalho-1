/******************************************************
*                                                     *
*   Moisés Silva de Azevedo                           *
*   RGA 2022.0743.004-6                               *
*   Implementação 1                                   *
*   Disciplina: Estruturas de Dados e Programacão I   *
*   Professor: Ronaldo Fiorilo *                      *
*                                                     *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main() {
  word *table[TABLE_SIZE];
  char input[200], op[STRING_SIZE], str1[STRING_SIZE], str2[STRING_SIZE];             
  initTable(table);
  loadTableFromFile(table);
  do {
    int inputCount;
    fgets(input, sizeof(input), stdin);
    inputCount = sscanf(input, "%s %s %s", op, str1, str2);
    if(strcmp(op, "insere") == 0) {
      /* Insere o primeiro par - cria uma lista para a str1 e adiciona str2 como sinonimo */
      insert(table, str1, str2);
      /* Insere o segundo par - cria uma lista para a str2 e adiciona str1 como sinonimo */
      insert(table, str2, str1);
    } else if(strcmp(op, "busca") == 0) {
      search(table, str1);
    } else if(strcmp(op,"remove") == 0) {
      if(inputCount == 2) {
        /* Remover a palavra str1 e sua lista de sinonimos da estrutura */
        removeFromTable(table, str1);
      } else if(inputCount == 3) {
        /* Remover str2 da lista de sinonimos de str1, e remover str1 da lista de sinonimos de str2 */
        int index = hash(str1);
        removeFromList(table[index], str2);
        /* Verifica se a palavra não tem mais sinonimos associados a ela para excluir da tabela */
        if(table[index]->next == NULL) {
          word *trash = table[index];
          table[index] = NULL;
          free(trash);
        }
      } 
    } else if(strcmp(op, "fim") == 0) {
      break;
    }
  } while(strcmp(op ,"fim") != 0);
  saveTableInFile(table);
  freeTable(table);
  return 0;
}