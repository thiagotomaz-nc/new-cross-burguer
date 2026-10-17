#ifndef _ORDER_REPARATION_QUEUE_HPP_
#define _ORDER__PREPARATION_QUEUE_HPP_

#include "PreparationQueue.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class OrderPreparationQueue
{
private:
    PreparationQueue * preparationQueue;
    PreparationQueue * head;
    int n_elements;

public:
    OrderPreparationQueue();

    void enqueue(Order* PreparationQueue); // ponteiro
    void dequeue();
    bool isEmpty();

    void displayMessage(string displayMessage);

    Order* getOrderPreparation();
    
    Order getPeek();
    // utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;

    void showQueuePreparation();

    ~OrderPreparationQueue();
};
 
#endif