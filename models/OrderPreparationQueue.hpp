#ifndef _ORDER_PREPARATION_QUEUE_HPP_
#define _ORDER_PREPARATION_QUEUE_HPP_

#include "PreparationQueue.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class OrderPreparationQueue
{
private:
    PreparationQueue * head;
    int n_elements;

public:
    OrderPreparationQueue();

    void enqueue(Order* orderInHistory);
    void dequeue();
    bool dequeueOrderNumber(int orderNumber);
    bool isEmpty();

    void displayMessage(string displayMessage);

    Order* getOrderPreparation();
    Order getPeek();

    void showQueuePreparation();

    ~OrderPreparationQueue();
};
 
#endif