#ifndef _ORDER_HISTORY_HPP
#define _ORDER_HISTORY_HPP

#include "Order.hpp"

// Lista duplamente encadeada - historico do  dia
class OrderHistory
{
private:
    Order * data;
    OrderHistory *previous;
    OrderHistory *next;


public:
    OrderHistory(/* args */);
    void insertBegin(Order *order);
    void insertEnd(Order *order);
    void insertMiddle(Order *order);
    Order searchOrderNumber(int number);
    Order searchOrderClient(string nameClient);
    Order searchOrderEnd(int number);
    int removeOrder(int number);
    void showReport();
    int getSize();
    void setSize(int newSeize);
    int getLength();
    void setLength(int newLength);
    Order getNext();
    Order getPrevious();
    void setNext(Order *order);
    void setPrevious(Order *order);
    ~OrderHistory();
};

#endif