#ifndef _PREPARATION_QUEUE_HPP_
#define _PREPARATION_QUEUE_HPP_

#include "Order.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class PreparationQueue
{
private:
    PreparationQueue * next;
    Order * orderPreparation;  

public:
    PreparationQueue();
    void setOrder(Order * order);
    
    Order* getOrder();

    PreparationQueue* getNext() const;

    void setNext(PreparationQueue* next);
    
};

#endif