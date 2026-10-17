#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

#include "../enuns/enumStatusOrder.h"

#include "../models/Item.hpp"

using namespace std;

#define DECIMAL_PLACES_ORDER 5

class Order
{
private:
    int numberOrder = 0;
    int numberTable;
    string nameClient;
    vector<Item> items; // marca qual o inicio do cabeça dos items;
    double priceTotalToOrder = 0;
    StatusOrder statusOrder; // 0 - CANCELADO, 1 - EM CONSTRUÇÃO, 2 - FECHADO, 3 - PRONTO

public:
    Order();

    // Construtor de cópia, para quando se cria o objeto e passa o novo objeto na criação
    // ex: Order pedido1;
    //  Order pedido2 = pedido1;
    Order(const Order &other);

    // Operador de atribuição por cópia
    // Order pedido3;
    // pedido3 = pedido1;
    Order &operator=(const Order &) = default;

    void addItemToOrder(Item item);
    void removeItemFromOrder(int index);

    pair<bool, Item> getItemToIndex(int index);

    void sumTotalPriceToOrder();
    double getTotalPriceToOrder();
    int setNumberOrder(int newNumberOrder);

    void setNumberTable(int newNumberTable);
    int getNumberOrder();
    int getNumberTable();
    void setNameClient(string newNameClient);
    string getNameClient();
    void setStatusOrder(StatusOrder newStatusOrder);
    StatusOrder getStatusOrder();

    int findItemIndexByBarCode(int barCode); // Retorna o índice do item no vetor do pedido ou -1 se não existir

    void showResumeOrder();

    string statusToString(StatusOrder status);

    ~Order();
};

#endif