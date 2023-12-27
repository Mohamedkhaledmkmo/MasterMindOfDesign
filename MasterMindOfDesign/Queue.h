#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "LinkedList.h"
using namespace std;


template <typename T>
class ArrayQueue {
	private:
		
		size_t capacity = 0; // FIXED
		size_t size = 0;
		size_t j = 0;	// next element to remove
		T *array;

	public:
		ArrayQueue(size_t initCap = 3) : capacity(initCap) {
			array = new T[capacity];
		}

		// copy constructor
		ArrayQueue(const ArrayQueue& other)
			: capacity(other.capacity), size(other.size) {

			array = new T[capacity];
			for(int i = 0; i < size; i++) {
				array[i] = other.array[i];
			}
		}

		void resize() {
			int s = size * 2;
			size_t newCap = max(s, 2);
			T *newArr = new T[newCap];

			for (int k = 0; k < size; k++) {
				newArr[k] = array[(j+k)%size];
			}

			delete[] array;
			capacity = newCap;
			array = newArr;
			j = 0;
		}

		T& getElement(size_t i) {
			if(i > size || i < 0)  
				throw std::out_of_range("Invalid index");
			return array[i];
		}

		void print() {
			for(int i = 0; i < size; i++) {
				cout << array[(j+i)%capacity];
			}
            cout << endl;
		}

		friend ostream& operator<< (ostream& os, const ArrayQueue& queue) {
        	for(int i = 0; i < queue.size; i++) {
				cout << "------------\n";
            	os << queue.array[((queue.j) + i)%queue.capacity];
				cout << "------------\n";
        	}
        	return os;
    	}

		size_t getSize() const {
			return size;
		}

		size_t getCap() const {
			return capacity;
		}

		// same as copy constructor
		ArrayQueue& operator= (const ArrayQueue &other) {
			if (this != &other) {
				delete[] array;
				capacity = other.capacity;
				size = other.size;
				array = new T[capacity];

				for (int i = 0; i < size; i++) {
					array[i] = other.array[i];
				}
			}

			return *this;
		}

		T& operator[] (size_t i) const {
			assert(i < size && i >= 0);
			return array[(j+i)%capacity];
		}

		bool add(T x) {
			if (isAvailable()) {
				array[(size + j) % capacity] = x;
				size++;
				return true;
			}
			else
				return false;
		}

		bool isAvailable() {
			if (size == capacity) {
				return false;
			} else {
				return true;
			}
		}

		bool isEmpty() {
			if (size == 0)
				return true;
			
			return false;
		}

		T remove() {
			T x = array[j];
			j = (j+1) % capacity;
			size--;
			return x;
		}

		~ArrayQueue() {
			delete[] array;
		}
};

// template <typename T>
// class Queue : public LinkedList<T> {
//     public:
//         void removeBack() {
//             if (this->n == 0) { return; }
//             if (this->n == 1) { delete this->head; }

//             Node<T> *node = this->tail;
//             this->tail = this->tail->prev;
//             this->tail->next = nullptr;
//             delete node;
//         }
// };

#endif