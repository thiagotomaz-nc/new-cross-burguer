#ifndef _KITCHEN_HPP_
#define _KITCHEN_HPP_

#include "PreparationQueue.hpp" // Para desenfileirar pedidos (RF05)
#include "PickupStack.hpp"      // Para empilhar pedidos prontos (RF06)

class Kitchen
{
private:
    Order *data; // Guarda o pedido que está sendo preparado no momento

public:
    Kitchen();

    void callOrder(PreparationQueue &preparationQueue);
    void startPreparation();
    void finishPreparation(PickupStack &pickupStack);

    ~Kitchen();
};

#endif