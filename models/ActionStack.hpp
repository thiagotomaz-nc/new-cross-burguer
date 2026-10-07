#ifndef _Action_HPP_
#define _Action_HPP_

#include "ActionItem.hpp"

#include <iostream>
using namespace std;

class ActionStack{

    private:
        ActionItem * data;
        ActionStack * next;
        int size;
        int length;
    
    public:
        void push(ActionItem *);
        ActionItem * pop();
        ActionItem * peek();

        bool isEmpty();

        void setSize(int size);
        int getSize();

        int getLength();
        void setLength(int newLength);
};

#endif