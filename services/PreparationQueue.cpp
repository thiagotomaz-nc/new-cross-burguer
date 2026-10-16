#include "../models/PreparationQueue.hpp"

PreparationQueue::PreparationQueue() {
    this->head = nullptr;
    this->n_elements = 0;
}

void PreparationQueue::enqueue(Order* orderHistoryTemp) {


    PreparationQueueNode * preparetionQueueNode = new PreparationQueueNode();
    preparetionQueueNode->setOrder(orderHistoryTemp);
    preparetionQueueNode->setNext(nullptr);

    this->n_elements++;

    // Se o elemento principal (head) não tiver dados ainda, preenche direto
    if (this->head == nullptr) {
        this->head  = preparetionQueueNode;
        this->peek = preparetionQueueNode;
        this->n_elements++;
        return;
    }

    // Caso contrário, navega até o último nó da fila
    PreparationQueueNode* current = this->head;

    while (current->getNext() != nullptr) {
        current = current->getNext();
    }

    // Conecta o novo nó ao final
    current->setNext(preparetionQueueNode);

    // Atualiza o ponteiro do último nó da fila
    this->peek = preparetionQueueNode; 
}

// ponteiro ou não
void PreparationQueue::dequeue() {
    // Se a fila está vazia (cabeça sem pedido), não faz nada
    if (this->head == nullptr) {
        return;
    }

    // Se há apenas 1 elemento na fila
    if (this->n_elements == 1) {
        delete this->head;
        this->head = nullptr;
        return;
    }

    // Se há 2 ou mais elementos na fila
    PreparationQueueNode* temp = this->head; // Guarda o ponteiro do segundo nó
    
    this->head = temp->getNext();           // Promove o pedido do segundo nó para a cabeça
    delete temp;                            // Aponta para o terceiro nó (preservando o resto da fila)
                                  // Desconecta o nó antigo antes de deletar
                            // Libera a memória apenas do nó promovido
}

int PreparationQueue::isEmpty(){
    return (this->head==nullptr)? 0 : this->n_elements;
}

//retorno o objeto OrderStory;
Order PreparationQueue::getPeek() {
    return this->head->getOrder();
}

// utilizar a copia do primeiro elemento da pilha,para não permitir exclusão;
// protegendo a estrutura;

PreparationQueue::~PreparationQueue(){
    //não posso apagar o orderhistory, pois ele esta salvo no historico;
}

Order* PreparationQueue::getOrderPreparation(){
    return this->head->getOrder();
}
