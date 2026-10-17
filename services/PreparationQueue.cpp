#include "../models/PreparationQueue.hpp"

PreparationQueue::PreparationQueue(){
    this->next=nullptr;
    this->orderPreparation=nullptr;

}
void PreparationQueue::setOrder(Order *order){
    this->orderPreparation = order;
}
Order *PreparationQueue::getOrder(){
    return this->orderPreparation;
}
PreparationQueue *PreparationQueue::getNext() const{
    return this->next;
}

void PreparationQueue::setNext(PreparationQueue *next){
    this->next = next;
}