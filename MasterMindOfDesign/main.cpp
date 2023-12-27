#include <iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include "Factory.h"
#include "assistantFunctions.h"
using namespace std;
// Text ui functions
void startScreen() {
    string gigaFactory = "\n\n\t\t\t\t  _____ _            ______         _                   \n\t\t\t\t |  __ (_)           |  ___|       | |                  \n\t\t\t\t | |  \\/_  __ _  __ _| |_ ___   ___| |_ ___  _ __ _   _ \n\t\t\t\t | | __| |/ _` |/ _` |  _/ _ \\ / __| __/ _ \\| '__| | | |\n\t\t\t\t | |_\\ \\ | (_| | (_| | || (_) | (__| || (_) | |  | |_| |\n\t\t\t\t  \\____/_|\\__, |\\__,_\\_| \\___/ \\___|\\__\\___/|_|   \\__, |\n\t\t\t\t           __/ |                                   __/ |\n\t\t\t\t          |___/                                   |___/ \n";
    cout << gigaFactory;
    system("color 0e");
    int bar1 = 177, bar2 = 219;
    cout << "\n\n\t\t\t\t\t\t\tLoading....";
    cout << "\n\t\t\t\t\t\t";
    for (int i = 0; i < 25; i++)
        cout << char(bar1);

    cout << "\r\t\t\t\t\t\t";
    for (int i = 0; i < 25; i++)
    {
        Sleep(100);
        cout << char(bar2);
    }
    system("cls");
    system("color 0F");
    return;
}
void screenBAR(string updated) {
    gotoXY(0, 0);
    color(7);
    string c = "";
    cout << "_______GigaFactory" << updated << setw(30 - updated.length()) << setfill('_') << c << setfill(' ') << "_____________________________________________________\n";

}

//menu funtions
void gigaFactoryInfo() {
    gotoXY(0, 16);
    cout << "- A Tesla Gigafactory is a massive manufacturing facility operated by Tesla Inc." << endl
        << "   These factories are designed to produce electric vehicles, batteries, and energy storage products" << endl
        << "   on a large scale. The term ""Gigafactory"" comes from the prefix ""giga - """ << endl
        << "   representing a billion, indicating the huge scale of production these facilities aim for." << endl;
}
void  itemExeute(Factory* main , int itemNumber)
{
    switch (itemNumber)
    {
    case 0:
        system("cls");
        screenBAR("----->Production line");
        main->startProduction();
        system("cls");
        main->statisticsBar();
        screenBAR("");
        break;
    case 1:
        system("cls");
        screenBAR("----->Add car");
        main->addCar();
        system("cls");
        main->statisticsBar();
        screenBAR("");
        break;
    case 2:
        system("cls");
        screenBAR("----->Warehouse");
        main->showFinishedCars();
        system("cls");
        main->statisticsBar();
        screenBAR("");
        break;
    case 3:
        system("cls");
        screenBAR("----->Operations info");
        main->showFactoryOperations();
        system("cls");
        main->statisticsBar();
        screenBAR("");
        break;
    case 4:
        gigaFactoryInfo();
        break;
    case 5:
        system("cls");
        break;
    default:
        break;
    }
}
void mainMenu(int xCoord, int ycoord, string menuItems[], int numOfItems, void(*execution_switch_function)(Factory* main, int _case), Factory* main){

    int* colors = new int[numOfItems];                           // holds the colors of items
    int counter = 0;                                             // indicates the selected item
    char key = 0;                                                    // stores the keyboard key

    // initialize the items color
    colors[0] = 10;  // 1st item will be selected by default
    for (int i = 1; i < numOfItems; i++)
    {
        colors[i] = 7;
    }

    // menu printing
    while (true)
    {
        color(7);
        gotoXY(xCoord-1, ycoord + counter * 2);
        cout << ">";
        gotoXY(xCoord + menuItems[counter].length() , ycoord + counter * 2);
        cout << "<" << endl;

        for (int i = 0; i < numOfItems; i++)
        {
            gotoXY(xCoord, ycoord + (i * 2));
            color(colors[i]);
            cout << menuItems[i];
        }

        for (int i = 0; i < numOfItems; i++)
            colors[i] = 7;

        char key = _getch();


        gotoXY(xCoord-1, ycoord + counter * 2);
        cout << " ";
        gotoXY(xCoord + menuItems[counter].length() , ycoord + counter * 2);
        cout << " ";
        if (counter==4)
        {
            partialScreenClear(14,6);
        }

        if (key == 72)
            counter = ((counter - 1) + numOfItems) % numOfItems;
        else if (key == 80)
            counter = (counter + 1) % numOfItems;
        else if (key == '\r')
        {
            color(7);
            execution_switch_function(main,counter);
            if (counter == 5) break;
        }
        if (counter >= 0 && counter < numOfItems)
            colors[counter] = 10;


    }
}
int main()

{
    ShowConsoleCursor(false);
    startScreen();
    screenBAR("");
    Factory* GigaFactory = new Factory;
    GigaFactory->statisticsBar();
    string arr[] = { "Start the production" , "Add a new car to the production line" , "Show the finished cars" , "Show car manufacture operations info" , "Show the Gigafactory info" ,"Exit" };
    mainMenu(1, 3, arr, 6, itemExeute, GigaFactory);
    return 0;
}
