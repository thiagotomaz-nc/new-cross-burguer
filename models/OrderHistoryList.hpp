#ifndef _ORDER_HISTORY_LIST_HPP
#define _ORDER_HISTORY_LIST_HPP

#include "OrderHistory.hpp"

// Manipular a lista duplamente encadeada
class OrderHistoryList
{
private:
    OrderHistory * orderHistory;
    OrderHistory *head;
    OrderHistory *tail;

public:
    OrderHistoryList();
    void removeOrder(int number);
    OrderHistory* gethead() const;
    OrderHistory* getTail() const;
    void showReportAll();
    int getSize();
    void insertBegin(Order newOrder);
    void insertEnd(Order newOrder);
    void insertMiddle(Order newOrder); // fica para o final
    pair<bool, Order>searchOrderIndexNumber(int number);
    pair<bool, Order> searchOrderClient(string nameClient);
    pair<bool, Order> searchOrderEndNumber(int number);
    void updateOrder(Order newOrder);

    ~OrderHistoryList();
};

#endif