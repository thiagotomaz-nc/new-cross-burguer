#include "../models/PickupStack.hpp"

PickupStack::PickupStack()
{
    this->next = nullptr;
}


void PickupStack::orderInPickupStack(Order * order){
    this->orderPickupStack = order;
}

void PickupStack::setNext(PickupStack *newNext){
    this->next = newNext;
}

PickupStack *PickupStack::getNext()
{
    return this->next;
}

Order *PickupStack::getOrder()
{
    return this->orderPickupStack;
}

PickupStack::~PickupStack()
{
}