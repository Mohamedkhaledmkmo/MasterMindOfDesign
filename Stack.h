#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename T>
class Stack : public LinkedList<T> {
    public:
        T remove() {
            if (this->size == 0) { throw out_of_range("Stack is empty"); }
            T data;
            data = this->head->key;
            if (this->size == 1) { 
                delete this->head; 
                return data;
            }

            Node<T> *node = this->head;
            this->head = this->head->next;
            delete node;
            this->size--;
            return data;
        }
};

#endif