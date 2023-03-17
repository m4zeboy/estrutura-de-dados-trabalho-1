## Dificuldades
**16/03/203**

Encontrei dificuldades em alocar memoria dinamicamente para 'strings'. 
Primeiramente nem me dei conta de que deveria alocar memória para uma cadeia, depois fiquei travado no código abaixo.
O codigo não funcionava, pois, eu colocava a função sizeof e esquecia de informar uma posição a mais para o caractere nulo: 

```c
new->data = (char *) malloc(sizeof(strlen("string2")))
/* depois de muita dor de cabeça funcionou assim */
new->data = (char *) malloc(strlen("string2") + 1)
```
Esse código é usado para inserir uma palavra na lista, por causa desse erro pensei que a lógica da função de inserção estava errada, ou os ponteiros e perdi um tempo consideravel, mas acredito que foi válido, pois eu realmente não sabia trabalhar dessa forma com 'strings'.

Também enrolei-me para liberar a memória de uma lista, eu esquecia de salvar o próximo nó da lista, e quando eu tentava reatribuir o nó atual ele não funcionava por que eu liberei ele, logo o programa não ia conseguir acessar para fazer a reatribuição.

- [x]  função de insere
    - [x] funçao hash
    - [x]criar nó
    - [x] inserir no na lista
    - [x] inserir na tabela
- [x] salvar dados em arquivo
- [x] carregar dados do arquivo
- [ ] função de busca
- [ ] função de remoção