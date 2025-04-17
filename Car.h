#ifndef CAR_H
#define CAR_H

#include "Stack.h"
#include "Operation.h"
#include <iomanip>
#include "assistantFunctions.h"
using namespace std;

class Car {
    private:
        Stack<Operation>* process;
        size_t carID;
        string color;
       
        void carColorsMenu(int xCoord, int ycoord , void (Car::*execution_switch_function)(int _case)) {
            string menuItems[10]= { "DarkBlue","DarkGreen","Cyan","Red","Purple","Yellow","White","Grey","Blue","Green" };
            int numOfItems = 10;
            int* colors = new int[numOfItems];                           // holds the colors of items
            int counter = 0;                                             // indicates the selected item
            char key = 0;                                                // stores the keyboard key

            // initialize the items color
            colors[0] = counter + 1;  // 1st item will be selected by default
            for (int i = 1; i < numOfItems; i++)
            {
                colors[i] = 7;
            }

            // menu printing
            while (true)
            {
                ASSISTANTFUNCTION_H::color(7);
                gotoXY(xCoord - 1, ycoord + counter * 2);
                cout << ">";
                gotoXY(xCoord + menuItems[counter].length(), ycoord + counter * 2);
                cout << "<" << endl;

                for (int i = 0; i < numOfItems; i++)
                {
                    gotoXY(xCoord, ycoord + (i * 2));
                    ASSISTANTFUNCTION_H::color(colors[i]);
                    cout << menuItems[i];
                }

                for (int i = 0; i < numOfItems; i++)      //reset items colors
                    colors[i] = 7;

                
                char key = _getch();


                gotoXY(xCoord - 1, ycoord + counter * 2);
                cout << " ";
                gotoXY(xCoord + menuItems[counter].length(), ycoord + counter * 2);
                cout << " ";

                
                if (key == 72)                                                  //up arrow key
                    counter = ((counter - 1) + numOfItems) % numOfItems;        
                else if (key == 80)                                             //down arrow key
                    counter = (counter + 1) % numOfItems;
                else if (key == '\r')                                           // Enter key
                {
                   ( this->*execution_switch_function)(counter);
                   ASSISTANTFUNCTION_H::color(7);
                   break;
                }

                colors[counter] = counter + 1;              


            }
            delete[] colors;
        }
        
        void colorSelector(int _case) {
            switch (_case)
            {
            case 0:
                color = "DarkBlue";
                break;
            case 1:
                color = "DarkGreen";
                break;
            case 2:
                color = "Cyan";
                break;
            case 3:
                color = "Red";
                break;
            case 4:
                color = "Purple";
                break;
            case 5:
                color = "Yellow";
                break;
            case 6:
                color = "White";
                break;
            case 7:
                color = "Grey";
                break;
            case 8:
                color = "Blue";
                break;
            case 9:
                color = "Green";
                break;
            default:
                break;
            }
        }
    public:
        Car ():carID(0),color(""){
            process = new Stack<Operation>;
            Operation op1("Battery Production", 10, "Producing high-capacity lithium-ion batteries.");
            Operation op2("Stamping", 8, "Large sheets of metal are stamped to create the various panels and structural components\n             of the car's body.");
            Operation op3("Body assembly", 5, "Robots and automated systems weld together the stamped metal parts to form the car's body.");
            Operation op4("Painting", 12, "Robots apply multiple layers of paint and protective coatings to achieve the desired finish.");
            Operation op5("car assembly", 3, "Different components such as the battery pack, motors, interiors, electronics, and other\n             parts are brought together.");
            Operation op6("Quality Control", 4, "This includes visual inspections, automated tests, and measurements to ensure the car meets\n             Tesla's high standards for safety and performance.");
            Operation op7("Testing", 7, "Once the car is fully assembled, it undergoes various tests to validate performance and safety.");
            Operation op8("Final Inspection and Packaging", 13, "After passing all tests, the car undergoes a final inspection to ensure everything meets quality standards.\n""             Once approved, the car is prepared for shipping then packaged securely for transportation\n" "             to distribution centers or directly to customers.");
            addOperation(op8);
            addOperation(op7);
            addOperation(op6);
            addOperation(op5);
            addOperation(op4);
            addOperation(op3);
            addOperation(op2);
            addOperation(op1);
        }

