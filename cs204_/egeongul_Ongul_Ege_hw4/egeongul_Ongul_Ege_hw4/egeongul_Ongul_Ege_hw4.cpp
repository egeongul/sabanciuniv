#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
#include "DynIntQueue.h"
#include "DynIntStack.h"
using namespace std;

DynIntStack commonStack;

struct node {
    
    string info;
    node* right;
    node* down;
    
    node(string _info, node* _down = NULL, node* _right = NULL){
        info = _info;
        down = _down;
        right = _right;
    }
};

bool ifExistHorizontal(node* head, string name){
    node* head2 = head;
    while(head2 != NULL){
        if(head2->info == name){
            return true;
        }else{
            head2 = head2->right;
        }
    }
    return false;
}


void printMenu(){
    cout << endl;
    cout<<"********************************************************************** "<<endl;
    cout <<"**************** 0 - EXIT PROGRAM " << endl;
    cout <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST " << endl;
    cout <<"**************** 2 - ADD A STUDENT SERVICE REQUEST " << endl;
    cout <<"**************** 3 - SERVE (PROCESS) A REQUEST " << endl;
    cout << "**********************************************************************"<<endl;
    cout << endl;
}

void serveTeacher(DynIntQueue teacher, string functionname, node* head2, node* head){
    head2 = head;
    string name, dummy, functionname2;
    while(head2->info != functionname){
        head2= head2->right;
    }
    head2 = head2->down;
    while(head2 != NULL){
        istringstream iss(head2->info);
        iss >> dummy;
        
        if(dummy == "define"){
            string push = functionname + ": " + head2->info;
            commonStack.push(push);
            cout << functionname << ": " << head2->info << endl;
        }
        else if(dummy == "print"){
            cout << "PRINTING THE STACK TRACE: " << endl;
            commonStack.printstack();
            cout << "------- PRINTED -------" << endl;
        }
        else if(dummy == "call"){
            cout << "Calling from " << functionname << " " ;
            node* head3 = head;
            StackNode* newNode = commonStack.top;
            iss >> functionname2; // say it fname2 because it has to return to its org value after it ends
            cout << functionname2 << "!!" << endl ;
            serveTeacher(teacher, functionname2, head3, head);
            commonStack.clearstack(newNode);
        }
        head2 = head2->down;
    }
    if(head2 == NULL){
        cout << functionname << " is finished. Clearing the stack from its data" << endl;
    }
}

// actually could of do both of them together but realised that later :(

void serveStudent(DynIntQueue student, string functionname, node* head2, node* head){
    head2 = head;
    string name, dummy, functionname2;
    while(head2->info != functionname){
        head2= head2->right;
    }
    head2 = head2->down;
    while(head2 != NULL){
        istringstream iss(head2->info);
        iss >> dummy;
        
        if(dummy == "define"){
            string push = functionname + ": " + head2->info;
            commonStack.push(push);
            cout << functionname << ": " << head2->info << endl;
        }
        else if(dummy == "print"){
            cout << "PRINTING THE STACK TRACE: " << endl;
            commonStack.printstack();
            cout << "------- PRINTED -------" << endl;
            
        }
        else if(dummy == "call"){
            cout << "Calling from " << functionname << " " ;
            node* head3 = head;
            StackNode* newNode = commonStack.top;
            iss >> functionname2;  // say it fname2 because it has to return to its org value after it ends
            cout << functionname2 << "!!" << endl;
            serveTeacher(student, functionname2, head3, head);
            commonStack.clearstack(newNode);
        }
        head2 = head2->down;
    }
    if(head2 == NULL){
        cout << functionname << " is finished. Clearing the stack from its data" << endl;
        commonStack.clearstack(NULL);
    }
}

