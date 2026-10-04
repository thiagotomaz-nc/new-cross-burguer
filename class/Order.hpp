#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <string>
#include "Item.hpp"

using namespace std;

class Order
{
private:
    int numberOrder = 0;
    int numberTable;
    string nameClient;
    // head que mostra onde inicia os items de um pedido;
    Item * headItems = nullptr; // marca qual o inicio do cabeça dos items; 
    double priceTotalToOrder = 0;
    // 0 - CANCELADO, 1 - EM CONSTRUÇÃO, 2 - FECHADO, 3 - PRONTO
    int statusOrder; 

public:
    Order(Item * newItem,int newNumberTable);
    Order();

    void addItemToOrder();
    void removeItemFromOrder();
    void sumTotalPriceToOrder();
    double getTotalPriceToOrder();
    int generateNumberOrder();

    void setNumberOrder(int numberOrder);
    void setNumberTable(int numberTable);
    int getNumberOrder();
    int getNumberTable();
  
    ~Order();
};

#endif