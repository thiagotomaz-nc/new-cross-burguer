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

        if (tempOrder.getStatusOrder() != StatusOrder::CANCELADO)
        {
            tempOrder.sumTotalPriceToOrder();
        }

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

bool OrderHistoryList::cancelOrder(int orderNumber)
{
    if (isEmpty())
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "[aviso] O historico esta vazio.\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
        return false;
    }

    OrderHistory *auxCancelOrder = this->head;

    while (auxCancelOrder != nullptr)
    {
        if (auxCancelOrder->getOrder().getNumberOrder() == orderNumber)
        {
            if (auxCancelOrder->getOrder().getStatusOrder() != StatusOrder::CANCELADO && auxCancelOrder->getOrder().getStatusOrder() != StatusOrder::PRONTO && auxCancelOrder->getOrder().getStatusOrder() != StatusOrder::FINALIZADO)
            {

                char confirm;
                cin.ignore();

                cout << "\nTem certeza que deseja cancelar o pedido de numero [ "
                     << auxCancelOrder->getOrder().getNumberOrder() << " ] ? (s/n): ";

                cin >> confirm;

                if (confirm == 's' || confirm == 'S')
                {

                    auxCancelOrder->getOrderPointer()->setStatusOrder(StatusOrder::CANCELADO);

                    cout << "\n---------------------------------------------------------\n";
                    cout << "pedido de numero [ " << orderNumber << " ] cancelado com sucesso.\n";
                    cout << "\n---------------------------------------------------------\n\n";

                    return true;
                }
                else
                {
                    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
                    cout << "Operacao abortada, nenhuma alteracao efetuada\n";
                    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
                    return false;
                }
            }
            else
            {
                cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
                cout << "Operacao bloqueada, pois o pedido ja esta com status de PRONTO / FINALIZADO / CANCELADO\n";
                cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
                return false;
            }
        }

        auxCancelOrder = auxCancelOrder->getNext();
    }

    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << "Pedido de numero [ "<<orderNumber<<  " ] inexistente. Tente novamente! \n";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";

    return false;
}

bool OrderHistoryList::removeOrder(int number)
{

    if (isEmpty())
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "[aviso] O historico esta vazio.\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
        return false;
    }

    OrderHistory *auxOrderRemove = this->head;

    while (auxOrderRemove != nullptr)
    {

        if (auxOrderRemove->getOrder().getNumberOrder() == number)
        {

            if (auxOrderRemove->getOrder().getStatusOrder() != StatusOrder::PRONTO && auxOrderRemove->getOrder().getStatusOrder() != StatusOrder::FINALIZADO)
            {

                char confirm;
                cin.ignore();

                cout << "\nTem certeza que deseja apagar o pedido de numero [ "
                     << auxOrderRemove->getOrder().getNumberOrder() << " ] ? (s/n): ";

                cin >> confirm;

                if (confirm == 's' || confirm == 'S')
                {
                    // INICIO - previous e next apontam para nullptr
                    if (auxOrderRemove->getPrevious() == nullptr && auxOrderRemove->getNext() == nullptr)
                    {
                        this->tail = nullptr;
                        this->head = nullptr;
                    }
                    // MEIO - significa que o historico tem um antecessor e um sucessor, NÃO MEXO NEM EM HEAD E NEM EM TAIL
                    else if (auxOrderRemove->getNext() != nullptr && auxOrderRemove->getPrevious() != nullptr)
                    {
                        auxOrderRemove->getPrevious()->setNext(auxOrderRemove->getNext());
                        auxOrderRemove->getNext()->setPrevious(auxOrderRemove->getPrevious());
                    }
                    else if (auxOrderRemove == this->head)
                    {
                        this->head = auxOrderRemove->getNext();
                        auxOrderRemove->getNext()->setPrevious(nullptr);
                    }
                    else
                    {
                        this->tail = auxOrderRemove->getPrevious();
                        auxOrderRemove->getPrevious()->setNext(nullptr);
                    }

                    delete auxOrderRemove;

                    cout << "\n---------------------------------------------------------\n";
                    cout << "pedido de numero [ " << number << "] deletado com sucesso.\n";
                    cout << "\n---------------------------------------------------------\n\n";

                    return true;
                }
                else
                {
                    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
                    cout << "Operacao abortada, nenhuma alteracao efetuada\n";
                    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
                    return false;
                }
            }
            else
            {
                cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
                cout << "Operacao cancelada, pois o pedido ja esta com status de PRONTO ou FINALIZADO\n";
                cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
                return false;
            }
        }

        auxOrderRemove = auxOrderRemove->getNext();
    }

    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << "Numero de pedido [ " << number << " ] inexistente.Tente novamente !";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";

    return false;
}

OrderHistory *OrderHistoryList::getTail() const
{
    return this->tail;
}

OrderHistory *OrderHistoryList::gethead() const
{
    return this->head;
}