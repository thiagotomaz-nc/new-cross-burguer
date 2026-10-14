#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include "../enuns/enumStatusOrder.h"

#include "../models/Item.hpp"

using namespace std;

class Order
{
private:
    int numberOrder = 0;
    int numberTable;
    string nameClient;
    vector<Item> items; // marca qual o inicio do cabeça dos items; 
    double priceTotalToOrder = 0;
    int statusOrder; // 0 - CANCELADO, 1 - EM CONSTRUÇÃO, 2 - FECHADO, 3 - PRONTO

public:
    Order();

    void addItemToOrder(Item item);
    void removeItemFromOrder(int index);

    pair<bool, Item> getItemToIndex(int index);
 
    void sumTotalPriceToOrder();
    double getTotalPriceToOrder();
    int generateNumberOrder();

    
    void setNumberTable(int newNumberTable);
    int getNumberOrder();
    int getNumberTable();
    void setNameClient(string newNameClient);
    string getNameClient();
    void setStatusOrder(StatusOrder newStatusOrder);
    int getStatusOrder();

    void showResumeOrder();

    string statusToString(int status);
  
    ~Order();
};

#endif