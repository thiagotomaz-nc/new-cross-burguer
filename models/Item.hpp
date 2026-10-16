#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include "Product.hpp"
#include <utility>


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

        void setPriceTotalItem(float unitPrice);
        float getPriceTotalItem();
        
        int getQuantityItem();
        void setQuantityItem(int newQuantity);

        pair<bool, Product> getProductItem();
        void setProductItem(Product newProduct);

        void showItems(int numberItem);
    
};

#endif