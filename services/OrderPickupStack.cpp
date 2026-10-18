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
        cout << "O pedido nao pode ser vazio!" << endl;
        return;
    }

    PickupStack *newPickupStack = new PickupStack();
    newPickupStack->orderInPickupStack(order);

    this->size++;

    if (this->head == nullptr)
    {
        this->head = newPickupStack;
        this->top = newPickupStack;
    }
    else
    {
        PickupStack *aux = this->head;

        while (aux->getNext() != nullptr)
        {
            aux = aux->getNext();
        }

        aux->setNext(newPickupStack);
        this->top = newPickupStack;
    }

    cout << "Pedido adicionado a fila: " << this->top->getOrder()->getNumberOrder() << endl;
}

void OrderPickupStack::pop()
{

    if (isEmpty())
    {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "Nenhum pedido disponivel para retirada." << endl;
        cout << "---------------------------------------------------------\n"
             << endl;
        return;
    }

    // Marca o status do pedido do topo como finalizado
    this->top->getOrder()->setStatusOrder(StatusOrder::FINALIZADO);

    // Caso 1: Apenas 1 elemento na pilha
    if (this->head == this->top)
    {
        delete this->head;

        // Zera TODOS os ponteiros para evitar acesso a memória libertada
        this->head = nullptr;
        this->top = nullptr;
        this->pickupStack = nullptr;
        this->size = 0;
        return;
    }

    // Caso 2: Mais de 1 elemento (encontra o nó anterior ao top)
    PickupStack *aux = this->head;
    while (aux->getNext() != this->top)
    {
        aux = aux->getNext();
    }

    delete this->top; // Liberta a memória do topo atual

    aux->setNext(nullptr);
    this->top = aux; // O anterior passa a ser o novo topo
    this->size--;
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
        int deliverySequence = this->size;

        cout << "\n\nFILA DE RETIRADA" << " [ total de pedidos prontos: " << this->size << " ]" << endl;
        cout << "**************************************************************" << endl;

        PickupStack *aux = this->head;

        do
        {
            cout << "-------" << endl;
            cout << "ORDERM PARA RETIRADA:  " << deliverySequence-- << endl;
            cout << "-------" << endl;
            aux->getOrder()->showResumeOrder();
            aux = aux->getNext();

        } while (aux != nullptr);

        cout << "\n";
    }
    else
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "Nenhum pedido disponivel para retirada! aguarde..." << "\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
    }
}

OrderPickupStack::~OrderPickupStack() {}