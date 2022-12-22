// Ege Öngül 29037


#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include "strutils.h"

using namespace std;

void prompt(){
    cout << endl;
    cout << "Press: " << endl;
    cout << "1. If you want to find out the surrounding of a cell" << endl << endl;
    cout << "2. If you want to open the cell" << endl << endl;
    cout << "3. If you want to exit." << endl << endl;
}


int xCounter(vector<vector<string>> a){
    
    int counter = 0;
    for (int i=0 ; i< a.size(); i++) {
        for(int k=0; k< a[0].size(); k++){
            if (a[i][k] == "x" ){
                counter ++;
            }
        }
    }
    return counter;
}

int main() {
    
    int row, col, bombs;
    
    cout << "Give the dimensions of the matrix: ";
    cin >> row >> col;
    cout << endl;
    
    vector<vector<string>> emptyMatrix(row, vector<string>(col,"x"));
    
    vector<vector<string>> orgMatrix(row, vector<string>(col, "x"));
    
    cout << "How many bombs: " ;
    cin >> bombs;
    while(bombs <= 0 || bombs >= (row*col)){
        if(bombs <= 0 ){
            cout << "The number of bombs could not be less than one. Please give the number of bombs again: " ;
        }
        else if(bombs >= (row*col)){
            cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
        }
        cin >> bombs;
    }
    
    
    vector<vector<int>> bombsLoc (2, vector<int>(bombs, 0));
    
    cout << endl << endl ;
    for(int i = 0; i <bombs; i++ ){
        int numberForRow = RandGen().RandInt(0,row-1);
        int numberForCol = RandGen().RandInt(0,col-1);
        bool ekle = true;
        
        for (int k = 0; k< bombsLoc.size(); k++) {
            if(bombsLoc[0][k] == numberForRow && bombsLoc[1][k] == numberForCol ){
                ekle = false;
                i--;
            }
        }
        if(ekle){
            bombsLoc[0][i] = numberForRow;
            bombsLoc[1][i] = numberForCol;
        }
    }
    
    for(int i = 0; i< bombsLoc[0].size(); i++){
        int satir = bombsLoc[0][i];
        int sutun = bombsLoc[1][i];
        orgMatrix[satir][sutun] = "B";
    }
    //sayıları yerleştir
    
    int counter1 = 0;   // sol üst köşenin etrafındaki bomba sayısı
    
    if(orgMatrix[0][1] == "B"){
        counter1++;
    }
    if(orgMatrix[1][1] == "B"){
        counter1++;
    }
    if(orgMatrix[1][0] == "B"){
        counter1++;
    }
    emptyMatrix[0][0] = itoa(counter1);
    
    
    int counter2 = 0; // sağ üst köşenin etrafındaki bomba sayısı
    
    if(orgMatrix[0][col-2] == "B"){
        counter2++;
    }
    if(orgMatrix[1][col-2] == "B"){
        counter2++;
    }
    if(orgMatrix[1][col-1] == "B"){
        counter2++;
    }
    emptyMatrix[0][col-1] = itoa(counter2);
    
    
    int counter3 = 0;  // sol alt köşenin etrafındaki bomba sayısı
    
    if(orgMatrix[row-1][1] == "B"){
        counter3++;
    }
    if(orgMatrix[row-2][1] == "B"){
        counter3++;
    }
    if(orgMatrix[row-2][0] == "B"){
        counter3++;
    }
    emptyMatrix[row-1][0] = itoa(counter3);
    
    
    int counter4 = 0;  // sağ alt köşenin etrafındaki bomba sayısı
    
    if(orgMatrix[row-1][col-2] == "B"){
        counter4++;
    }
    if(orgMatrix[row-2][col-2] == "B"){
        counter4++;
    }
    if(orgMatrix[row-2][col-1] == "B"){
        counter4++;
    }
    emptyMatrix[row-1][col-1] = itoa(counter4);
    
    for(int i = 1; i < col-1; i++){  // en üst satır için bomba sayacı
        int counter5 = 0;
        
        if(orgMatrix[0][i-1] == "B"){
            counter5++;
        }
        if(orgMatrix[0][i+1] == "B"){
            counter5++;
        }
        if(orgMatrix[1][i-1] == "B"){
            counter5++;
        }
        if(orgMatrix[1][i] == "B"){
            counter5++;
        }
        if(orgMatrix[1][i+1] == "B"){
            counter5++;
        }
        
        emptyMatrix[0][i] = itoa(counter5);
    }
    
    for(int i = 1; i < col-1; i++){  // en alt satır için bomba sayacı
        int counter6 = 0;
        
        if(orgMatrix[row-1][i-1] == "B"){
            counter6++;
        }
        if(orgMatrix[row-1][i+1] == "B"){
            counter6++;
        }
        if(orgMatrix[row-2][i-1] == "B"){
            counter6++;
        }
        if(orgMatrix[row-2][i] == "B"){
            counter6++;
        }
        if(orgMatrix[row-2][i+1] == "B"){
            counter6++;
        }
        
        emptyMatrix[row-1][i] = itoa(counter6);
    }
    
    for(int i = 1; i < row-1; i++){  // sağ sütun için bomba sayacı
        int counter7 = 0;
        
        if(orgMatrix[i-1][col-1] == "B"){
            counter7++;
        }
        if(orgMatrix[i-1][col-2] == "B"){
            counter7++;
        }
        if(orgMatrix[i][col-2] == "B"){
            counter7++;
        }
        if(orgMatrix[i+1][col-2] == "B"){
            counter7++;
        }
        if(orgMatrix[i+1][col-1] == "B"){
            counter7++;
        }
        
        emptyMatrix[i][col-1] = itoa(counter7);
    }
    
    for(int i = 1; i < col-1; i++){  // sol sütun için bomba sayacı
        int counter8 = 0;
        
        if(orgMatrix[i-1][0] == "B"){
            counter8++;
        }
        if(orgMatrix[i-1][1] == "B"){
            counter8++;
        }
        if(orgMatrix[i][1] == "B"){
            counter8++;
        }
        if(orgMatrix[i+1][1] == "B"){
            counter8++;
        }
        if(orgMatrix[i+1][0] == "B"){
            counter8++;
        }
        
        emptyMatrix[i][0] = itoa(counter8);
    }
    
    for(int i = 1; i < col-1; i++){  // en alt satır için bomba sayacı
        for(int k = 1; k< row-1; k++){
            int counter9 = 0;
            if(orgMatrix[i-1][k-1] == "B"){
                counter9++;
            }
            if(orgMatrix[i-1][k] == "B"){
                counter9++;
            }
            if(orgMatrix[i-1][k+1] == "B"){
                counter9++;
            }
            if(orgMatrix[i][k-1] == "B"){
                counter9++;
            }
            if(orgMatrix[i][k+1] == "B"){
                counter9++;
            }
            if(orgMatrix[i+1][k-1] == "B"){
                counter9++;
            }
            if(orgMatrix[i+1][k] == "B"){
                counter9++;
            }
            if(orgMatrix[i+1][k+1] == "B"){
                counter9++;
            }
            emptyMatrix[i][k] = itoa(counter9);
        }
    }
    
    for(int i = 0; i<orgMatrix.size(); i++ ){
        for(int j = 0; j< orgMatrix[0].size(); j++){
            cout << orgMatrix[i][j] << "   " ;
        }
        cout << endl;
    }
    cout << endl << endl;
    
//    bombaların yerini bulmak için orgMatrix kullanılcak
//    sayıları öğrenmek için emptyMatrix kullanılcak
    
    vector<vector<string>> gameMatrix(row, vector<string>(col,"x")); // oyunun oynanacağı matrix
    
    for(int i = 0; i<gameMatrix.size(); i++ ){
        for(int j = 0; j< gameMatrix[0].size(); j++){
            cout << gameMatrix[i][j] << "   " ;
        }
        cout << endl;
    }
    cout << endl;
    
    int numberOfEmptySpaces = (row*col) - bombs;
    int numberOfX = (row*col);
    int LastNumOfX = numberOfX - numberOfEmptySpaces;
    
    string decision = "0";
    
    while (decision != "3") {
        prompt();
        cin >> decision;
        cout << endl;
        int checkIfTrue = 1;
        
        if(decision != "1" && decision != "2" && decision != "3" ){
            checkIfTrue = 0;
        }
        while (checkIfTrue == 0) {
            cout << "Your input is wrong. Please select one of the options: 1, 2 or 3."<< endl;
            cin >> decision;
            cout << endl;
            if(decision == "1" || decision == "2" || decision != "3" ){
                checkIfTrue = 1;
            }
        }
        if (decision == "1") {
            cout << "Give the coordinates: ";
            int coordinate1, coordinate2;
            cin >> coordinate1 >> coordinate2;
            cout << endl << endl;
            bool trueCoordinate = true;
            if(coordinate1 > row-1 || coordinate2 > col-1){
                trueCoordinate = false;
            }
            while(!trueCoordinate){
                cout << "It is out of range. Please give a valid coordinates: ";
                cin >> coordinate1 >> coordinate2;
                cout << endl << endl;
                if(coordinate1 <= row-1 && coordinate2 <= col-1){
                    trueCoordinate = true;
                }
            }
            
            gameMatrix[coordinate1][coordinate2] = emptyMatrix[coordinate1][coordinate2];
            cout << endl << endl << endl;
            for(int i = 0; i<gameMatrix.size(); i++ ){
                for(int j = 0; j< gameMatrix[0].size(); j++){
                    cout << gameMatrix[i][j] << "   " ;
                }
                cout << endl;
            }
            
            gameMatrix[coordinate1][coordinate2] = "x";
            cout << endl;
            cout << "Around (" << coordinate1 << "," << coordinate2<< ") you have " << emptyMatrix[coordinate1][coordinate2] << " bomb(s)" << endl << endl;
            
        }
        else if(decision == "2"){
            int coordinate1, coordinate2;
            cout << "Give the coordinates: " ;
            cin >> coordinate1 >> coordinate2;
            cout << endl << endl;
            bool trueCoordinate = true;
            if(coordinate1 > row-1 || coordinate2 > col-1){
                trueCoordinate = false;
            }
            while(!trueCoordinate){
                cout << "It is out of range. Please give a valid coordinates: ";
                cin >> coordinate1 >> coordinate2;
                cout << endl << endl;
                if(coordinate1 <= row-1 && coordinate2 <= col-1){
                    trueCoordinate = true;
                }
            }
            
            cout << "Opening cell (" << coordinate1 << "," << coordinate2 << "): " << endl;
            if(orgMatrix[coordinate1][coordinate2] == "B" ){
                gameMatrix[coordinate1][coordinate2] = "B";
                
                for(int i = 0; i<gameMatrix.size(); i++ ){
                    for(int j = 0; j< gameMatrix[0].size(); j++){
                        cout << gameMatrix[i][j] << "   " ;
                    }
                    cout << endl;
                }
                cout << "Unfortunately, you stepped on a mine" << endl << endl;
                cout << "Arrangement of mines: " << endl << endl;
                
                for(int i = 0; i<emptyMatrix.size(); i++ ){
                    for(int j = 0; j< emptyMatrix[0].size(); j++){
                        if (orgMatrix[i][j] == "B") {
                            cout << "B" << "   ";
                        }
                        else{
                            cout << emptyMatrix[i][j] << "   " ;
                        }
                    }
                    cout << endl;
                }
                cout << endl;
                cout << ">>>>> Game Over! <<<<<" << endl;
                return 0;
                
            }else{
                gameMatrix[coordinate1][coordinate2] = emptyMatrix[coordinate1][coordinate2];
                
                cout << endl << endl << endl;
                for(int i = 0; i<gameMatrix.size(); i++ ){
                    for(int j = 0; j< gameMatrix[0].size(); j++){
                        cout << gameMatrix[i][j] << "   " ;
                    }
                    cout << endl;
                }
                if(LastNumOfX == xCounter(gameMatrix)){
                    cout << "Congratulations! All the non-mined cells opened successfully" << endl;
                    cout << "You won!" << endl;
                    return 0;
                }
            }
        }
    }
    
    if (decision == "3") {
        cout << "Program exiting ..." << endl;
    }
    return 0;
}
