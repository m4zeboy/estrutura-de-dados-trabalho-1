#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int main(void) {
  Node *table[SIZE];
  initTable(table);

  read(table);
  insertInTable(table, "comida", "alface");
  insertInTable(table, "alface", "comida");
  showTable(table);


  save(table);
  return 0;
}