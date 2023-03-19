## Dificuldades
**16/03/203**
Encontrei dificuldades em alocar memoria dinamicamente para 'strings'. 
Primeiramente nem me dei conta de que deveria alocar memória para uma cadeia, depois fiquei travado no código abaixo.
O código não funcionava, pois, eu colocava a função sizeof e esquecia de informar uma posição a mais para o carácter nulo: 
```c
new->data = (char *) malloc(sizeof(strlen("string2")))
/* depois de muita dor de cabeça funcionou assim */
new->data = (char *) malloc(strlen("string2") + 1)
```
Esse código é usado para inserir uma palavra na lista, por causa desse erro pensei que a lógica da função de inserção estava errada, ou os ponteiros e perdi um tempo considerável, mas acredito que foi válido, pois eu realmente não sabia trabalhar dessa forma com 'strings'.

Também enrolei-me para liberar a memória de uma lista, eu esquecia de salvar o próximo nó da lista, e quando eu tentava re-atribuir o nó atual ele não funcionava por que eu liberei ele, logo o programa não ia conseguir acessar para fazer a re-atribuição.

Tive dificuldade em como tratar a função remove, quando recebe uma entrada e quando recebe duas entradas, resolvi essa questão pesquisando na internet, onde encontrei sobre a função *fgets* e *sscanf*. créditos: ChatGPT;

## Problemas do programa
Se ao inserir um par de palavras (str1,str2) acontecer uma colisão com a str1, não será criada uma lista para a str1 e seus sinónimos, mas se no próximo passo da função, ao inserir o outro par (str2, str1) não acontecer nenhuma colisão, a lista será criada normalmente e a str1 estará presente como um sinonimo da str2.

- [x]  função de insere
    - [x] funçao hash
    - [x] criar nó 
    - [x] inserir no na lista
    - [x] inserir na tabela
- [x] salvar dados em arquivo
- [x] carregar dados do arquivo
- [x] função de busca
- [] função de remoção
    - [ ] se o sinonimo str2 a ser removido for o unico sinonimo da palavra str1, remover a lista str1 da estrutura.
- [ ] Relatório
    - [ ] Como estão estruturados os dados
    - [ ] Justificativa para o tamanho da tabela
    - [ ] Justificativa para a escolha da função de dispersão
    - [ ] Quais partes foram desenvolvidas com sucesso
    - [ ] Quais partes não funcionam
    - [ ] Principais dificuldades