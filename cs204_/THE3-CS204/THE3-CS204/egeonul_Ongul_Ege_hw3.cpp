
// Ege Ongul 29037

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
using namespace std;

//-------------------------FONKSİYONLAR

void printMainMenu() {
    cout << endl;
    cout <<"I***********************************************I"<<endl <<"I 0 - EXIT PROGRAM I"<<endl
    <<"I 1 - PRINT LINES I"<<endl
    <<"I 2 - ADD BUS LINE I"<<endl
    <<"I 3 - ADD BUS STOP I"<<endl
    <<"I 4 - DELETE BUS LINE I"<<endl
    <<"I 5 - DELETE BUS STOP I"<<endl
    <<"I 6 - PATH FINDER I"<<endl <<"I***********************************************I"<<endl <<">>";
    cout << endl;
}

struct busStop {
    string busStopName;
    busStop *left;
    busStop *right;
    
    busStop(string s, busStop* t, busStop* y){
        busStopName = s;
        right = t;
        left = y;
    }
};

struct busLine {
    string busLineName;
    busLine *next;
    busStop *busStops;
    
    busLine(string s, busLine* t, busStop* y){
        busLineName = s;
        next = t;
        busStops = y;
    }
    busLine();
};

bool ifExist(string s, busLine* kafa){ // to check if busline exist
    while(kafa != NULL){
        if(kafa->busLineName == s){
            return true;
        }
        else{
            kafa = kafa->next;
        }
    }
    return false;
}

bool ifExistHorizontal(string s, busStop* kafa){ //to check if busstop exist in busline(horizontal)
    
    while(kafa != NULL){
        if(kafa->busStopName == s){
            return true;
        }
        else{
            kafa = kafa->right;
        }
    }
    
    return false;
}
bool ifExistALL(string s, busLine* kafa){ // to check if busstop exist in all bus lines
    
    while(kafa != NULL){
        busStop* head3 = kafa->busStops;
        if(ifExistHorizontal(s, head3)){
            return true;
        }
        else{
            kafa = kafa->next;
        }
    }
    
    return false;
}

//--------------------------FONKSİYONLAR

