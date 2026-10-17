#include "../models/PickupStackNode.hpp"

PickupStackNode::PickupStackNode() {
    this->order = nullptr;
    this->next = nullptr;
}

PickupStackNode::PickupStackNode(Order *order) {
    this->order = order;
    this->next = nullptr;
}

Order* PickupStackNode::getOrder() {
    return this->order;
}

void PickupStackNode::setOrder(Order *order) {
    this->order = order;
}

PickupStackNode* PickupStackNode::getNext() const {
    return this->next;
}

void PickupStackNode::setNext(PickupStackNode *next) {
    this->next = next;
}

PickupStackNode::~PickupStackNode() {
    // Não deletamos o 'order' aqui para garantir que o pedido
    // continue existindo no vetor principal e no histórico.
}