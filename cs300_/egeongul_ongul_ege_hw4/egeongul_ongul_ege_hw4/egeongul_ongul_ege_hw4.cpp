

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
#include "Sort.h"



class phoneBook{
public:
    string name;
    string surname;
    string phoneNum;
    string city;
    phoneBook(string s1 = "", string s2 = "", string s3 = "", string s4 = ""){
        name = s1;
        surname = s2;
        phoneNum = s3;
        city = s4;
    }
    bool operator > (const phoneBook & compare ){
        string name1 = "";
        string name2 = "";
        name1 = this->name + this->surname;
        name2 = compare.name + compare.surname;
        bool alanur = CompareSTR(name1, name2);
        return alanur;
    };
    bool operator < (const phoneBook & compare ){
        string name1 = "";
        string name2 = "";
        name1 = this->name + this->surname;
        name2 = compare.name + compare.surname;
        bool alanur = CompareSTR(name1, name2);
        return !alanur;
    };
    phoneBook & operator = (phoneBook & temp){
        this->name = temp.name;
        this->surname = temp.surname;
        this->phoneNum = temp.phoneNum;
        this->city= temp.city;
        return *this;
    }
};

struct timeStr{
    string name;
    unsigned long int time;
    
};

void makeEmpty(vector<phoneBook> & t){
    for(int i = 0; i < t.size(); i++){
        t.pop_back();
    }
}

void equal(vector<phoneBook> & t, vector<phoneBook> org){
//    makeEmpty(t);
    t.clear();
    for(int i = 0; i < org.size(); i++)
        t.push_back(org[i]);
}
void printVect(vector<phoneBook> & t){
    if(!t.empty()){
        for(int i = 0; i < t.size(); i++){
            cout << t[i].name << " " << t[i].surname << endl;
        }
    }
    
}



int main() {
    
    string line, name, surname, phone, city, query, filename, words, myName, mySurname;
    cout << "Please enter the contact file name: " ;
    cin >> filename;
    cout << endl << "Please enter the word to be queried : " ;
    cin.ignore();
    getline(cin, query);
    ifstream input;
    vector<phoneBook> insertionVect;
    vector<phoneBook> quickVect;
    vector<phoneBook> mergeVect;
    vector<phoneBook> heapVect;
    map<string, unsigned long int> map;
    input.open(filename.c_str());
    while (getline(input, line)) {
        istringstream iss(line);
        iss >> name >> surname >> phone >> city;
        phoneBook myBook(name, surname, phone, city);
        insertionVect.push_back(myBook);
        quickVect.push_back(myBook);
        mergeVect.push_back(myBook);
        heapVect.push_back(myBook);
    }
    input.close();
    
    vector<phoneBook> copyVect1; // insertion sort vect
    vector<phoneBook> copyVect2; // heap sort vect
    vector<phoneBook> copyVect3; // merge  sort vect
    vector<phoneBook> copyVect4; // quick sort vect
    cout << "Sorting the vector copies" << endl;
    cout << "======================================" << endl;
    vector<unsigned long int> timeVect;
    int N = 100;
    
    // insertion sort below
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        equal(copyVect1, insertionVect);
        insertionSort(copyVect1);
    }
    auto stop = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start);
    cout << "Insertion Sort Time: " << stop.count()/N << " Nanoseconds." << endl;
    map["insertion_time"] = stop.count()/N;
    // heap sort below
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        equal(copyVect2, heapVect);
        heapsort(copyVect2);
    }
    stop = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start);
    cout << "Heap Sort Time: " << stop.count()/N << " Nanoseconds." << endl;
    map["heap_time"] = stop.count()/N;
    // merge sort below
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        equal(copyVect3, mergeVect);
        mergeSort(copyVect3);
    }
    stop = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start);
    cout << "Merge Sort Time: " << stop.count()/N << " Nanoseconds." << endl;
    map["merge_time"] = stop.count()/N;
    // quick sort below
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        equal(copyVect4, mergeVect);
        quicksort(copyVect4);
    }
    stop = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start);
    cout << "Quick Sort Time: " << stop.count()/N << " Nanoseconds." << endl;
    map["quick_time"] = stop.count()/N;
    int count = 0;
    istringstream iss(query);
    while(iss >> words)
        count++;
    cout << "Searching for " << query << endl;
    cout << "======================================" << endl;
    
    if(count == 1){
        start = std::chrono::high_resolution_clock::now();
        if(!sequentialSearch(copyVect1, query)){
            cout << query << " does not exist in the dataset." << endl;
        }
        stop = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() -
         start);
        cout << "Sequential Search Time: " << stop.count()/N << " Nanoseconds." << endl;
        map["sequential"] = stop.count()/N;
        cout << endl;
        bool myInd = false;
        binarySearch(copyVect1, 0, copyVect1.size()-1, query, myInd);
        start = std::chrono::high_resolution_clock::now();
        sequentialSearch(copyVect1, query);
        stop = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() -
         start);
        if(!myInd)
            cout << query << " does not exist in the dataset." << endl;
        cout << "Binary Search Time: " << stop.count()/N << " Nanoseconds." << endl;
        map["binary"] = stop.count()/N;
        cout << endl;
        cout << "SpeedUp between Search Algorithms" << endl << "======================================" << endl;
        cout << "(Sequential Search/ Binary Search) SpeedUp = " << double(map["sequential"]) / map["binary"] << endl;
        cout << endl;
        cout << "SpeedUps between Sorting Algorithms" << endl << "======================================" << endl;
        cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << double(map["insertion_time"]) / map["quick_time"] << endl;
        cout << "(Merge Sort / Quick Sort) SpeedUp = " << double(map["merge_time"]) / map["quick_time"] << endl;
        cout << "(Heap Sort / Quick Sort) SpeedUp = " << double(map["heap_time"]) / map["quick_time"] << endl;
    }
    else{
        istringstream issx(query);
        issx >> myName >> mySurname;
        
        start = std::chrono::high_resolution_clock::now();
        if(!sequentialSearch(copyVect1, myName, mySurname)){
            cout << myName << " " << mySurname << " does not exist in the dataset." << endl;
        }
        stop = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() -
         start);
        cout << "Sequential Search Time: " << stop.count()/N << " Nanoseconds." << endl;
        map["sequential"] = stop.count()/N;
        cout << endl;
        start = std::chrono::high_resolution_clock::now();
        if(!binarySearch(copyVect1, 0, copyVect1.size()-1, myName, mySurname)){
            cout << myName << " " << mySurname << " does not exist in the dataset." << endl;
        }
        stop = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() -
         start);
        map["binary"] = stop.count()/N;
        cout << "Binary Search Time: " << stop.count()/N << " Nanoseconds." << endl;
        cout << endl;
        cout << "SpeedUp between Search Algorithms" << endl << "======================================" << endl;
        
        cout << "(Sequential Search/ Binary Search) SpeedUp = " << map["binary"] / map["sequential"] << endl;
        cout << endl;
        cout << "SpeedUps between Sorting Algorithms" << endl << "======================================" << endl;
        cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << double(map["insertion_time"]) / map["quick_time"] << endl;
        cout << "(Merge Sort / Quick Sort) SpeedUp = " << double(map["merge_time"]) / map["quick_time"] << endl;
        cout << "(Heap Sort / Quick Sort) SpeedUp = " << double(map["heap_time"]) / map["quick_time"] << endl;
    }
    
    return 0;
}
