#include "../models/OrderHistory.hpp"

OrderHistory::OrderHistory(const Order &st):order(st)
{
    
    this->previous = nullptr;
    this->next = nullptr;
}


void OrderHistory::setOrder(Order newOrder)
{
    this->order = newOrder;
}

void OrderHistory::setNext(OrderHistory *next)
{
    this->next = next;
}

void OrderHistory::setPrevious(OrderHistory *previous)
{
    this->previous = previous;
}

// possivelmente não presice desses metodos
OrderHistory *OrderHistory::getNext()
{
    return this->next;
}

OrderHistory *OrderHistory::getPrevious()
{
    return this->previous;
}

Order OrderHistory::getOrder()
{
    return this->order;
}

Order *OrderHistory::getOrderPointer()
{
    return &this->order;
}

OrderHistory::~OrderHistory()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "Pedido [ " << this->getOrder().getNumberOrder() << " ] removido do historico com sucesso!" << "\n";
    cout << "---------------------------------------------------------\n\n";
}
