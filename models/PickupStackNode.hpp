#ifndef _PICKUP_STACK_NODE_HPP
#define _PICKUP_STACK_NODE_HPP

#include "Order.hpp"

class PickupStackNode {
private:
    Order *order;             // Ponteiro para o pedido guardado no nó
    PickupStackNode *next;    // Ponteiro para o nó que está abaixo na pilha

public:
    PickupStackNode();
    PickupStackNode(Order *order);

    Order* getOrder();
    void setOrder(Order *order);

    PickupStackNode* getNext() const;
    void setNext(PickupStackNode *next);

    ~PickupStackNode();
};

#endif