#ifndef _ORDER_HISTORY_LIST_HPP
#define _ORDER_HISTORY_LIST_HPP

#include "OrderHistory.hpp"

// Manipular a lista duplamente encadeada
class OrderHistoryList
{
private:
    OrderHistory *head;
    OrderHistory *tail;

public:
    OrderHistoryList();
    int removeOrder(int number);
    OrderHistory* gethead() const;
    OrderHistory* getTail() const;
    void showReportAll();
    int getSize();
    void insertBegin(Order newOrder);
    void insertEnd(Order newOrder);
    void insertMiddle(Order *newOrder); // fica para o final
    pair<bool, OrderHistory> searchOrderNumber(int number);
    pair<bool, OrderHistory> searchOrderClient(string nameClient);
    pair<bool, OrderHistory> searchOrderEnd(int number);
    ~OrderHistoryList();
};

#endif