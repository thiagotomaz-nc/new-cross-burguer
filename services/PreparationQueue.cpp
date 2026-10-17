#include "../models/PreparationQueue.hpp"

PreparationQueue::PreparationQueue()
{
    this->head = nullptr;
    this->n_elements = 0;
}

void PreparationQueue::enqueue(Order *orderInHistory)
{

    this->preparationQueueNode = new PreparationQueueNode();
    this->preparationQueueNode->setOrder(orderInHistory);
    this->preparationQueueNode->setNext(nullptr);

    this->n_elements++;

    // Se o elemento principal (head) não tiver dados ainda, preenche direto
    if (this->head == nullptr)
    {
        this->head = this->preparationQueueNode;
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
}

// ponteiro ou não
void PreparationQueue::dequeue()
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
        this->head = nullptr;
        return;
    }

    // Se há 2 ou mais elementos na fila
    PreparationQueueNode *temp = this->head; // Pega o ponteiro do primeiro nó 

    this->head = temp->getNext(); // atualaliza a cabeça apontando ela para o proximo  nó

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
    // Sempre vou exibir toda a minha fila de preparo
    cout << "\nFILA DE PREPARO" << "[ total de pedidos: " << this->n_elements << " ]" << endl;
    cout << "**************************************************************" << endl;
    int sequencia = 1;

    if (!isEmpty())
    {
        PreparationQueueNode *aux = this->head;

        do
        {
            cout << "Ordem preparo: " << sequencia << endl;
            aux->getOrder()->showResumeOrder();
            aux = aux->getNext();

        } while (aux != nullptr);
    }
    else
    {
        displayMessage("Fila de preparo esta vazia!");
    }
}

void PreparationQueue::displayMessage(string displayMessage)
{
    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << displayMessage << "\n";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
}