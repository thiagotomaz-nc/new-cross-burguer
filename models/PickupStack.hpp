#ifndef _PICKUP_STACK_HPP
#define _PICKUP_STACK_HPP

#include "Order.hpp"

#define SIZE_DEFAULT 10
//Pilha encadeada simples
class PickupStack
{
private:
    PickupStack * top;
    int size;
    int length;

public:
    PickupStack(int size = SIZE_DEFAULT);
    void push(Order *Order);
    void pop(Order *order);
    void peek(Order *order);
    int isEmpty();
    int getSize();
    int setSize(int newSize);
    int setLength(int newLength);
    int getLength();
    ~PickupStack();
};



#endif