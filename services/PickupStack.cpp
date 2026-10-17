#include "../models/PickupStack.hpp"
#include <iostream>

PickupStack::PickupStack() {
    this->top = nullptr;
    this->length = 0;
}

// Empilha um novo pedido no topo (LIFO)
void PickupStack::push(Order *order) {
    if (order == nullptr) return;

    PickupStackNode *newNode = new PickupStackNode(order);
    
    // O novo nó aponta para o antigo topo
    newNode->setNext(this->top);
    
    // O novo nó passa a ser o topo
    this->top = newNode;
    this->length++;
}

// Desempilha o pedido do topo e retorna o seu ponteiro (RF07)
Order* PickupStack::pop() {
    if (isEmpty()) {
        cout << "Pilha de retirada vazia!" << endl;
        return nullptr;
    }

    PickupStackNode *temp = this->top;
    Order *extractedOrder = temp->getOrder();

    // Promove o nó abaixo para ser o novo topo
    this->top = this->top->getNext();
    
    // Deleta apenas o nó da pilha (mantendo o objeto Order seguro)
    delete temp;
    this->length--;

    return extractedOrder;
}

// Consulta o pedido do topo sem remover
Order* PickupStack::peek() {
    if (isEmpty()) {
        return nullptr;
    }
    return this->top->getOrder();
}

// Retorna 1 (true) se estiver vazia ou 0 (false)
int PickupStack::isEmpty() {
    return (this->top == nullptr);
}

int PickupStack::getLength() {
    return this->length;
}

PickupStack::~PickupStack() {
    // Libera todos os nós da pilha ao destruir o objeto
    while (!isEmpty()) {
        pop();
    }
}