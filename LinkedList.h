#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cassert>
using namespace std;

/*

    Stack: --> insertFront(), removeFront()
    Queue: --> insertFront(), removeBack()

*/

template <typename T>
struct Node {
    T key;
    Node<T> *next = nullptr;
    Node<T> *prev = nullptr;
};

template <typename T>
class LinkedList {
protected:
        size_t size = 0;   // to track the number of elements 
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
public:
        LinkedList() {
        }
        void insertBack(T key) {
            Node<T>* newNode = new Node<T>;
            newNode->key = key;
            if (size==0)
            {
                head = tail = newNode;
            }
            else
            {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
            size++;
        }
        void insertFront(T key) {
            Node<T> *newNode = new Node<T>;
            newNode->key = key;
            newNode->next = head;

            if (head != nullptr) {
                head->prev = newNode;
            }

            head = newNode;
            if (size == 0) {
                tail = newNode;
            }
            size++;
        }

        void print() const {
            Node<T>* current = head;
            while (current) {
                cout << current->key;
                current = current->next;
            }
            cout << endl;
        }

        Node<T>* findKey(T key) {
            Node<T> *ptr = head;
            size_t j = 0;
            while (ptr != nullptr && ptr->key != key && j < size-1) {
                ptr = ptr->next;
                j++;
            }
            if (ptr == nullptr || ptr->key != key) {
                throw out_of_range("The key doesn't exist\n");
            }
            return ptr;
        }

        Node<T>* findIndex(size_t i) {
            assert(i <= size && i >= 0);
            Node<T> *ptr = head;
            size_t j = 0;
            while (ptr != nullptr && j != i) {
                ptr = ptr->next;
                j++;
            }
            if (!ptr) {
                throw out_of_range("Invalid index");
            }
            return ptr;
        }
public:
        size_t getNum() {
            return size;
        }

        Node<T>* getHead() {
            return head;
        }

        ~LinkedList() {
            Node<T> *ptr = head;
            while (ptr != nullptr) {
                Node<T> *next = ptr->next;
                delete ptr;
                ptr = next;
            }
        }
};

#endif

