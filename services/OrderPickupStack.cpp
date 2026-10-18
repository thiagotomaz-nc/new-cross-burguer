#include "../models/OrderPickupStack.hpp"

OrderPickupStack::OrderPickupStack(/* args */)
{
    this->top = nullptr;
    this->pickupStack = nullptr;
}

void OrderPickupStack::push(Order *order)
{
    if (order == nullptr)
    {
        cout << "O pedido nao pode ser vazio!";
        return;
    }

    this->pickupStack = new PickupStack();
    this->pickupStack->orderInPickupStack(order);

    this->size++;

    if (this->top == nullptr)
    {
        this->head = this->pickupStack;
        this->top = this->head;
        return;
    }
    else
    {
        this->top = this->pickupStack;

        PickupStack *aux = this->head;

        while (aux->getNext() != nullptr)
        {
            aux = aux->getNext();
        }

        // O anterior aponta para o novo topo
        aux->setNext(this->top);

        cout << "Pedido: " << this->head->getOrder() << endl;
    }
}

void OrderPickupStack::pop()
{
    if (!isEmpty())
    {

        this->top->getOrder()->setStatusOrder(StatusOrder::FINALIZADO);

        cout << "\n---------------------------------------------------------" << endl;
        cout << "Pedido [ " << this->top->getOrder()->getNumberOrder() << " ] entregue!" << endl;
        cout << "---------------------------------------------------------\n"
             << endl;

        if (this->size == 1)
        {
            this->size--;
            delete this->head;

            this->head = nullptr;
            this->top = nullptr;

            return;
        }

        PickupStack *aux = this->head;

        while (aux->getNext() != this->top)
        {
            aux = aux->getNext();
        }

        delete this->top;

        aux->setNext(nullptr);
        this->top = aux;

        this->size--;
    }
    else
    {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "Nenhum pedido disponivel para retirada." << endl;
        cout << "---------------------------------------------------------\n"
             << endl;
    }
}

Order OrderPickupStack::peek()
{
    return *this->top->getOrder();
}

bool OrderPickupStack::isEmpty()
{
    return this->head == nullptr;
}
int OrderPickupStack::getSize()
{
    return this->size;
}

void OrderPickupStack::printReadyOrders()
{
    if (!isEmpty())
    {
        int deliverySequence = this->size ;

        cout << "\n\nFILA DE RETIRADA" << " [ total de pedidos prontos: " << this->size << " ]" << endl;
        cout << "**************************************************************" << endl;

        PickupStack *aux = this->head;

        do
        {   
            cout << "-------" << endl;
            cout<<"ORDERM PARA RETIRADA:  "<< deliverySequence--<<endl;
            cout << "-------" << endl;
            aux->getOrder()->showResumeOrder();
            aux = aux->getNext();

        } while (aux != nullptr);

        cout<<"\n";
    }
    else
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "Nenhum pedido disponivel para retirada! aguarde..." << "\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
    }
}

OrderPickupStack::~OrderPickupStack() {}