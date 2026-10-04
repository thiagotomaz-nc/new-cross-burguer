#include "Item.hpp"

Item::Item(Product* product, int quantity) {
    this->product = product;
    this->quantity = quantity;
    this->priceTotalItems = this->product->getUnitPrice() * quantity;
}

Item::Item(){}

//O const está protegendo apenas o objeto original (other) durante a cópia.
Item::Item(const Item& copyItem){
    this->product = copyItem.product;
    this->quantity = copyItem.quantity;
    this->priceTotalItems = copyItem.product->getUnitPrice() * copyItem.quantity;
}

void Item::setPriceTotalItem(int unitPrice) {
    if (this->product != nullptr && unitPrice > 0) {
        this->priceTotalItems = getQuantityItem() * unitPrice;
    } else {
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<< "Total preco nao alterado. Verifique se o valor é negativo ou se esqueceu de intormar o produto e tente novmente!"<<endl;       
        cout<<"---------------------------------------------------------\n"<<endl;
    }
}

float Item::getPriceTotalItem() {
    return this->priceTotalItems;
}

int Item::getQuantityItem() {
    return this->quantity;
}

Item * Item::getNextItem(){
    return this->nextItem;
}

void Item::setQuantityItem(int newQuantity) {
    if (newQuantity > 0 ){
        this->quantity = newQuantity;
        this->setPriceTotalItem(this->product->getUnitPrice());  
    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<< "["<< newQuantity<<"] valor negativo invalido. Tente novmente!"<<endl;       
        cout<<"---------------------------------------------------------\n"<<endl;
    }
     // Recalcula o total ao alterar a quantidade
}

Product* Item::getProductItem() { // retorn o produto adicionado ao item
    return this->product;
}

void Item::setNextItem(Item * nextItem){
    this->nextItem = nextItem;
}


void Item::setProductItem(Product* newProduct) { // tualiza o produto adicionado ao item;
    // preciso reiniciar todas as informçlões
    if (newProduct != nullptr) {
        this->product = newProduct;
        Item(product, 1);   // Recalcula o total ao alterar o produto
    }
}