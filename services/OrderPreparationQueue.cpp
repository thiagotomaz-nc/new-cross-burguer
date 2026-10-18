#include "../models/OrderPreparationQueue.hpp"

OrderPreparationQueue::OrderPreparationQueue()
{
    this->head = nullptr;
    this->n_elements = 0;
}

void OrderPreparationQueue::enqueue(Order *orderInHistory)
{

    this->preparationQueue = new PreparationQueue();
    this->preparationQueue->setOrder(orderInHistory);
    this->preparationQueue->setNext(nullptr);

    this->n_elements++;

    // Se o elemento principal (head) não tiver dados ainda, preenche direto
    if (this->head == nullptr)
    {
        this->head = this->preparationQueue;
        return;
    }

    // Caso contrário, navega até o último nó da fila
    PreparationQueue *current = this->head;

    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }

    // Conecta o novo nó ao final
    current->setNext(this->preparationQueue);
}

bool OrderPreparationQueue::dequeueOrderNumber(int orderNumber)
{
    if (isEmpty())
    {
        return false;
    }

    // Se há 2 ou mais elementos na fila
    PreparationQueue *aux = this->head;

    if (aux->getOrder()->getNumberOrder() == orderNumber)
    {

        this->head = aux->getNext();
        delete aux;
        this->n_elements--;
        return true;
    }

    while (aux->getNext() != nullptr)
    {
        if (aux->getNext()->getOrder()->getNumberOrder() == orderNumber)
        {
            aux->setNext(aux->getNext()->getNext());

            delete aux->getNext();
            this->n_elements--;
            return true;
        }
        aux = aux->getNext();
    }

    return false;
}
// ponteiro ou não
void OrderPreparationQueue::dequeue()
{
    // Se a fila está vazia (cabeça sem pedido), não faz nada
    if (isEmpty())
    {
        displayMessage("Fila de preparo esta vazia!");
        return;
    }

    // Se há apenas 1 elemento na fila
    if (this->n_elements == 1)
    {
        delete this->head;
        this->head = nullptr;
        this->n_elements--;
        return;
    }

    // Se há 2 ou mais elementos na fila
    PreparationQueue *temp = this->head; // Pega o ponteiro do primeiro nó

    this->head = this->head->getNext();

    this->n_elements--;

    delete temp;
    // atualaliza a cabeça apontando ela para o proximo  nó
}

bool OrderPreparationQueue::isEmpty()
{
    return this->head == nullptr;
}

// retorno o objeto OrderStory;
Order OrderPreparationQueue::getPeek()
{
    return *this->head->getOrder();
}

// utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;
// protegendo a estrutura;

OrderPreparationQueue::~OrderPreparationQueue()
{
    // não posso apagar o orderhistory, pois ele esta salvo no historico;
    delete this->preparationQueue;
    this->preparationQueue = nullptr;
}

Order *OrderPreparationQueue::getOrderPreparation()
{
    return this->head->getOrder();
}

void OrderPreparationQueue::showQueuePreparation()
{
    // Caso contrário, navega até o último nó da fila
    // Sempre vou exibir toda a minha fila de preparo
    cout << "\nFILA DE PREPARO" << " [ total de pedidos: " << this->n_elements << " ]" << endl;
    cout << "**************************************************************" << endl;
    int sequencia = 1;

    if (!isEmpty())
    {
        PreparationQueue *aux = this->head;

        do
        {
            cout << "Ordem preparo: " << sequencia << endl;
            aux->getOrder()->showResumeOrder();
            aux = aux->getNext();
            sequencia++;
            cout << "\n";
        } while (aux != nullptr);
    }
    else
    {
        displayMessage("Fila de preparo esta vazia!");
    }
}

void OrderPreparationQueue::displayMessage(string displayMessage)
{
    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << displayMessage << "\n";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
}