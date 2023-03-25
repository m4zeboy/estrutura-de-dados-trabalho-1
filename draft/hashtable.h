/******************************************************
*                                                     *
*   Moisés Silva de Azevedo                           *
*   RGA 2022.0743.004-6                               *
*   Implementação 1                                   *
*   Disciplina: Estruturas de Dados e Programacão I   *
*   Professor: Ronaldo Fiorilo                        *
*                                                     *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 977
#define STRING_SIZE 30
#define string char *

/* Estrutura para armazenar uma palavra */
typedef struct word {
  string data;
  struct word *next;
} word;

/* Dado x e n calcula o valor de x elevado a n */
int power(int x, int n) {
  if(n == 0) {
    return 1;
  } else if (n == 1) {
    return x;
  } else
    return x * power(x, n - 1);
}

/* Dado uma string, calcula o hash dessa string */
unsigned int hash(string str) {
  int i, k;
  unsigned long hash_value = 0;
  k = 13;
  for(i = 0; str[i] != '\0'; i++) {
    hash_value = hash_value + (str[i] * power(k, i));
  }
  return hash_value % TABLE_SIZE;
}

/* Aloca memória para a criação de uma palavra */
word *newWord(string data) {
  word *new = (string) malloc(sizeof(word));
  if(new) {
    new->data = (string) malloc(strlen(data) + 1);
    if(new->data) {
      strcpy(new->data, data);
    }
    new->next = NULL;
  }
  return new;
}

/* Recebe a cabeça de uma lista e uma chave e a insere na lista em ordem */
void insertInList(word **head, string data) {
  word *new = newWord(data);
  if(new) {
    word *p, *q;
    p = *head;
    q = (*head)->next;
    while(q && strcmp(data, q->data) > 0) {
      p = q;
      q = q->next;
    }
    /* insere se a palavra não for repetida */
    if(q == NULL || strcmp(data, q->data) != 0) {
      new->next = q;
      p->next = new;
    }
  }
}

/* Dado uma lista e uma palavra str, remove a palavra str da lista */
void removeFromList(word *head, string str) {
  word *p, *q;
  p = head;
  q = head->next;
  while(q && strcmp(q->data, str) != 0) {
    p = q;
    q = q->next;
  }
  p->next = q->next;
  free(q->data);
  free(q);
}

/* Recebe a cabeça de uma lista e calcula seu tamanho */
int listLength(word *head) {
  int count = 0;
  while(head) {
    count++;
    head = head->next;
  }
  return count;
}

/* Recebe o ponteiro de um struct word e libera sua memória */
void freeWord(word *word) {
  free(word->data);
  free(word);
}

/* Dada uma lista, libera a memoria de cada nó */
void freeList(word *head) {
  word *current;
  current = head;
  while(current) {
    word *next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
}

/* Inicializa todas as posições da tabela com o ponteiro NULL */
void initTable(word *table[]) {
  int i;
  for (i = 0; i < TABLE_SIZE; i++){
    table[i] = NULL;
  }
}

/* Recebe a tabela e uma chave e cria uma palavra nova e coloca na estrutura caso não aconteça colisões */
void insert(word *table[], string str1, string str2) {
  int index = hash(str1);
  word *head;
  if(table[index] == NULL) {
    /* a str1 não existe na estrutura */
    word *new = newWord(str1);
    table[index] = new;
    insertInList(&table[index], str2);
  } else if(strcmp(table[index]->data, str1) == 0) {
    /* a str1 já existe na estrutura */
    head = table[index];
    insertInList(&head, str2);
  } else {
    fprintf(stderr, "Erro: Nao foi possível inserir a palavra '%s' na estrutura devido a uma colisao.\n", str1);
  }
}

/* Conta quantas linhas da tabelas estão ocupadas */
int countNotEmptyRows(word *table[]) {
  int count, i;
  count = 0;
  for(i = 0; i < TABLE_SIZE; i++) {
    if(table[i] != NULL) {
      count++;
    }
  }
  return count;
}

/* Recebe a tabela de dispersão e salva seus dados em um arquivo */
void saveTableInFile(word *table[]) {
  FILE *file;
  file = fopen("words.txt","w");
  if(file) {
    int i;
    /* Imprime a quantidade de linhas usadas da tabela. Será usado posteriormente para a leitura correta */
    fprintf(file, "%d\n", countNotEmptyRows(table));
    for(i = 0; i < TABLE_SIZE; i++) {
      if(table[i]) {
        int list_length;
        word *temp = table[i];
        list_length = listLength(temp);
        /* Imprime o tamanho da lista atual será usado posteriormente para o programa fazer a leitura correta */
        fprintf(file,"%d\n", list_length);
        while(temp) {
          fprintf(file, "%s\n", temp->data);
          temp = temp->next;
        }
      }
    }
    fclose(file);
  }
}

/* Carrega os dados de um arquivo e armazena em uma tabela de dispersão */
void loadTableFromFile(word *table[]) {
  FILE *file;
  file = fopen("words.txt", "r");
  if(file) {
    int count_not_empty_rows, i;
    fscanf(file, "%d\n", &count_not_empty_rows);
    for (i = 0; i < count_not_empty_rows; i++) {
      int list_length, j;
      fscanf(file,"%d\n", &list_length);
      for(j = 0; j < list_length; j++) {
        int index;
        char str[STRING_SIZE];
        fscanf(file, "%s\n", str);
        if(j == 0) {
          /* É a cabeça da lista, a palavra chave */
          word *head;
          head = newWord(str);
          index = hash(str);
          table[index] = head;
        } else {
          insertInList(&table[index], str);
        }

      }
    }
    fclose(file);
  } else {
    fprintf(stderr, "Erro ao abriro o arquivo 'words.txt'.\n");
  }
}

/* Percorre as linhas da tabela e se estiver vazia, libera a memória da lista que está alocada na respectiva posição */
void freeTable(word *table[]) {
  int i;
  for(i = 0; i < TABLE_SIZE; i++) {
    if(table[i] != NULL) {
      freeList(table[i]);
    }
  }
}

/* Recebe uma palavra e verifica se ela se encontra na estrutura, se sim mostra seus sinonimos um em cada linha */
void search(word *table[], string str) {
    int index;
    index = hash(str);
    if(table[index] != NULL && strcmp(str, table[index]->data) == 0) {
      word *iterator = table[index]->next;
      while(iterator) {
        printf("%s\n", iterator->data);
        iterator = iterator->next;
      }
    } else {
      printf("hein?\n");
    }
}

/* 
  Dado uma palavra str exclui ela e sua lista de sinônimos da estrutura, 
  mas não exclui a palavra str como sinonimo em outras listas 
*/
void removeFromTable(word *table[], string str) {
  int index;
  word *head;
  index = hash(str);
  head = table[index];
  freeList(head);
  table[index] = NULL;
}