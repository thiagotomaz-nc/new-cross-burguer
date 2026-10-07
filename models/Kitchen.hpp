#ifndef _KITCHEN_HPP_
#define _KITCHEN_HPP_

#include "PreparationQueue.hpp"

// desenfileirado da fila PreparationQueue;
class Kitchen
{
private:
   Order *data3
   ;
public:
    Kitchen(/* args */);

    void callOrder();
    void startPreration();
    void finishPreparation();

    ~Kitchen();
};

#endif