#ifndef Car_h
#define Car_h

using namespace std;
#include <iostream>
#include <string>

class Car{
public:
    Car(int initFuel, int insurance, int travelled);
    void display();
    void travel(int);
    int raise(int);
    double fulle();
private:
    double myFuel;
    int myInsurance;
    int myTravelled;
};


#endif 
