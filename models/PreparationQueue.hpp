#ifndef _PREPARATION_QUEUE_HPP_
#define _PREPARATION_QUEUE_HPP_

#include "Order.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class PreparationQueue
{
private:
    Order* data;
    PreparationQueue* next;

public:
    PreparationQueue();

    void enqueue(Order * order); // ponteiro ou não
    void dequeue();
    int isEmpty();
    
    Order* peek();
    // utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;
    // protegendo a estrutura;

    ~PreparationQueue();
};

#endif