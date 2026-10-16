#ifndef _PREPARATION_QUEUE_NODE_HPP_
#define _PREPARATION_QUEUE_NODE_HPP_

#include "OrderHistory.hpp"

#define SIZE_DEFAULT 10

// Fila encadeada simples - FIFO — First In, First Out
class PreparationQueueNode
{
private:
    PreparationQueueNode* next;
    Order * orderPreparation;

public:
    PreparationQueueNode();
    void setOrder(Order * order);
    Order* getOrder();
    PreparationQueueNode* getNext() const;

    void setNext(PreparationQueueNode* next);
    
};

#endif