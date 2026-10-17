#include "../models/Kitchen.hpp"

Kitchen::Kitchen() {
    this->data = nullptr;
}

// Chamar a cozinha -> Desenfileira da PreparationQueue
void Kitchen::callOrder(PreparationQueue &preparationQueue) {
    if (preparationQueue.isEmpty() == 0) {
        cout << "Fila de preparo vazia!" << endl;
        return;
    }

    // Pega o pedido do topo da fila e guarda na cozinha
    this->data = preparationQueue.getOrderPreparation();
    
    // Desenfileira da fila de preparo
    preparationQueue.dequeue();

    cout << "Pedido N. " << this->data->getNumberOrder() << " chamado para a cozinha!" << endl;
}

// Iniciar a preparação (Apenas confirmação visual no terminal)
void Kitchen::startPreparation() {
    if (this->data == nullptr) {
        cout << "Nenhum pedido foi chamado ainda! Chame um pedido primeiro." << endl;
        return;
    }

    cout << "Iniciando o preparo do Pedido N. " << this->data->getNumberOrder() << endl;
}

// Marcar como pronto -> Empilha na PickupStack
void Kitchen::finishPreparation(PickupStack &pickupStack) {
    if (this->data == nullptr) {
        cout << "Nenhum pedido esta sendo preparado no momento!" << endl;
        return;
    }

    this->data->setStatusOrder(StatusOrder::PRONTO);

    // Empilha na pilha de retirada
    pickupStack.push(this->data);

    cout << "Pedido N. " << this->data->getNumberOrder() << " esta PRONTO e foi enviado para a pilha de retirada!" << endl;

    // Libera a bancada de preparo da cozinha
    this->data = nullptr;
}

Kitchen::~Kitchen() {
    // Apontamos para nullptr para garantir que o ponteiro local da bancada é desvinculado,
    // preservando a instância do pedido no histórico.
    this->data = nullptr;
}