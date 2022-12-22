#ifndef Driver_h
#define Driver_h

#include <string>
#include <iostream>
using namespace std;
#include "Car.h"
class Driver{
    
public:
    
    Driver(Car &carName, double initBudget) //constructor
    : myCar(carName), budget(initBudget)
    {};
    void drive(int km);
    void repairCar(string accident);
    void display();
    void fullFuel();
    
private:
    double budget;
    Car &myCar;
};



#endif /* Driver_h */
