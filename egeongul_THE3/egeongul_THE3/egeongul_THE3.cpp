

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

int main() {
    string keys, answers, line, linex, first, second, third, forth;
    ifstream input1, input2;
    string name, surname, ans1, ans2, ans3, ans4, ans5, ans6, house;
    int total;
    cout << "Hello and welcome to the Hogwarts house sorting hat program!" << endl;
    cout << "When I call your name, you'll come forth, I shall place the sorting hat on your head, and you will be sorted into your houses." << endl;
    cout << "Enter the name of the key file: ";
    cin >> keys;
    input1.open(keys.c_str());
    while(input1.fail()){
        cout << "Error: Cannot open file " << keys << endl;
        cout << "Enter the name of the key file: ";
        cin >> keys;
        input1.open(keys.c_str());
    }
    cout << "Enter the name of the answer file: ";
    cin >> answers;
    input2.open(answers.c_str());
    while(input2.fail()){
        cout << "Error: Cannot open file " << answers << endl;
        cout << "Enter the name of the answer file: ";
        answers.clear();
        cin >> answers;
        input2.open(answers.c_str());
    }
    map<string,int>dict = {};
    while(getline(input1,line)){
        if(!line.empty()){
            istringstream iss(line);
            iss >> first >> second >> third >> forth;
            dict[first]=1;
            dict[second]=2;
            dict[third]=3;
            dict[forth]=4;
        }
    }
    while(getline(input2, linex)){
        if(linex.length()!=1 && !linex.empty()){
            istringstream iss(linex);
            iss >> name >> surname >> ans1 >> ans2 >> ans3 >> ans4 >> ans5 >> ans6;
            total = dict[ans1] + dict[ans2] + dict[ans3] + dict[ans4] + dict[ans5] + dict[ans6];
            if(name=="Draco"){
                total=23;
            }
            if(total<10){
                house="Hufflepuff";
            }
            else if(10<=total && total<15){
                house="Ravenclaw";
            }
            else if(15<=total && total <21){
                house="Gryffindor";
            }
            else{
                house="Slytherin";
            }
            cout << "Oh! we have " << name << " " << surname << " under the sorting hat. " << name << ", you scored " <<  total << " points, you are a "
            << house << "!" <<endl;
        }
    }
    input1.close();
    input2.close();
    return 0;
}
