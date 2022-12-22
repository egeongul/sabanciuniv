
// Ege Ongul 29037

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
using namespace std;

vector<int> newRemovedVector(vector<int> & s, int num){
    
    for(int i = 0; i < s.size(); i++){
        int temp = s[i];
        if(s[i] == num){
            s[i] = s[i+1];
            s[i+1] = temp;
        }
    }
    s.pop_back();
    return s;
}

bool ifExist(int sayi, vector<int> s){
    
    for(int i = 0; i< s.size(); i++){
        if(s[i] == sayi){
            return true;
        }
    }
    return false;
}

bool ifExistString(string sayi, vector<string> s){
    
    for(int i = 0; i< s.size(); i++){
        if(s[i] == sayi){
            return true;
        }
    }
    return false;
}

int wordCounter(string s){
    
    int counter = 0;
    
    unsigned long int length = s.length()-1;
    for(int i = 0; i < length; i++){
        if(s[i] == ' '){
            counter++;
        }
    }
    return counter + 1;
}


void printMenu(){
    cout << "1. Add to List" << endl;
    cout << "2. Drop from List" << endl;
    cout << "3. Display List" << endl;
    cout << "4. Finish Add/Drop and Exit" << endl;
}

void vectorSort(vector<int> & vector){  //insertion sort function from cs201
    int k, loc, numElts = int(vector.size());
    for(k = 1; k < numElts; k++ ){
        int hold = vector[k];
        loc = k;
        while(0 < loc && hold < vector[loc-1]){
            vector[loc] = vector[loc-1];
            loc--;
        }
        vector[loc] = hold;
    }
}

void vectorSortString(vector<string> & vector){  //insertion sort function from cs201
    int k, loc, numElts = int(vector.size());
    for(k = 1; k < numElts; k++ ){
        string hold = vector[k];
        loc = k;
        while(0 < loc && hold < vector[loc-1]){
            vector[loc] = vector[loc-1];
            loc--;
        }
        vector[loc] = hold;
    }
}

