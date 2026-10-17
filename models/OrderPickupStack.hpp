#ifndef _ORDER_PICKUP_STACK_HPP_
#define _ORDER_PICKUP_STACK_HPP_

#include "../models/PickupStack.hpp"

class OrderPickupStack
{
private:
    PickupStack * pickupStack;
    PickupStack * head;
    PickupStack * top;
    int size;

public:
    OrderPickupStack(/* args */);

    void push(Order *order);
    void pop();
    Order peek();
    
    bool isEmpty();
    int getSize();

    void printReadyOrders();

    ~OrderPickupStack();
};

#endif