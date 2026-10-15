#include "../models/OrderHistoryList.hpp"

OrderHistoryList::OrderHistoryList()
{
    this->head = nullptr;
    this->tail = nullptr;
}

void OrderHistoryList::insertBegin(Order newOrder)
{
    OrderHistory *orderHistory = new OrderHistory();
    orderHistory->setOrder(newOrder);

    // Adiciona o primeiro elemento na lista de historico;
    if (this->head == nullptr)
    {
        this->head = orderHistory;
        orderHistory->setNext(this->head);
        orderHistory->setPrevious(this->head);
        return;
    }
    else
    {

        // alterar o proximo e o anterior do OrderHistory
        orderHistory->setNext(this->head);
        orderHistory->setPrevious(this->head->getNext());

        this->head->setPrevious(orderHistory);
        OrderHistory *aux = this->head;

        while (aux->getNext() != this->head)
        {
            aux = aux->getNext();
        }

        aux->setNext(orderHistory);
        this->head = orderHistory;

        return;
    }
}

void OrderHistoryList::insertEnd(Order newOrder)
{
    OrderHistory *orderHistory = new OrderHistory();
    orderHistory->setOrder(newOrder);

    if (this->head == nullptr)
    {
        this->head = orderHistory;
        orderHistory->setNext(this->head);
        orderHistory->setPrevious(this->head);
        return;
    }
    else
    {

        // alterar o proximo e o anterior do OrderHistory
        orderHistory->setNext(this->head);

        OrderHistory *aux = this->head;

        while (aux->getNext() != this->head)
        {
            aux = aux->getNext();
        }

        orderHistory->setPrevious(aux);
        aux->setNext(orderHistory);

        return;
    }
}

int OrderHistoryList::getSize()
{
    OrderHistory *aux = this->head;
    int count = 0;

    while (aux != this->head)
    {
        count++;
        aux = aux->getNext();
    }

    return count;
}

void OrderHistoryList::showReport()
{
}

pair<bool, OrderHistory> OrderHistoryList::searchOrderNumber(int number)
{

    OrderHistory *aux = this->head;

    while (aux != this->head)
    {


        if (aux->getOrder().getNumberOrder() == number)
        {
            return {true, *aux};
            break;
        }
        aux = aux->getNext();
    }

    return {false, OrderHistory{}};
}

pair<bool, OrderHistory> OrderHistoryList::searchOrderEnd(int number)
{

    OrderHistory *aux = this->tail;

    while (aux != this->tail)
    {
      

        if (aux->getOrder().getNumberOrder() == number)
        {
            return {true, *aux};
            break;
        }
        aux = aux->getPrevious();
    }

    return {false, OrderHistory{}};
}

pair<bool, OrderHistory> OrderHistoryList::searchOrderClient(string nameClient)
{
    OrderHistory *aux = this->head;
   
    while (aux != this->head)
    {

        if (aux->getOrder().getNameClient() == nameClient)
        {
            return {true, *aux};
            break;
        }
        aux = aux->getNext();
    }

    return {false, OrderHistory{}};
}

OrderHistoryList::~OrderHistoryList(){

}


 int OrderHistoryList::removeOrder(int number){

   OrderHistory* orderRemove =  this->head;


    while (orderRemove != this->head)
    {
        if (orderRemove->getOrder().getNumberOrder() == number)
        {
            break;
        }
        orderRemove = orderRemove->getNext();
    }

    if (orderRemove != this->head){
        // utilizar um ponteiro;
        // atualizar o proximo e o antecessor
        orderRemove->getNext()->getPrevious()->setPrevious(orderRemove->getPrevious());
        orderRemove->getPrevious()->getNext()->setNext(orderRemove->getNext());

        // deletar o objeto
        delete orderRemove;
    }else{
        cout<<"Pedido não esta no histórico";
    }

 }