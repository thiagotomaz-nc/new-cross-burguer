#ifndef _ActionItem_HPP_
#define _ActionItem_HPP_
                            //açãoItem é uma classe intermediário que vai ser organizada pelo ActionStack

#include "Items.hpp"

#include <iostream>
using namespace std;

class ActionItem{

    private:
        int typeOperation;
        Item *affectedItem;        
    public:
        string getTypeOperation();
        void setTypeOperation(string);

        Item * getAffectedItems();
        void setAffectedItem(Item*);

        int getPreviousQuantity();
        void setPreviousQuantity(int quantity);
};

#endif