int main(){
    
    char key;
    string filename, dummy, _info, teacherName, studentName, functionname;
    int teacherID, studentID;
    DynIntQueue teacherQueue, studentQueue;
    node* head = NULL;
    cout << "If you want to open a service <function> defining file,\nthen press <Y/y> for 'yes', otherwise press any single key" << endl;
    cin >> key;
    while(key == 'y' || key == 'Y'){
        cout << "Enter the input file name: " << endl;
        cin >> filename;
        ifstream inputFile;
        inputFile.open(filename.c_str());
        if(inputFile.is_open()){
            if(head == NULL){ // initializing is different from adding a node
                getline(inputFile, dummy);
                dummy.pop_back();
//                dummy.pop_back();
                head = new node(dummy);
                node* head2 = head;
                while(getline(inputFile, dummy)){
                    dummy.pop_back();
//                    dummy.pop_back();
                    node* temp = new node(dummy);
                    head2->down = temp;
                    head2 = temp;
                }
            }
            else{
                node* head2 = head;
                while(head2->right != NULL){ //sending head2 to the end and creating a new linked list from there
                    head2 = head2->right;
                }
                getline(inputFile, dummy);
                dummy.pop_back();
//                dummy.pop_back();
                head2->right = new node(dummy);
                head2 = head2->right;
                while(getline(inputFile, dummy)){
                    dummy.pop_back();
//                    dummy.pop_back();
                    node* temp = new node(dummy);
                    head2->down = temp;
                    head2 = temp;
                }
            }
        }
        else{
            cout << "File cannot opened!!!!" << endl;
            inputFile.close();
            return 0;
        }
        inputFile.close();
        cout << "If you want to open a service <function> defining file,\nthen press <Y/y> for 'yes', otherwise press any single key" << endl;
        cin >> key;
    }
    cout << "-------------------------------------------------------------------" << endl;
    cout << "PRINTİNG AVALİABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    node* head2 = head;
    while(head2 != NULL){  // head2 goes through top of the linked lists and head3 goes down for each linked list to print all of them
        node* head3 = head2;
        cout << head3->info << ":" << endl;
        head3 = head3->down;
        while(head3 != NULL){
            cout << head3->info << ", ";
            head3 = head3->down;
        }
        head2 = head2->right;
        cout << endl;
    }
    head2 = head;
    int option = 1;
    while(option == 1 || option == 2 || option == 3){
        printMenu();
        cout << "Pick an option from above <int number from 0 to 3> " << endl;
        cin >> option;
        if(option == 1){
            string function_name;
            cout << "Add a servive <function> that instructor wants to use: " << endl;
            cin >> function_name;
            if(ifExistHorizontal(head2, function_name)){
                cout << "Give the instructors name: " ;
                cin >> teacherName;
                cout << "Give the instructors ID <an int>: " ;
                cin >> teacherID;
                cout << "Prof. " << teacherName << "'s service request of " << function_name << " has been put in the instructors queue.\nWaiting to be served!!";
                teacherQueue.enqueue(teacherName, function_name, teacherID);
                head2 = head;
            }
            else{
                cout << "The requested service <function> does not exist\nGOİNG BACK TO MAİN MENU";
                head2 = head;
            }
        }
        else if(option == 2){
            string function_name;
            cout << "Add a servive <function> that student wants to use: " << endl;
            cin >> function_name;
            if(ifExistHorizontal(head2, function_name)){
                cout << "Give the student's name: " ;
                cin >> studentName;
                cout << "Give the student's ID <an int>: " ;
                cin >> studentID;
                cout << studentName << "'s service request of " << function_name << " has been put in the students queue.\nWaiting to be served!!";
                studentQueue.enqueue(studentName, function_name, studentID);
                head2 = head;
            }
            else{
                cout << "The requested service <function> does not exist\nGOİNG BACK TO MAİN MENU";
                head2 = head;
            }
        }
        else if(option == 3){
            if(!teacherQueue.isEmpty()){
                head2 = head;
                teacherQueue.dequeue(teacherName, functionname, teacherID);
                cout << "Processing prof." << teacherName << "'s request <with ID " << teacherID << "> of service <function>: " << endl;
                cout << functionname << endl;
                serveTeacher(teacherQueue, functionname, head2, head);
                commonStack.clearstack(NULL);
            }
            else if(!studentQueue.isEmpty()){
                head2 = head;
                studentQueue.dequeue(studentName, functionname, studentID);
                cout << "Processing " << studentName << "'s request <with ID " << studentID << "> of service <function>: " << endl;
                cout << functionname << endl;
                serveStudent(studentQueue, functionname, head2, head);
                commonStack.clearstack(NULL);
            }
            else{
                cout << "Both instructors and students queue is empty\nNo request is processed\nGoing back to MAIN MENU" << endl;
            }
        }
    }
    if(option == 0){
        head2 = head;
        while(head2 != NULL){
            node* head3 = head2->down;
            while(head3 != NULL){
                node* temp = head3;
                head3 = head3->down;
                delete temp;
            }
            node* temp = head2;
            head2 = head2->right;
            delete temp;
        }
        cout << "Exiting program..." << endl;
    }
    return 0;
}
