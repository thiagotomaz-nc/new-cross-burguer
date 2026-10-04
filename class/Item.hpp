#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include "Product.hpp"

#include <iostream>
using namespace std;

class Item{

    private:
        Product* product;// Ponteiro para o produto cadastrado e exibido no menu
        int quantity;   
        float priceTotalItems;
        Item * nextItem; // o endereço do proximo item;

    public:
        Item(Product* product, int quantity); // construtor geral
        Item(); // construtor vazio;
        Item(const Item& copyItem); // construtor de copia

        void setPriceTotalItem(int unitPrice);
        float getPriceTotalItem();
        Item * getNextItem();
        void setNextItem(Item * nextItem);

        int getQuantityItem();
        void setQuantityItem(int newQuantity);

        Product* getProductItem();
        void setProductItem(Product* newProduct);
};

#endif