int main() {
    
    fstream file;
    string filename = "busLines.txt";
    string line, str, busName, busStops;
    int choice;
    busLine* head = new busLine("kafa", NULL, NULL);
    busLine* temp = NULL;
    busLine* head2 = head;
    file.open(filename.c_str());
    
    while(getline(file, line)){
        istringstream alanur(line);
        busStop* head3 = NULL;
        busStop* temp2 = NULL;
        while(alanur >> str){
            if(str[0] < 58 && str[0] > 47){
                str.pop_back();
                temp = new busLine(str, NULL, NULL);
                head2 ->next = temp;
                head2 = temp;
            }
            
            else{
                if(head3 == NULL){
                    temp2 = new busStop(str, NULL, NULL);
                    head2->busStops = temp2;
                    head3 = temp2;
                }
                else{
                    temp2 = new busStop(str, NULL, head3);
                    head3->right = temp2;
                    head3 = temp2;
                }
            }
        }
    }
    head = head->next;
    head2 = head;
    file.close();
    
    choice = 1;
    while(choice > 0 && choice < 7){
        printMainMenu();
        cout << "Please enter your option: " << endl;
        cin >> choice;
        if(choice == 1){
            head2 = head;
            while(head2 != NULL){ //printing all the bus lines and their stops
                cout << head2->busLineName << ": " ;
                busStop* head3 = head2->busStops;
                while(head3 != NULL){
                    cout << head3->busStopName << " ";
                    head3 = head3->right;
                    if(head3 != NULL){
                        cout << "<->";
                    }
                }
                cout << endl;
                head2 = head2->next;
            }
        }
        else if(choice == 2){
            string newBusline;
            head2 = head;
            cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
            cin >> newBusline;
            while(newBusline != "0"){
                while(ifExist(newBusline, head2)){
                    cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
                    cin >> newBusline;
                }
                if(!ifExist(newBusline, head2)){
                    temp = new busLine(newBusline, head, NULL);
                    head = temp;
                    head2 = head;
                    busStop * head3 = NULL;
                    busStop * temp2 = NULL;
                    head2->busStops = NULL ;
                    string newBusStop;
                    cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
                    cin >> newBusStop;
                    while(newBusStop != "0"){
                        if(!ifExistHorizontal(newBusStop, head2->busStops)){
                            if(head2->busStops == NULL){    // if busline empty
                                temp2 = new busStop(newBusStop, NULL, NULL);
                                head2->busStops = temp2;
                                head3 = temp2;
                            }
                            else{ // busline da en az 1 busstop varsa
                                temp2 = new busStop(newBusStop, NULL, head3);
                                head3->right = temp2;
                                head3 = temp2;
                            }
                            cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl ;
                            cin >> newBusStop;
                        }
                        else{
                            cout << "Bus stop already exists in the line" << endl;
                            cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
                            cin >> newBusStop;
                        }
                    }
                    if(newBusStop == "0"){
                        cout << "The bus line information is shown below" << endl;
                        head3 = head->busStops;
                        cout << head->busLineName << ": " ;
                        while(head3 != NULL){
                            cout << head3->busStopName ;
                            head3 = head3->right;
                            if(head3 != NULL){
                                cout << "<->";
                            }
                        }newBusline = "0";
                    }
                }
            }
        }
        else if (choice == 3){
            head2 = head;
            string newBusStop, newBusLine;
            cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
            cin >> newBusLine;
            if(ifExist(newBusLine, head)){ // check if busline exists
                while(head2->busLineName != newBusLine){ //send head2 to its destination
                    head2 = head2->next;
                }
                busStop * head3;
                busStop * temp2;
                head3 = head2->busStops;
                temp2 = head3;
                cout << head2->busLineName << ": " ;
                while(head3 != NULL){  // busline printed
                    cout << head3->busStopName ;
                    head3 = head3->right;
                    if(head3 != NULL){
                        cout << "<->";
                    }
                }
                cout << endl;
                head3 = head2->busStops;
                cout << "Enter the name of the new bus stop:" << endl;
                cin >> newBusStop;
                if(ifExistHorizontal(newBusStop, head3)){
                    cout << "Bus stop already exists. Going back to previous menu." << endl;
                }
                else{
                    head3 = head2->busStops;
                    string prevBusStop;
                    cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop):" << endl;
                    cin >> prevBusStop;
                    if(prevBusStop == "0"){
                        temp2 = new busStop(newBusStop, head3, NULL);
                        head2->busStops = temp2;
                        head3->left = temp2;
                        head3 = temp2;
                        head2 = head;
                        while(head2 != NULL){ // print lines
                            cout << head2->busLineName << ": " ;
                            busStop* head3 = head2->busStops;
                            while(head3 != NULL){
                                cout << head3->busStopName << " ";
                                head3 = head3->right;
                                if(head3 != NULL){
                                    cout << " <-> ";
                                }
                            }
                            cout << endl;
                            head2 = head2->next;
                        }
                    }
                    else{
                        head3 = head2->busStops;
                        if(ifExistHorizontal(prevBusStop, head3)){
                            while(head3->busStopName != prevBusStop){
                                head3 = head3->right;
                            }
                            temp2 = new busStop(newBusStop, head3->right, head3);
                            head3->right->left = temp2;
                            head3->right = temp2;
                            head2 = head;
                            while(head2 != NULL){ // debug session
                                cout << head2->busLineName << ": " ;
                                busStop* head3 = head2->busStops;
                                while(head3 != NULL){
                                    cout << head3->busStopName << " ";
                                    head3 = head3->right;
                                    if(head3 != NULL){
                                        cout << " <-> ";
                                    }
                                }
                                cout << endl;
                                head2 = head2->next;
                            }
                        }
                        else{
                            cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)";
                            cin >> prevBusStop;
                            while(!ifExistHorizontal(prevBusStop, head3) && prevBusStop != "0"){
                                cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)";
                                cin >> prevBusStop;
                            }
                            head3 = head2->busStops;
                            if(ifExistHorizontal(prevBusStop, head3)){
                                while(head3->busStopName != prevBusStop){
                                    head3 = head3->right;
                                }
                                temp2 = new busStop(newBusStop, head3->right, head3);
                                head3->right->left = temp2;
                                head3->right = temp2;
                                head2 = head;
                                while(head2 != NULL){ // debug session
                                    cout << head2->busLineName << ": " ;
                                    busStop* head3 = head2->busStops;
                                    while(head3 != NULL){
                                        cout << head3->busStopName << " ";
                                        head3 = head3->right;
                                        if(head3 != NULL){
                                            cout << " <-> ";
                                        }
                                    }
                                    cout << endl;
                                    head2 = head2->next;
                                }
                            }
                            else if(prevBusStop == "0"){
                                cout << "Going back to main menu" << endl;
                            }
                        }
                    }
                }
            }
            else{
                cout << "Bus line cannot be found. Going back to previous menu." << endl;
            }
        }
        else if(choice == 4){
            head2 = head;
            string deleteBusLine;
            cout << "Enter the name of the bus line to delete: " << endl;
            cin >> deleteBusLine;
            if(ifExist(deleteBusLine, head)){
                if(head2->busLineName == deleteBusLine){
                    busStop * head3 = NULL;
                    busStop * temp2 = NULL;
                    head2->busStops = head3;
                    temp2 = head3;
                    while(head3 != NULL){ //first send head3 to right and delete the old head3 (we need temp to stay at old head3)
                        head3 = head3->right;
                        delete temp2;
                        temp2 = head3;
                    }
                    if(head3 == NULL){
                        delete head3;
                    }
                    delete head->busStops;
                    temp = head->next;
                    delete head;
                    head = temp;
                }
                else{
                    while(head2->next->busLineName != deleteBusLine){
                        head2 = head2->next;
                    }
                    busStop * head3 = NULL;
                    busStop * temp2 = NULL;
                    head2->next->busStops = head3;
                    temp2 = head3;
                    while(head3 != NULL){
                        head3 = head3->right;
                        delete temp2;
                        temp2 = head3;
                    }
                    if(head3 == NULL){
                        delete head3;
                    }
                    delete head2->busStops;
                    head2->next = head2->next->next;
                    delete head2->next;
                }
                head2 = head;
                while(head2 != NULL){ // print all lines
                    cout << head2->busLineName << ": " ;
                    busStop* head3 = head2->busStops;
                    while(head3 != NULL){
                        cout << head3->busStopName << " ";
                        head3 = head3->right;
                        if(head3 != NULL){
                            cout << " <-> ";
                        }
                    }
                    cout << endl;
                    head2 = head2->next;
                }
            }
            else{
                cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
            }
        }
        else if(choice == 5){
            head2 = head;
            string deleteBusLineFrom, deleteBusStop;
            cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
            cin >> deleteBusLineFrom;
            if(ifExist(deleteBusLineFrom, head2)){
                while(head2->busLineName != deleteBusLineFrom){
                    head2 = head2->next;
                }
                busStop * head3 = NULL;
                busStop * temp2 = NULL;
                cout << "The bus line information is shown below" << endl;
                head3 = head2->busStops;
                cout << head2->busLineName << ": " ;
                while(head3 != NULL){ //sellected line print
                    cout << head3->busStopName ;
                    head3 = head3->right;
                    if(head3 != NULL){
                        cout << "<->";
                    }
                }
                cout << endl;
                cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
                cin >> deleteBusStop;
                head3 = head2->busStops;
                while(deleteBusStop != "0"){
                    while(!ifExistHorizontal(deleteBusStop, head3)){
                        cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
                    }
                    if(deleteBusStop != "0"){
                        
                        if(head3->busStopName == deleteBusStop){
                            head2->busStops = head3->right;
                            head3->right->left = NULL;
                            temp2 = head3->right;
                            delete head3;
                            head3 = temp2;
                        }
                        else{
                            while(head3->right->busStopName != deleteBusStop){
                                head3 = head3->right;
                            }
                            head3->right = head3->right->right;
                            head3->right->right->left = head3;
                            temp2 = head3->right;
                            delete head3;
                            head3 = temp2;
                        }
                        head2 = head;
                        while(head2 != NULL){ // debug session
                            cout << head2->busLineName << ": " ;
                            busStop* head3 = head2->busStops;
                            while(head3 != NULL){
                                cout << head3->busStopName << " ";
                                head3 = head3->right;
                                if(head3 != NULL){
                                    cout << " <-> ";
                                }
                            }
                            cout << endl;
                            head2 = head2->next;
                        }
                        deleteBusStop = "0";
                    }
                }
            }
            else{
                cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
            }
        }
        else if(choice == 6){
            head2 = head;
            string currentBusStop, wantedBusStop;
            cout << "Where are you now?" << endl;
            cin >> currentBusStop;
            if(!ifExistALL(currentBusStop, head2)){
                cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
            }
            else{
                head2 = head;
                cout << "Where do you want to go?" << endl;
                cin >> wantedBusStop;
                if(!ifExistALL(wantedBusStop, head2)){
                    cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
                }
                else{
                    head2 = head;
                    while(head2 != NULL){
                        busStop * head3 = NULL;
                        busStop * temp2 = NULL;
                        head3 = head2->busStops;
                        temp2 = head3;
                        
                        if(ifExistHorizontal(currentBusStop, head3) && ifExistHorizontal(wantedBusStop, head3)){
                            cout << "You can go there by " <<  head2->busLineName << ": ";
                            while(head3->busStopName != currentBusStop && head3->busStopName != wantedBusStop){ //send head3 to right until it
                                head3 = head3->right;                                                           // comes one of them
                            }
                            if(head3->busStopName == currentBusStop){                                           //if it is current stop, send it
                                while(head3->busStopName != wantedBusStop){                                     //until it is wanted stop and print
                                    cout << head3->busStopName;
                                    if(head3->busStopName != wantedBusStop){
                                        cout << " <-> ";
                                    }
                                    head3 = head3->right;
                                }
                                cout << head3->busStopName;
                            }
                            else if(head3->busStopName == wantedBusStop){                                       //if it is wanted stop, send it
                                while(head3->busStopName != currentBusStop){                                    //until it is current stop than
                                    head3 = head3->right;                                                       //come back with printing until
                                }                                                                               //wanted stop
                                while(head3->busStopName != wantedBusStop){
                                    cout << head3->busStopName;
                                    if(head3->busStopName != wantedBusStop){
                                        cout << " <-> ";
                                    }
                                    head3 = head3->left;
                                }
                                cout << head3->busStopName;
                            }
                            break;
                        }
                        else{
                            head2 = head2->next;
                        }
                        if(head2 == NULL){
                            cout << "Sorry not path from " << currentBusStop << " to " << wantedBusStop;
                            cout << " could be found" << endl;
                        }
                    }
                    
                }
            }
        }
    }
    head2 = head;
    while(head != NULL){
        busStop* head3 = head->busStops;
        while(head3 != NULL){
            busStop* temp2 = head3;
            head3 = head3->right;
            delete temp2;
            temp2 = head3;
        }
        head = head->next;
        head2 = head;
    }
    return 0;
}