int main() {
    
    
    
    ifstream file;
    string filename, line, courseCode, courseName, StudentID;
    int choice;
    
    struct courseNode{
        string courseCode, courseName;
        vector<int> studentsAttendingIDs;
        courseNode * next;
        
        courseNode(string x, string y, vector<int> t, courseNode * linker):
        courseCode(x), courseName(y), studentsAttendingIDs(t), next(linker)
        {}
        
    };
    
    courseNode * head = NULL;
    courseNode * temp = NULL;
    
    cout << "Please enter file name: " ;
    cin >> filename;
//    filename = "coursesAndStudents.txt";   // inputla alıncak şimdilik kalsın
    
    cout << "Successfully opened file " << filename  << endl;
    cout << "The linked list is created." << endl;
    cout << "The initial list is:" << endl ;
    
    vector<string> storage;
    
    file.open(filename.c_str());
    
    while(getline(file, line)){
        if(!line.empty() && line != "\0"){
            istringstream alanur(line);
            string courseCode, courseName, StudentID;
            
            vector<int> studentsAttendingIDs ;
            alanur >> courseCode >> courseName >> StudentID;
            courseNode * head2 = head;
            
            while(head2 != NULL){
                if(head2->courseCode == courseCode){
                    if(!ifExist(atoi(StudentID), head2->studentsAttendingIDs)){
                        head2->studentsAttendingIDs.push_back(atoi(StudentID));
                    }
                    break;
                }
                else{
                    head2 = head2 ->next;
                }
            }
            
            if(head2 == NULL){
                temp = new courseNode(courseCode, courseName, studentsAttendingIDs, head);
                temp->studentsAttendingIDs.push_back(atoi(StudentID));
                head = temp;
            }
        }
    }head = head->next;
    courseNode * head2 = head;
    
    while(head2 != NULL){
        cout << head2->courseName << "  " << head2->courseCode << ": " ;
        
        //        int size = head->studentsAttendingIDs.size();
        vectorSort(head2->studentsAttendingIDs);
        for(int i=0; i< head2->studentsAttendingIDs.size(); i++ ){
            cout << head2->studentsAttendingIDs[i] << "  ";
        }
        if(!ifExistString(head2->courseName, storage)){
            storage.push_back(head2->courseName);
        }
        cout << endl;
        head2 = head2->next;
    }cout << endl;
    head2 = head;
    file.close();
    cout << "Please select one of the choices:" << endl;
    printMenu();
    cin >> choice;
    vector<int> studentsAttendingIDs ;
    while(choice != 4){
        
        if(choice == 1){
            head2 = head;
            string str;
            cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
            cin >> str;
            courseCode = str;
            getline(cin, str);
            istringstream iss(str);
            string subs;
            
            while (iss >> subs){
                if(subs.length() <= 7 && subs[0] > 64 ){
                    courseCode = subs;
                }
                else if(subs.length() > 5 && subs[0] > 64){
                    courseName = subs;
                }
                else if(subs.length() == 5 && subs[0] < 58){
                    StudentID = subs;
                    head2 = head;
                    while(head2 != NULL){
                        if(head2->courseCode == courseCode){
                            if(!ifExist(atoi(StudentID), head2->studentsAttendingIDs)){
                                head2->studentsAttendingIDs.push_back(atoi(StudentID));
                                vectorSort(head2->studentsAttendingIDs);
                                cout << "Student with id " << StudentID << " is enrolled to " << courseCode << endl;
                            }
                            else{
                                cout << "Student with id " << StudentID << " already is enrolled to " << courseCode << ". No action taken." << endl;
                            }
                            break;
                        }
                        else{
                            head2 = head2->next;
                        }
                    }
                    if(head2 == NULL){
                        temp = new courseNode(courseCode, courseName, studentsAttendingIDs, head);
                        temp->studentsAttendingIDs.push_back(atoi(StudentID));
                        head = temp;
                        head2 = head;
                        cout << courseCode << " does not exist in the list of Courses. It is added up." << endl;
                        cout << "Student with id " << StudentID << " is enrolled to " << courseCode << endl;
                        if(!ifExistString(head2->courseName, storage)){
                            storage.push_back(head2->courseName);
                        }
                        
                    }
                }
            }
        }
        
        else if (choice == 2){
            head2 = head;
            string str;
            cout << "Give the student ID and the course names and course codes that he/she wants to drop: "<< endl;
            cin >> str;
            courseCode = str;
            getline(cin, str);
            istringstream iss(str);
            string subs;
            
            while (iss >> subs){
                if(subs.length() <= 7 && subs[0] > 64 ){
                    courseCode = subs;
                }
                else if(subs.length() > 5 && subs[0] > 64){
                    courseName = subs;
                }
                else if(subs.length() == 5 && subs[0] < 58){
                    StudentID = subs;
                    head2 = head;
                    while(head2 != NULL){
                        if(head2->courseCode == courseCode){
                            if(ifExist(atoi(StudentID), head2->studentsAttendingIDs)){
                                newRemovedVector(head2->studentsAttendingIDs, atoi(StudentID));
                                cout << "Student with id " << atoi(StudentID) << " has dropped " << courseCode << "." << endl;
                            }
                            else{
                                cout << "Student with id " << atoi(StudentID) << " is not enrolled to " << courseCode << ", thus he can't drop that course." << endl;
                            }
                            break;
                        }
                        else{
                            head2 = head2->next;
                        }
                    }
                    if(head2 == NULL){
                        head2 = head;
                        cout << "The " << courseCode << " course is not in the list, thus student with id " << atoi(StudentID) << " can’t be dropped" << endl;
                        
                    }
                }
                
            }
        }
        
        else if (choice == 3){
            vectorSortString(storage);
            cout << "The current list of course and the students attending them: " << endl;
            head2 = head;

            for(int i = 0; i < storage.size(); i++){  // printing the sorted list
                head2 = head;
                while(head2 != NULL){
                    if(head2->courseName == storage[i]){
                        cout << head2->courseCode << "  " << head2->courseName << ": " ;
                        vectorSort(head2->studentsAttendingIDs);
                        for(int i=0; i< head2->studentsAttendingIDs.size(); i++ ){
                            cout << head2->studentsAttendingIDs[i] << "  ";
                        }
                        cout << endl;
                        break;
                    }
                    else{
                        head2 = head2->next;
                    }
                }
            }
        }
            cout << endl ;
            cout << "Please select one of the choices:" << endl;
            printMenu();
            cin >> choice;
        
    }
        if(choice == 4){
            
            cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
            cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
            for(int i = 0; i < storage.size(); i++){  // printing the sorted list
                head2 = head;
                while(head2 != NULL){
                    if(head2->courseName == storage[i]){
                        if(head2->studentsAttendingIDs.size() > 2){
                            cout << head2->courseCode << "  " << head2->courseName << ": " ;
                            vectorSort(head2->studentsAttendingIDs);
                            for(int i=0; i< head2->studentsAttendingIDs.size(); i++ ){
                                cout << head2->studentsAttendingIDs[i] << "  ";
                            }
                        }
                        else{
                            cout << head2->courseCode << " " << head2->courseName << " ";
                            for(int i=0; i< head2->studentsAttendingIDs.size(); i++ ){
                                cout << head2->studentsAttendingIDs[i] << "  ";
                            }
                            cout << " -> This course will be closed" ;
                        }
                        cout << endl;
                        break;
                    }
                    else{
                        head2 = head2->next;
                    }
                }
            }
        }
    return 0;
}
