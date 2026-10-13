#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include "Product.hpp"

#include <iostream>
using namespace std;

// uma classe que representa um nó de produtos;
// representa um nó de uma lista encadeada de produto
class Item{

    private:
        Product product;// Ponteiro para o produto cadastrado e exibido no menu
        int quantity;   
        float priceTotalItems;
        

    public:
        Item(); // construtor vazio;
        // Item(const Item& copyItem); // construtor de copia

        void setPriceTotalItem(int unitPrice);
        float getPriceTotalItem();
        void setNextItem(Item * nextItem);

        int getQuantityItem();
        void setQuantityItem(int newQuantity);

        Product getProductItem();
        void setProductItem(Product newProduct);
};

#endif