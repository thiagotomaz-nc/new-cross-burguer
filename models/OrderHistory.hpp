#ifndef _ORDER_HISTORY_HPP
#define _ORDER_HISTORY_HPP

#include "Order.hpp"

// Lista duplamente encadeada - historico do  dia
class OrderHistory
{
private:
    Order order;
    OrderHistory *previous;
    OrderHistory *next;

public:
    OrderHistory();
    OrderHistory* getNext();
    OrderHistory* getPrevious();
    void setNext(OrderHistory* next);
    void setPrevious(OrderHistory* previous);
    void setOrder(Order newOrder);
    Order getOrder();
   
};

#endif