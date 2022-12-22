#include <iostream>
#include "Car.h"


Car::Car(int initFuel, int insurance, int travelled){
    myInsurance = insurance;
    myFuel = initFuel;
    myTravelled = travelled;
}

void Car::display(){
    cout << "Fuel Level: " << myFuel << endl;
    cout << "Insurance Fee: " << myInsurance << endl;
    cout << "Total distance that the car has travelled: " << myTravelled << endl;
}

void Car::travel(int km){
    myTravelled += km;
    myFuel -= (km* 0.25);
}

int Car::raise(int num){
    myInsurance = (myInsurance*(100+num))/100;
    return myInsurance;
}

double Car::fulle(){
    double now = myFuel;
    myFuel = 300;
    return now;
}
