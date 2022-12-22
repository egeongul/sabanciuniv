#include "Driver.h"
#include <iostream>
using namespace std;

void Driver::drive(int km){
    myCar.travel(km);
}

void Driver::repairCar(string accident){
    if(accident == "SMALL"){
        budget -= 50;
        int insurance = myCar.raise(5);
        cout << "50$ is reduced from the driver's budget because of the SMALL accident"<< endl;
        cout << "Yearly insurance fee is increased to " << insurance << " because of the SMALL accident " << endl;
    }
    else if(accident == "MEDIUM"){
        budget -= 150;
        int insurance = myCar.raise(10);
        cout << "150$ is reduced from the driver's budget because of the MEDIUM accident"<< endl;
        cout << "Yearly insurance fee is increased to " << insurance << " because of the MEDIUM accident " << endl;
    }
    else if(accident == "LARGE"){
        budget -= 300;
        int insurance = myCar.raise(20);
        cout << "300$ is reduced from the driver's budget because of the LARGE accident"<< endl;
        cout << "Yearly insurance fee is increased to " << insurance << " because of the LARGE accident " << endl;
    }
};

void Driver::display(){
    cout << "Driver budget: " << budget;
}

void Driver::fullFuel(){
    double spent = myCar.fulle();
    spent = 300 - spent;
    budget -= spent;
    cout << "Fuel is full" << endl;
}
