Associar o produto com o nó de itens;

produto passa a ser uma lista ordenada;
 um codgigo para cada tipo
 1. bebidas
 2. pizzas
 3. acompanhamentos 
 4. Hambuguer

cuidado com o acesso a estrutura;
 1. utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;
 2. protegendo a estrutura;

status dos pedidos
Valores para fechar pedido = ENUM;
0 - CANCELADO, 1 - EM CONSTRUÇÃO, 2 - FECHADO, 3 - PRONTO


Criar o arquivo na pasta output:
mkdir -p output && g++ -Wall -Wextra -g3 -I. main.cpp services/*.cpp -o output/main && ./output/main

Rodar o arquivo na pasta output, se não houve alteração no código:
./output/main