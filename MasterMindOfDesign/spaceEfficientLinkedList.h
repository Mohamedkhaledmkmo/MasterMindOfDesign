#ifndef SPACEEFFICIENTLINKEDLIST_H
#define SPACEEFFICIENTLINKEDLIST_H
#include "LinkedList.h"
#include "Queue.h"
template <typename B>
class SELinkedList : protected LinkedList<ArrayQueue<B>> {
private:
    size_t numElements; //number of elements
    size_t alreadyFull; //the already full nodes
public:
	SELinkedList():numElements(0),alreadyFull(0){}
    ~SELinkedList() {
        Node<ArrayQueue<B>>* ptr = this->head;
        while (ptr) {
            Node<ArrayQueue<B>>* next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }
	void insert(B element){

		if (this->size==0){

			Node<ArrayQueue<B>>* newnode = new Node<ArrayQueue<B>>;
			newnode->key.add(element);
            this->head = this->tail = newnode;
		}
		else {
            Node<ArrayQueue<B>>* node = this->head;
            if(this->size!=1)
                for (size_t i = 1; i < this->size; i++)
                {
                    node = node->next;
                }

                if (node->key.add(element)) {
                    numElements++;
                    return;
                }
                else {
                    Node<ArrayQueue<B>>* newnode = new Node<ArrayQueue<B>>;
                    newnode->key.add(element);
                    node->next = newnode;
                    
                }
		}
        this->size++;
        numElements++;
        
	}

    B remove() {
            
            if (this->head->key.isEmpty()) {
                Node<ArrayQueue<B>>* node = this->head;
                this->head = this->head->next;
                delete node;
                this->size--;
            }
            numElements--;
            return this->head->key.remove();

    }
    
    size_t getNumOfElements() { return numElements; }
    
    size_t getsize() { return this->getNum(); }
};











#endif 
