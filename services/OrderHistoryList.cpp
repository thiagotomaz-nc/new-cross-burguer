#include "../models/OrderHistoryList.hpp"

OrderHistoryList::OrderHistoryList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->orderHistory = nullptr;
}

void OrderHistoryList::insertBegin(Order newOrder)
{
    this->orderHistory = new OrderHistory(newOrder);

    // Adiciona o primeiro elemento na lista de historico;
    if (this->head == nullptr)
    {
        this->head = orderHistory;
        this->tail = this->head;
        this->orderHistory->setNext(nullptr);
        this->orderHistory->setPrevious(nullptr);
        return;
    }
    else
    {

        // alterar o proximo e o anterior do OrderHistory
        orderHistory->setNext(this->head);
        orderHistory->setPrevious(nullptr);

        this->head->setPrevious(orderHistory);

        OrderHistory *aux = this->head;

        while (aux->getNext() != nullptr)
        {
            aux = aux->getNext();
        }

        aux->setNext(nullptr);
        this->tail = aux;
        this->head = orderHistory;

        return;
    }
}

void OrderHistoryList::insertEnd(Order newOrder)
{
    this->orderHistory = new OrderHistory(newOrder);

    if (this->head == nullptr)
    {
        this->head = this->orderHistory;
        this->tail = this->head;
        this->orderHistory->setNext(nullptr);
        this->orderHistory->setPrevious(nullptr);
        return;
    }
    else
    {

        // apontar o ultimo ponteiro para o inicio;
        this->orderHistory->setNext(nullptr);

        OrderHistory *aux = this->head;

        while (aux->getNext() != nullptr)
        {
            aux = aux->getNext();
        }

        // apontar o primeiro para o ultimo elemento;
        this->orderHistory->setPrevious(aux);
        aux->setNext(this->orderHistory);
        this->tail = this->orderHistory;

        return;
    }
}

int OrderHistoryList::getSize()
{
    OrderHistory *aux = this->head;

    int count = 0;

    while (aux != nullptr)
    {
        count++;
        aux = aux->getNext();
    }

    return count;
}

void OrderHistoryList::showReportAll()
{
    if (this->head == nullptr)
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "Historico vazio!" << "\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
        return;
    }

    OrderHistory *aux = this->head;
    double totalSold = 0.0;

    

    do
    {
        // Garante que o nó atual é válido antes de acessar os dados
        if (aux == nullptr)
        {
            break;
        }

        Order tempOrder = aux->getOrder();
        tempOrder.sumTotalPriceToOrder();
        tempOrder.showResumeOrder();

        totalSold += tempOrder.getTotalPriceToOrder();

        // Avança para o próximo nó
        aux = aux->getNext();

    } while (aux != nullptr && aux != this->head); // Proteção contra ponteiros nulos

    cout << "--------------------------------------------" << endl;
    cout << "Valor total vendido : R$ " << totalSold << endl;
    cout << "Quantidade de pedidos: " << getSize() << endl;
    cout << "--------------------------------------------" << endl;
}

bool OrderHistoryList::isEmpty()
{
    return this->head == nullptr;
}

pair<bool, Order> OrderHistoryList::searchOrderIndexNumber(int number)
{

    OrderHistory *aux = this->head;

    while (aux != nullptr)
    {
        if (aux->getOrder().getNumberOrder() == number)
        {
            
            return {true, aux->getOrder()};
        }
        aux = aux->getNext();
    }

    return {false, Order{}};
}

pair<bool, Order> OrderHistoryList::searchOrderEndNumber(int number)
{

    OrderHistory *aux = this->tail;

    while (aux != nullptr)
    {

        if (aux->getOrder().getNumberOrder() == number)
        {
            return {true, aux->getOrder()};
            break;
        }
        aux = aux->getPrevious();
    }

    return {false, Order{}};
}

pair<bool, Order> OrderHistoryList::searchOrderClient(string nameClient)
{
    OrderHistory *aux = this->head;

    while (aux != nullptr)
    {

        if (aux->getOrder().getNameClient() == nameClient)
        {
            return {true, aux->getOrder()};
            break;
        }
        aux = aux->getNext();
    }

    return {false, Order{}};
}

OrderHistoryList::~OrderHistoryList()
{
}

void OrderHistoryList::removeOrder(int number)
{

    OrderHistory *auxOrderRemove = this->head;

    if (auxOrderRemove != nullptr)
    {
        while (auxOrderRemove->getNext() != nullptr)
        {
            if (auxOrderRemove->getOrder().getNumberOrder() == number)
            {
                break;
            }

            auxOrderRemove = auxOrderRemove->getNext();
        }

        if (auxOrderRemove != this->head)
        {
            // utilizar um ponteiro;
            // atualizar o proximo e o antecessor
            auxOrderRemove->getNext()->getPrevious()->setPrevious(auxOrderRemove->getPrevious());
            auxOrderRemove->getPrevious()->getNext()->setNext(auxOrderRemove->getNext());

            // deletar o objeto
            delete auxOrderRemove;
        }
        else
        {
            cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
            cout << "Pedido não esta no histórico" << "\n";
            cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
        }
    }
    else
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "Pedido não esta no histórico" << "\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
    }
}

OrderHistory *OrderHistoryList::getTail() const
{
    return this->tail;
}

OrderHistory *OrderHistoryList::gethead() const
{
    return this->head;
}