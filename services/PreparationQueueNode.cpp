#include "../models/PreparationQueueNode.hpp"

PreparationQueueNode::PreparationQueueNode(){
    this->next=nullptr;
    this->orderPreparation=nullptr;

}
void PreparationQueueNode::setOrder(Order *order){
    this->orderPreparation = order;
    
}

Order *PreparationQueueNode::getOrder(){
    return this->orderPreparation;
}
PreparationQueueNode *PreparationQueueNode::getNext() const{
    return this->next;
}

void PreparationQueueNode::setNext(PreparationQueueNode *next){
    this->next = next;
}