        Car (size_t id , string c = "Red") : carID(id) , color(c) {
            process = new Stack<Operation>;
            Operation op1("Battery Production", 10, "Producing high-capacity lithium-ion batteries.");
            Operation op2("Stamping", 8, "Large sheets of metal are stamped to create the various panels and structural components\n             of the car's body.");
            Operation op3("Body assembly", 17, "Robots and automated systems weld together the stamped metal parts to form the car's body.");
            Operation op4("Painting", 12, "Robots apply multiple layers of paint and protective coatings to achieve the desired finish.");
            Operation op5("car assembly", 3, "Different components such as the battery pack, motors, interiors, electronics, and other\n             parts are brought together.");
            Operation op6("Quality Control", 4, "This includes visual inspections, automated tests, and measurements to ensure the car meets\n             Tesla's high standards for safety and performance.");
            Operation op7("Testing", 7, "Once the car is fully assembled, it undergoes various tests to validate performance and safety.");
            Operation op8("Final Inspection and Packaging", 13, "After passing all tests, the car undergoes a final inspection to ensure everything meets quality standards.\n""             Once approved, the car is prepared for shipping then packaged securely for transportation\n" "             to distribution centers or directly to customers.");
            addOperation(op8);
            addOperation(op7);
            addOperation(op6);
            addOperation(op5);
            addOperation(op4);
            addOperation(op3);
            addOperation(op2);
            addOperation(op1);
        }
        
        void addOperation(Operation op) {
            process->insertFront(op);
        }

        void setColor() {
            cout << "\nSelect the car color: \n";
            COORD currLoc = GetConsoleCursorPosition();
            carColorsMenu(currLoc.X + 1, currLoc.Y+1, &Car::colorSelector);
        }

        void getoperations() {
            process->print();
        }
        
        size_t getId() { return carID; }
       
        string getColor() { return color; }
        
        void carManufacture() {
            size_t numOfProcesses = process->getNum();

            cout << "-------------" << "CarID:" << carID << setw(4) <<"  Color:"<< color << setw(6) << "----------------------------------" << endl;

            COORD firstLocation = GetConsoleCursorPosition(); // holds cursor location when starting the func
            
            gotoXY(firstLocation.X,(firstLocation.Y + 7));
            cout << endl << "-----------------------------------------------------------------------\n";
            
            int loadingBarLength = 10;
            // prints the operation with the empty loading bar 
            gotoXY(firstLocation.X, firstLocation.Y);
            for (size_t i = 0; i < numOfProcesses; i++)
            {
                cout << "-" << process->findIndex(i)->key.getName();
                gotoXY((firstLocation.X + 40) , (firstLocation.Y + i));
                for (int i = 0; i < loadingBarLength; i++)
                    cout << char(177);
                cout << endl;
            }
            // draws the loading progress and remaining time
            for (size_t i = 0; i < numOfProcesses; i++)
            {
                size_t time = process->remove().getTime();
                int draw = 0;
                int move = 0;
                for (size_t j = 1; j <= time; j++)
                {
                    Sleep(300);
                    gotoXY(51, (firstLocation.Y + i));
                    cout << "(" << setw(2) << (time) - j << "  sec remaining )";
                    ASSISTANTFUNCTION_H::color(10);
                    gotoXY((firstLocation.X + 40) + move , (firstLocation.Y + i));
                    if (time < loadingBarLength) {
                        if (j < time)
                            draw = loadingBarLength / time;
                        else
                            draw = loadingBarLength - ((loadingBarLength / time) * (time - 1));
                    }
                    else if (time > loadingBarLength) {
                        if (j <= time % loadingBarLength)
                            draw = 0;
                        else
                            draw = time / loadingBarLength;
   
                    }
                    else
                        draw = 1;
                    for (int i = 0; i < draw; i++)
                    {
                        cout << char(219);
                    }
                    move += draw;
                    ASSISTANTFUNCTION_H::color(7);
                }
                cout << endl;
             
            }
            return;
        }

        friend ostream& operator<<(ostream& os, const Car& car) {
            os << "carID: " << car.carID << endl
                << "Color: " << car.color << endl
                << "----\n";
            return os;
        }
};

#endif 
