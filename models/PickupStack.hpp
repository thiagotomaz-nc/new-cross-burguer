#ifndef _PICKUP_STACK_HPP
#define _PICKUP_STACK_HPP

#include "Order.hpp"
#include "PickupStackNode.hpp"

class PickupStack
{
private:
    PickupStackNode *top;   // Aponta para o nó no topo da pilha
    int length;             // Quantidade atual de elementos

public:
    PickupStack();
    
    void push(Order *order);
    Order* pop();
    Order* peek();
    
    int isEmpty();
    int getLength();
    
    ~PickupStack();
};

#endif