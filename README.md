**16/03/203**

Encontrei dificuldades em alocar memoria dinamicamente para strings. 
primeiramente nem me dei conta de que deveria alocar memoria para uma cadeia, depois fiquei travado no código abaixo.
O codigo não funcionava pois estava colocando a função sizeof e esquecendo de colocar uma posição a mais para o caractere nulo.
char *string1;
```c
new->data = (char *) malloc(sizeof(strlen("string2")))
/* depois de muita dor de cabeça funcionou assim */
new->data = (char *) malloc(strlen("string2") + 1)
```
Esse código esta sendo usada para inserir uma palavra na lista, por causa desse erro achei que a logica da função de inserção estava errada, ou os ponteiros e perdi um tempo consideravel, mas acredito que foi válido pois eu realmente não sabia trabalhar dessa forma com strings.