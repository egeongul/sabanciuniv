
/*
string query, words;
cout << "Enter queried words in one line: " ;
getline(cin, query);
istringstream iss(query);
while(iss){
    iss >> words;
    auto it = remove_if(words.begin(), words.end(), [](char const &c) {
            return !isalpha(c);
        });
    words.erase(it, words.end());
    ToLower(words);
    cout << words << endl;
}
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#include "Hash.h"
#include "BST.h"
#include "strutils.h"

void check(Hash<string> & h1, Hash<string> h2){
    /*
    cout << "loadfactor ->> " << h1.loadFactor << endl;
    cout << "numOfıtems ->> " << h1.numOfItems << endl;
    cout << "tableSize  ->> " << h1.tableSize << endl;
    cout << "uniqueCount->> " << h1.uniqueCount << endl;
    */
    if(h1.loadFactor > 0.8){
        int prevTablezSize = h1.tableSize;
        h1 = h1.resize();
        int tabSize = h1.tableSize;        cout << "rehashed..." << endl;
        cout  << "previous table size: " <<prevTablezSize << ", new table size: " << tabSize << " , current unique word count: " <<  h1.uniqueCount << " current load factor: " << h1.loadFactor << endl;
    }
    //cout << "-----" << endl;
}


int main() {
    Hash<string> H4C(1);
    Hash<string> H1(53);
    BinarySearchTree<string> myTree("ItemNotFound");
    int inputNum;
    string filename, line, words;
    istringstream iss;
    cout << "Enter number of input files: " ;
    cin >> inputNum;
    vector<string> fileVect;

    for(int i = 1; i < inputNum+1; i++){
        cout << "Enter " <<  i << ". file name: ";
        cin >> filename;
        fileVect.push_back(filename);
    }
    int sayac = 0;
    for(int i = 0; i < inputNum; i++){
        ifstream input;
        filename = fileVect[i];
        H1.fileName = filename;
        input.open(filename.c_str());
        while(getline(input, line)){
            line = line.substr(0, line.length()-1);
            iss.clear();
            for(int i = 0; i < line.length(); i++){
                if(!isalpha(line[i]))
                    line[i] = ' ';
            }
            istringstream iss(line);
            while(iss >> words){
//                auto it = remove_if(words.begin(), words.end(), [](char const &c) {
//                        return !isalpha(c);
//                    });
//                words.erase(it, words.end());
                ToLower(words);
                if(words == "and")
                    sayac ++;
                H1.insert(words);
                myTree.insert(words, words);
                check(H1, H4C);
            }
        }
        input.close();
    }
    check(H1, H4C);
    cout << endl << "After preprocessing, the unique word count is " <<  H1.uniqueCount << ". Current load ratio is " << H1.loadFactor << endl;
    cout << "Enter queried words in one line: " ;
    cin.ignore();
    getline(cin,  words );
    cout << endl;
    string kelime;
    for(int i = 0; i < words.length(); i++){
        if(!isalpha(words[i]))
            words[i] = ' ';
        if(words[i] == ' ')
            words.erase(i,1);
    }
    
    istringstream issX(words);
    auto start = std::chrono::high_resolution_clock::now();
    while(issX >> kelime){
        ToLower(kelime);
        H1.find(kelime);
        sayac++;
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start);
    istringstream issXX(words);
    while(issXX >> kelime){
        ToLower(kelime);
        H1.find(kelime);
    }
    
    auto start2 = std::chrono::high_resolution_clock::now();
    istringstream issXX3(words);
    while(issXX3 >> kelime){
        ToLower(kelime);
        myTree.find(kelime);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() -
     start2);
    
    cout << "\nTime to find in HashTable: " << HTTime.count()/sayac  << "\n";  // average time to find 1 word in HashTable
    cout << "\nTime to find in BST: " << BSTTime.count()/sayac  << "\n"; // average time to find 1 word in BinarySearchTree
    cout << "Speed Up: " <<   double((BSTTime.count()/sayac)) / (HTTime.count()/sayac) << endl;
    
    return 0;
}
