#ifndef _ORDER_HISTORY_HPP
#define _ORDER_HISTORY_HPP

#include "Order.hpp"

// Lista duplamente encadeada - historico do  dia
class OrderHistory
{
private:
    Order order;
    OrderHistory *previous;
    OrderHistory *next;

public:
    OrderHistory();
    // const após o método: impede alterações diretas nos atributos do objeto atual.
    // const antes do tipo retornado: impede alterações no objeto apontado pelo retorno.
    OrderHistory *getNext();
    OrderHistory *getPrevious();

    void setNext(OrderHistory *next);
    void setPrevious(OrderHistory *previous);
    void setOrder(Order newOrder);

    Order getOrder();
};

#endif