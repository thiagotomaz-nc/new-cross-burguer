#ifndef _PICKUP_STACK_HPP
#define _PICKUP_STACK_HPP

#include "Order.hpp"

#define SIZE_DEFAULT 10
// Pilha encadeada simples
class PickupStack
{
private:
    Order * orderPickupStack;
    PickupStack *next;

public:

    PickupStack();

    void orderInPickupStack(Order * order);
    void setNext(PickupStack *newNext);
    PickupStack* getNext();

    Order* getOrder();  

    ~PickupStack();
};

#endif