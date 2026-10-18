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

    bool removeOrder(int number);
    bool cancelOrder(int orderNumber);

    OrderHistory* gethead() const;
    OrderHistory* getTail() const;
    void showReportAll();

    int getSize();
    bool isEmpty();

    void insertBegin(Order newOrder);
    void insertEnd(Order newOrder);
    void insertMiddle(Order newOrder); // fica para o final
    
    pair<bool, Order> searchOrderIndexNumber(int number);
    pair<bool, Order> searchOrderClient(string nameClient);
    pair<bool, Order> searchOrderEndNumber(int number);


    ~OrderHistoryList();
};

#endif