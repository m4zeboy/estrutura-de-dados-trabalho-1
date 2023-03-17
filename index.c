#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_LENGTH 10

/* Estrutura para armazenar uma palavra */
typedef struct word {
    char *data;
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
unsigned int hash(char *str) {
  int i, k;
  unsigned int count = 0;
  k = 13;
  for(i = 0; str[i] != '\0'; i++) {
    count = count + (str[i] * power(k, i));
  }
  return count % TABLE_LENGTH;
}

/* Aloca memória para a criação de uma palavra */
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

/* Recebe a cabeça de uma lista e uma chave e a insere na lista em ordem */
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

/* Recebe a cabeça de uma lista e imprime na tela seus dados */
void showList(word *head) {
  while(head != NULL) {
    printf("%s - %x -> ", head->data, head->next);
    head = head->next;
  }
}

/* Inicializa todas as posições da tabela com o ponteiro NULL */
void initTable(word *table[]) {
  int i;
  for (i = 0; i < TABLE_LENGTH; i++){
    table[i] = NULL;
  }
}

/* Recebe a tabela e uma chave e cria uma palavra nova e coloca na estrutura caso não aconteça colisões */
void insertInTable(word *table[], char *data) {
  int index = hash(data);
  if(table[index] == NULL) {
    word *head = newWord(data);
    if(head) {
      table[index] = head;
    }
  } else {
    insertInList(&table[index], data);
  }
}

/* Conta quantas linhas da tabelas estão ocupadas */
int countNotEmptyRows(word *table[]) {
  int count, i;
  count = 0;
  for(i = 0; i < TABLE_LENGTH; i++) {
    if(table[i] != NULL) {
      count++;
    }
  }
  return count;
}

/* Imprime a tabela */
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

/* Recebe a cabeça de uma lista e calcula seu tamanho */
int listLength(word *head) {
  int count = 0;
  while(head) {
    count++;
    head = head->next;
  }
  return count;
}

/* Recebe a tabela de dispersão e salva seus dados em um arquivo */
void saveTableInFile(word *table[]) {
  FILE *file;
  file = fopen("words.csv","w");
  if(file) {
    int i;
    fprintf(file, "%d\n", countNotEmptyRows(table));
    for(i = 0; i < TABLE_LENGTH; i++) {
      if(table[i]) {
        int list_length;
        word *temp = table[i];
        list_length = listLength(temp);
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
  file = fopen("words.csv", "r");
  if(file) {
    int count_not_empty_rows, i;
    fscanf(file, "%d\n", &count_not_empty_rows);
    for(i = 0; i < count_not_empty_rows; i++) {
      int list_length, j;
      fscanf(file, "%d\n", &list_length);
      for(j = 0; j < list_length; j++) {
        char data[20];
        fscanf(file, "%s\n", data);
        insertInTable(table, data);
      }
    }
    fclose(file);
  } else {
    fprintf(stderr, "Can't open the file 'words.csv'.\n");
  }
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

/* Percorre as linhas da tabela e se estiver vazia, libera a memória da lista que está alocada na respectiva posição */
void freeTable(word *table[]) {
  int i;
  for(i = 0; i < TABLE_LENGTH; i++) {
    if(table[i] != NULL) {
      freeList(table[i]);
    }
  }
}

int main() {
  word *table[TABLE_LENGTH];
  char op[10], str1[20], str2[20];
  initTable(table);
  loadTableFromFile(table);
  do {
    scanf("%s", op);
    if(strcmp(op, "insere") == 0) {
      /* Operação de inserção */
      scanf(" %s %s", str1, str2);
      printf("%s %s\n");
    }
    if(strcmp(op, "busca") == 0) {
      /* Operação de busca */
    }
  } while(strcmp(op ,"fim") != 0);
  freeTable(table);
  return 0;
}