#include "models/Order.hpp"

Order::Order(Item * newItem, int newNumberTable){ // inserindo itens no final
    if (newItem!=nullptr){
        // passo o valor do ponteiro newItem par ao construtor de copia, 
        // que cria uma copia em outro endereço baseado nos valores de newItem;
        // vantagem, não precisa fazer uso do set no item e dos get no newItem
        Item * item = new Item(*newItem); 
        this->numberOrder = generateNumberOrder();
        this->numberTable=newNumberTable;
        sumTotalPriceToOrder(); // atualiza o preço total de acordo com os items cadastrados no pedido
        this->priceTotalToOrder=getTotalPriceToOrder(); // deve ser chamado por função
        this->statusOrder=1; // inicialmente, em construção;
        this->nameClient = "avulso"; // nome padrão do cliente
        
        if (this->headItems==nullptr){
            // item já é um ponteiro que aponta para o endereço que contem as informações dos itens;
            // então o head deve apontar para o mesmo endereço apontando o inicio da lista;
            this->headItems = item;
        }else{
            Item * aux = this->headItems;
            
            while (aux->getNextItem() != nullptr){
                aux = aux->getNextItem();
            }

            aux->setNextItem(item);
        }
    }
}

Order::Order(){}

int Order::generateNumberOrder(){
    return this->numberOrder+1;
}
    
void Order::addItemToOrder(){}// ver estrutura

void Order::removeItemFromOrder(){} // ver estrutura

void Order::sumTotalPriceToOrder(){
    
    Item * aux = this->headItems;
    
    double sumPriceTotal = 0.0;

    while (aux!=nullptr){
        sumPriceTotal += aux->getPriceTotalItem();   
        aux = aux->getNextItem();
    };
    
    this->priceTotalToOrder = sumPriceTotal;

}

double Order::getTotalPriceToOrder(){
    return this->priceTotalToOrder;
}

Order::~Order(){}