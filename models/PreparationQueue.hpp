#ifndef _PREPARATION_QUEUE_HPP_
#define _PREPARATION_QUEUE_HPP_

#include "PreparationQueueNode.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class PreparationQueue
{
private:
    PreparationQueueNode* head;
    PreparationQueueNode* peek;
    int n_elements;

public:
    PreparationQueue();

    void enqueue(Order* PreparationQueue); // ponteiro
    void dequeue();
    int isEmpty();

    Order* getOrderPreparation();
    
    Order getPeek();
    // utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;

    void showQueuePreparation();

    ~PreparationQueue();
};
 
#endif