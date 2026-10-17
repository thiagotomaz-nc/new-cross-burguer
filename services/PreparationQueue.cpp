#include "../models/PreparationQueue.hpp"

PreparationQueue::PreparationQueue()
{
    this->head = nullptr;
    this->peek = nullptr;
    this->n_elements = 0;
}

void PreparationQueue::enqueue(Order *orderHistoryTemp)
{

    this->preparationQueueNode = new PreparationQueueNode();
    this->preparationQueueNode->setOrder(orderHistoryTemp);
    this->preparationQueueNode->setNext(nullptr);

    this->n_elements++;

    // Se o elemento principal (head) não tiver dados ainda, preenche direto
    if (this->head == nullptr)
    {
        this->head = this->preparationQueueNode;
        this->peek = this->preparationQueueNode;
        return;
    }

    // Caso contrário, navega até o último nó da fila
    PreparationQueueNode *current = this->head;

    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }

    // Conecta o novo nó ao final
    current->setNext(this->preparationQueueNode);

    // Atualiza o ponteiro do último nó da fila
    this->peek = this->preparationQueueNode;
}

// ponteiro ou não
void PreparationQueue::dequeue()
{
    // Se a fila está vazia (cabeça sem pedido), não faz nada
    if (this->head == nullptr)
    {
        return;
    }

    // Se há apenas 1 elemento na fila
    if (this->n_elements == 1)
    {
        delete this->head;
        this->head = nullptr;
        return;
    }

    // Se há 2 ou mais elementos na fila
    PreparationQueueNode *temp = this->head; // Guarda o ponteiro do segundo nó

    this->head = temp->getNext(); // Promove o pedido do segundo nó para a cabeça
    delete temp;                  // Aponta para o terceiro nó (preservando o resto da fila)
                                  // Desconecta o nó antigo antes de deletar
                                  // Libera a memória apenas do nó promovido
}

bool PreparationQueue::isEmpty()
{
    return this->head == nullptr;
}

// retorno o objeto OrderStory;
Order PreparationQueue::getPeek()
{
    return *this->head->getOrder();
}

// utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;
// protegendo a estrutura;

PreparationQueue::~PreparationQueue()
{
    // não posso apagar o orderhistory, pois ele esta salvo no historico;
    delete this->preparationQueueNode;
    this->preparationQueueNode = nullptr;
}

Order *PreparationQueue::getOrderPreparation()
{
    return this->head->getOrder();
}

void PreparationQueue::showQueuePreparation()
{
    // Caso contrário, navega até o último nó da fila

    if (!isEmpty())
    {
        PreparationQueueNode *aux = this->head;
        
        do
        {
            aux-> getOrder()->showResumeOrder();
            aux = aux->getNext();

        } while (aux != nullptr);
    }
    else
    {
        cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
        cout << "Fila de preparo esta vazia!" << "\n";
        cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
    }
}