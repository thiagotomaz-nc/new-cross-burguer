#include "../models/Order.hpp"

Order::Order() {
    this->statusOrder = static_cast<int>(StatusOrder::EM_CONSTRUCAO);
}

void Order::addItemToOrder(Item item)
{
    this->items.push_back(item);
}

void Order::removeItemFromOrder(int index)
{
    if (index > 0 && index < this->items.size())
    {
        // Apaga o produto do vetor usando o iterador
        this->items.erase(items.begin() + index);
        // adicionar a pilha de ações;
    }
}

// optional armazena o objeto diretamente quando existe
pair<bool, Item> Order::getItemToIndex(int index)
{
    if (index > 0 && index < this->items.size())
    {
        return {true, this->items[index]};
    }
    return {false, Item{}};
}

void Order::sumTotalPriceToOrder()
{
    double sumPriceTotal = 0.0;
    // size_t é um tipo inteiro sem sinal
    for (size_t i = 0; i < this->items.size(); i++)
    {
        sumPriceTotal += this->items[i].getPriceTotalItem();
    };

    this->priceTotalToOrder = sumPriceTotal;
}

double Order::getTotalPriceToOrder()
{
    return this->priceTotalToOrder;
}

int Order::setNumberOrder(int newNumberOrder)
{
    return this->numberOrder = newNumberOrder + 1;

}

void Order::setNumberTable(int newNumberTable)
{
    this->numberTable = newNumberTable;
}

int Order::getNumberOrder()
{
    return this->numberOrder;
}

int Order::getNumberTable()
{
    return this->numberTable;
}

void Order::setNameClient(string newNameClient){
    this->nameClient = newNameClient;
}

string Order::getNameClient(){
    if (this->nameClient.empty()){
        return "Cliente Avulso";
    }
    return this->nameClient;
}

void Order::setStatusOrder(StatusOrder newStatusOrder){
    int status = static_cast<int>(newStatusOrder);
    if (status > 0){
        this->statusOrder = status;
    }else{
        this->statusOrder=1;
    }
}

int Order::getStatusOrder(){
    return this->statusOrder;
}

string Order::statusToString(int status)
{
    switch (status)
    {
    case 0:
        return "CANCELADO";
        break;
    case 1:
        return "EM_CONSTRUCAO";
        break;
    case 2:
        return "FECHADO";
        break;
    case 3:
        return "PRONTO";
        break;
    default:
        return "status não encontrado";
        break;
    }
}


void Order::showResumeOrder()
{

    cout << this->numberOrder << " | " << this->numberTable << " | " << this->nameClient << endl;
    cout << "\nEtapa do pedido: " << statusToString(this->statusOrder) << endl;
    cout << "\nitens do pedido: " << endl;

    if (this->items.size() > 0)
    {
       
        for (size_t i = 0; i < this->items.size(); i++)
        {

            Product Product = this->items[i].getProductItem().second;

            cout << i + 1 << "  " << Product.getName() << "  "
                 << Product.getUnitPrice() << " x " << this->items[i].getQuantityItem() << " = "
                 << this->items[i].getPriceTotalItem() << endl;
        }

        cout << "\nTotal do pedido:  R$ " << this->priceTotalToOrder << endl;
        cout << "-------------------------------------------" << endl;

    }
    else
    {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "Nenhum item adicionado." << endl;
        cout << "---------------------------------------------------------\n"
             << endl;
    }
}

Order::~Order() {}

