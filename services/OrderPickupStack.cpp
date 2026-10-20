#include "../models/OrderPickupStack.hpp"

OrderPickupStack::OrderPickupStack(/* args */)
{
    this->top = nullptr;
    this->pickupStack = nullptr;
    this->size = 0;
    this->head = nullptr;
}

void OrderPickupStack::push(Order *order)
{
    if (order == nullptr)
    {
        cout << "O pedido nao pode ser vazio!" << endl;
        return;
    }

    // Criamos um NOVO nó localmente para não reutilizar o mesmo ponteiro de membro
    PickupStack *newNode = new PickupStack();
    newNode->orderInPickupStack(order);

    this->size++;

    if (this->head == nullptr)
    {
        this->head = newNode;
        this->top = newNode;
    }
    else
    {
        newNode->setNext(this->top);
        this->top = newNode;
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

    cout << "\n---------------------------------------------------------" << endl;
    cout << "Pedido [ " << this->top->getOrder()->getNumberOrder() << " ] entregue!" << endl;
    cout << "---------------------------------------------------------\n"
         << endl;

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

    PickupStack *aux = this->top;

    this->top = this->top->getNext();

    delete aux; // Liberta a memória do topo atual

   // O anterior passa a ser o novo topo
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
        int deliverySequence = 1;

        cout << "\n\nFILA DE RETIRADA" << " [ total de pedidos prontos: " << this->size << " ]" << endl;
        cout << "**************************************************************" << endl;

        PickupStack *aux = this->top;

        do
        {
            cout << "-------" << endl;
            cout << "ORDEM PARA RETIRADA:  " << deliverySequence++ << endl;
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