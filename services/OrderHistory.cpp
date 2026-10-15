#include "../models/OrderHistory.hpp"

OrderHistory::OrderHistory()
{
    this->previous = nullptr;
    this->next = nullptr;
}

void OrderHistory::setOrder(Order newOrder)
{
    this->order = newOrder;
}

void OrderHistory::setNext(OrderHistory* next)
{
    this->next = next;
}

void OrderHistory::setPrevious(OrderHistory* previous)
{
    this->previous = previous;
}

// possivelmente não presice desses metodos
OrderHistory* OrderHistory::getNext(){
    return this-> next;
}

OrderHistory* OrderHistory::getPrevious(){
    return this-> previous;
}

 Order OrderHistory::getOrder(){
    return this->order;
 }