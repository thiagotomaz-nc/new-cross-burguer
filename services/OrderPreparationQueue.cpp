#include "../models/OrderPreparationQueue.hpp"

OrderPreparationQueue::OrderPreparationQueue()
{
    this->head = nullptr;
    this->n_elements = 0;
}

void OrderPreparationQueue::enqueue(Order *orderInHistory)
{
    if (orderInHistory == nullptr) return;

    // Alocação em ponteiro LOCAL (não guarda em membro da classe)
    PreparationQueue *newNode = new PreparationQueue();
    newNode->setOrder(orderInHistory);
    newNode->setNext(nullptr);

    this->n_elements++;

    if (this->head == nullptr)
    {
        this->head = newNode;
        return;
    }

    PreparationQueue *current = this->head;
    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }

    current->setNext(newNode);
}

bool OrderPreparationQueue::dequeueOrderNumber(int orderNumber)
{
    if (isEmpty())
    {
        return false;
    }

    PreparationQueue *aux = this->head;

    // Caso 1: O elemento a ser removido é o HEAD
    if (aux->getOrder() != nullptr && aux->getOrder()->getNumberOrder() == orderNumber)
    {
        this->head = aux->getNext();
        delete aux;
        this->n_elements--;
        return true;
    }

    // Caso 2: O elemento está no meio ou fim da fila
    while (aux->getNext() != nullptr)
    {
        if (aux->getNext()->getOrder() != nullptr && aux->getNext()->getOrder()->getNumberOrder() == orderNumber)
        {
            PreparationQueue *nodeToDelete = aux->getNext();
            aux->setNext(nodeToDelete->getNext());
            delete nodeToDelete;
            
            this->n_elements--;
            return true;
        }
        aux = aux->getNext();
    }

    return false;
}

void OrderPreparationQueue::dequeue()
{
    if (isEmpty())
    {
        displayMessage("Fila de preparo esta vazia!");
        return;
    }

    PreparationQueue *temp = this->head;
    this->head = this->head->getNext();
    this->n_elements--;

    delete temp;
}

bool OrderPreparationQueue::isEmpty()
{
    return this->head == nullptr;
}

Order OrderPreparationQueue::getPeek()
{
    if (this->head != nullptr && this->head->getOrder() != nullptr)
    {
        return *this->head->getOrder();
    }
    return Order();
}

OrderPreparationQueue::~OrderPreparationQueue()
{
    while (this->head != nullptr)
    {
        PreparationQueue *temp = this->head;
        this->head = this->head->getNext();
        delete temp;
    }
}

Order *OrderPreparationQueue::getOrderPreparation()
{
    if (this->head != nullptr)
    {
        return this->head->getOrder();
    }
    return nullptr;
}

void OrderPreparationQueue::showQueuePreparation()
{
    cout << "\nFILA DE PREPARO" << " [ total de pedidos: " << this->n_elements << " ]" << endl;
    cout << "**************************************************************" << endl;

    if (isEmpty())
    {
        displayMessage("Fila de preparo esta vazia!");
        return;
    }

    PreparationQueue *aux = this->head;
    int sequencia = 1;

    // Usa loop while limpo para evitar imprimir lixo de memória
    while (aux != nullptr)
    {
        cout << "Ordem preparo: " << sequencia << endl;
        if (aux->getOrder() != nullptr)
        {
            aux->getOrder()->showResumeOrder();
        }
        aux = aux->getNext();
        sequencia++;
        cout << "\n";
    }
}

void OrderPreparationQueue::displayMessage(string displayMessage)
{
    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << displayMessage << "\n";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
}