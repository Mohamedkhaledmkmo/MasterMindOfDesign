#ifndef operation_H
#define operation_H

#include <string>
#include <iostream>
#include <limits> 
using namespace std;

class Operation {
private:
	string name;
	size_t time;
	string description;

public:
	Operation():time(0) {
	}

	Operation(string initName, size_t initTime, string initDesc) : name(initName), time(initTime), description(initDesc) {}
	
	string getName() { return name; }
	
	size_t getTime() { return time; }
	
	string getDescription() { return description; }
	
	void getDetails() {
		cout << "Name: " << name << "\nTime: " << time << "\nDescripion: " << description << "\n";
	}
	

	friend std::ostream& operator<<(std::ostream& os, const Operation& operation) {
        os << "Operation: " << operation.name << endl
           << "Time: " << operation.time << endl
           << "Description: " << operation.description << endl << endl;
        return os;
    }
};


#endif