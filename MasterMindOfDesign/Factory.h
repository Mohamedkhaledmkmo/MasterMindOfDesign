#ifndef FACTORY_H
#define FACTORY_H

#include "spaceEfficientLinkedList.h"
#include "Operation.h"
#include "Queue.h"
#include "Car.h"
#include "assistantFunctions.h"
#include <thread>
#include <chrono>
#include <vector>

enum class FactoryStatus {
    OPERATIONAL,
    UNDER_MAINTENANCE,
    NON_OPERATIONAL
};

class Factory {
    private:
        SELinkedList<Car>* line;  // stores the cars in the manufacturing process
        ArrayQueue<Car>* wareHouse; // stores the finished cars
        size_t carCount = 0; // how many cars entered the manufacturing process
        size_t carInqueue = 0; // how many cars in the production line
        size_t prodCapacity = 999; // how many cars the factory can manufacture
        FactoryStatus factoryStatus = FactoryStatus::OPERATIONAL;

    public:
        Factory() {
            line = new SELinkedList<Car>;
            wareHouse = new ArrayQueue<Car>(999);
            carCount++;
            carInqueue++;
            Car firstCar(carCount);
            line->insert(firstCar);

        }
       
        ~Factory() {
            delete line;
            delete wareHouse;
        }
        
        void addCar() {
            carCount++;
            carInqueue++;
            Car newCar(carCount);
            newCar.setColor();
            line->insert(newCar);
        }
        
        void startProduction() {
            if (carInqueue == 0) { 
                cout << "\nNo cars in the production line\n\n";
                system("pause");
            }
            else if (carInqueue == prodCapacity) {
                if (carInqueue == 0) {
                    cout << "\nProduction line is Full\n\n";
                    system("pause");
                }
            }
            else if (wareHouse->getSize() == prodCapacity) {
                if (carInqueue == 0) {
                    cout << "\nWarehouse is Full\n\n";
                    system("pause");
                }
            }
            else
            {
                vector<std::thread> threads;                    // each 3 cars manufacturing works simultaneously using threads to simulate real factory 
                size_t n = carInqueue;
                for (size_t i = 0; i <n; i++)             
                {
                    if (i%3==0 && i!=0)
                    {
                        partialScreenClear(1,30);
                    }
                   
                    carInqueue--;
                    Car produced = line->remove();
                    wareHouse->add(produced);
                    threads.emplace_back(&Car::carManufacture,produced);
                    if ((i+1)%3==0)
                    {
                       this_thread::sleep_for(chrono::seconds(21));
                    }
                    this_thread::sleep_for(chrono::seconds(3));            // each car manufacture process starts after 3 sec of runtime of the previous
                    gotoXY(0, (i%3+1)*10 + 1 );
                        
                }
                for (auto& thread : threads)
                {
                    thread.join();
                    
                }
            }

        }
       
        void showFactoryOperations() {
            gotoXY(0, 2);
            Car b;
            b.getoperations();
            system("pause");
        }
       
        void showFinishedCars() {
            gotoXY(0, 2);
            if (wareHouse->getSize() == 0)
            {
                color(4);
                cout << "!!No Added cars\n";
                color(7);
            }
            else {
                
                wareHouse->print();
            }

            system("pause");
        }

        void statisticsBar() {
            COORD curr = GetConsoleCursorPosition();
            gotoXY(77, 28);
            cout << setw(3) << setfill('0') << carInqueue << " / 999 production " << (char)(219) << " " << setw(3) << wareHouse->getSize() << " / 999 warehouse" << setfill(' ');
            gotoXY(77, 29);
            cout << "------------------------------------------";
            gotoXY(curr.X, curr.Y);
        }
       
        size_t getCarCount() { return carCount; }
        
};

#endif