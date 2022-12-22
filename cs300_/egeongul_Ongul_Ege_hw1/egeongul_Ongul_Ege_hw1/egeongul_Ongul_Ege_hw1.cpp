//Ege Öngül 29037
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "randgen.h"
#include "stack.h"
#include "sstream"

struct cell {
    
    int x;
    int y;
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;
    bool visited = false;
    bool canGo = true;
    
    cell(int m, int n){
        x = m;
        y = n;
    }
};

bool ExistInVect(cell myCell, vector<cell> myVect){
    for(int i = 0; i < myVect.size(); i++){
        if(myVect[i].x == myCell.x && myVect[i].y == myCell.y){
            return true;
        }
    }
    return false;
}

cell  findCell(int  x, int  y, vector<cell> & vect, int row, int col){
    if(x < 0){
        x = 0;
    }
    if(x >= row){
        x = row-1;
    }
    if(y < 0){
        y = 0;
    }
    if(y >= col){
        y = col-1;
    }
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            return vect[i];
        }
    }
    cell myCell(x,y);
    return myCell;
}

void changeCell(int x, int y, vector<cell> & vect){
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            vect[i].visited = true;
        }
    }
}

void changeCellUp(int x, int y, vector<cell> & vect){
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            vect[i].up = false;
        }
    }
}
void changeCellDown(int x, int y, vector<cell> & vect){
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            vect[i].down = false;
        }
    }
}
void changeCellRight(int x, int y, vector<cell> & vect){
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            vect[i].right = false;
        }
    }
}
void changeCellLeft(int x, int y, vector<cell> & vect){
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].x == x && vect[i].y == y){
            vect[i].left = false;
        }
    }
}

string chooseDirection(){
    string direction;
    RandGen rand;
    int num = rand.RandInt(1,4);
    if(num == 1 ){
        direction = "up";
    }
    else if( num == 2){
        direction = "right";
    }
    else if( num == 3){
        direction = "down";
    }
    else{
        direction = "left";
    }
    return direction;
}

void debugCells(vector<cell> myVect){
    cout << "-----------   DEBUGGING   ------------" << endl;
    for(int i = 0; i < myVect.size(); i++){
        cout << "x = " << myVect[i].x << " y = " << myVect[i].y ;
        if(myVect[i].visited){
            cout << " v = 1";
        }else{
            cout << " v = 0";
        }
        
        if(myVect[i].up == true){
            cout << " u = 1" ;
        }else{
            cout << " u = 0";
        }
        
        if(myVect[i].down == true){
            cout << " d = 1" ;
        }else{
            cout << " d = 0";
        }
        
        if(myVect[i].right == true){
            cout << " r = 1" ;
        }else{
            cout << " r = 0";
        }
        
        if(myVect[i].left == true){
            cout << " l = 1" ;
        }else{
            cout << " l = 0";
        }
        cout << endl;
    }
    cout << "----------- DEBUGGING END ------------" << endl;
}


bool canGo(cell myCell, vector<cell> myVect, int row, int col){
    int x = myCell.x;
    int y = myCell.y;
    cell Upcell = findCell(x+1, y, myVect, row, col);
    cell Downcell = findCell(x-1, y, myVect, row, col);
    cell Rightcell = findCell(x, y+1, myVect, row, col);
    cell Leftcell = findCell(x, y-1, myVect, row, col);
    if(Upcell.visited == true && Downcell.visited == true && Rightcell.visited == true && Leftcell.visited == true){
        myCell.canGo = false;
        return false;
    }
    else{
        return  true;
    }
}

bool canGo2(cell myCell, vector<cell> myVect, int row, int col){
    int x = myCell.x;
    int y = myCell.y;
    cell Upcell = findCell(x+1, y, myVect, row, col);
    cell Downcell = findCell(x-1, y, myVect, row, col);
    cell Rightcell = findCell(x, y+1, myVect, row, col);
    cell Leftcell = findCell(x, y-1, myVect, row, col);
    if((Upcell.visited == true && Downcell.visited == true && Rightcell.visited == true && Leftcell.visited == true)
       || (myCell.up && myCell.down && myCell.right && Leftcell.visited)
       || (myCell.up && myCell.down && Rightcell.visited && myCell.left)
       || (myCell.up && Downcell.visited && myCell.right && myCell.left)
       || (Upcell.visited && myCell.down && myCell.right && myCell.left)
       || (!myCell.up && !myCell.down && myCell.right && myCell.left && Upcell.visited && Downcell.visited)
       || (!myCell.up && myCell.down && !myCell.right && myCell.left && Upcell.visited && Rightcell.visited)
       || (!myCell.up && myCell.down && myCell.right && !myCell.left && Upcell.visited && Leftcell.visited)
       || (myCell.up && !myCell.down && !myCell.right && myCell.left && Downcell.visited && Rightcell.visited)
       || (myCell.up && !myCell.down && myCell.right && !myCell.left && Downcell.visited && Leftcell.visited)
       || (myCell.up && myCell.down && !myCell.right && !myCell.left && Rightcell.visited && Leftcell.visited)
       || (!myCell.up && !myCell.down && !myCell.right && myCell.left && Upcell.visited && Downcell.visited && Rightcell.visited)
       || (!myCell.up && !myCell.down && myCell.right && !myCell.left && Upcell.visited && Downcell.visited && Leftcell.visited)
       || (myCell.up && !myCell.down && !myCell.right && !myCell.left && Downcell.visited && Rightcell.visited && Leftcell.visited)
       ){
        myCell.canGo = false;
        return false;
    }
    else{
        return  true;
    }
}

bool ifExist(cell myCell){
    if(myCell.x < 0 || myCell.y < 0){
        return false;
    }
    return true;
}

bool finished(vector<cell> myVect){
    for(int i = 0; i < myVect.size(); i++){
        if(!myVect[i].visited){
            return false;
        }
    }
    return true;
}

int main(){
    int row,col;
    cout << "Please enter the number of rows and collumns: " << endl;
    cin >> row >> col;
    stack<cell> stack1;
    vector<cell> myVect;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cell myCell(i, j);
            myVect.push_back(myCell);
        }
    }
    debugCells(myVect);
    cell myCell(0,0);
    int counter = 0;
    
    while(!finished(myVect)){
        stack1.push(myCell);
        while(!canGo(stack1.top(), myVect, row, col)){
            stack1.pop();
        }
        counter++;
        changeCell(myCell.x, myCell.y, myVect);
        myCell = findCell(myCell.x, myCell.y, myVect, row, col);
        cout << stack1.top().x << "   " << stack1.top().y << endl; //debug to see clearly
        cout << myCell.x << "   " << myCell.y << endl;
        cout << counter << endl;
        cout << "---------------" << endl;
        
        string direction = chooseDirection();
        cell oldCell = findCell(myCell.x, myCell.y, myVect, row, col);
        if(direction == "up"){
            myCell = findCell((myCell.x)+1, (myCell.y), myVect, row, col);
            if(myCell.visited){
                myCell = oldCell;
            }
        }
        else if(direction == "right"){
            myCell = findCell((myCell.x), (myCell.y)+1, myVect, row, col);
            if(myCell.visited){
                myCell = oldCell;
            }
        }
        else if(direction == "down"){
            myCell = findCell((myCell.x)-1, (myCell.y), myVect, row, col);
            if(myCell.visited){
                myCell = oldCell;
            }
        }
        else if(direction == "left"){
            myCell = findCell((myCell.x), (myCell.y)-1, myVect, row, col);
            if(myCell.visited){
                myCell = oldCell;
            }
        }
        if(ifExist(myCell)){
            if(!myCell.visited){
                if(myCell.visited){
                    myCell = oldCell;
                }
                else{
                    changeCell(myCell.x, myCell.y, myVect);
                    if(direction == "up"){
                        changeCellUp(oldCell.x, oldCell.y, myVect);
                        changeCellDown(myCell.x, myCell.y, myVect);
                    }
                    else if(direction == "right"){
                        changeCellRight(oldCell.x, oldCell.y, myVect);
                        changeCellLeft(myCell.x, myCell.y, myVect);
                    }
                    else if(direction == "down"){
                        changeCellDown(oldCell.x, oldCell.y, myVect);
                        changeCellUp(myCell.x, myCell.y, myVect);
                    }
                    else if(direction == "left"){
                        changeCellLeft(oldCell.x, oldCell.y, myVect);
                        changeCellRight(myCell.x, myCell.y, myVect);
                    }
                }
                
            }
            else{
                while(!canGo(stack1.top(), myVect, row, col)){
                    stack1.pop();
                }
                myCell = findCell(stack1.top().x, stack1.top().y, myVect, row, col);
                counter--;
                changeCell(myCell.x, myCell.y, myVect);
            }
        }
        else{
            myCell = oldCell;
            stack1.pop();
            counter --;
        }
    }
    cout << row << " " << col << endl;
    ofstream yazdir;
    string filename = "maze_1.txt";
    yazdir.open(filename.c_str());
    debugCells(myVect);
    yazdir << row << " " << col << endl ;
    for(int i = 0; i < myVect.size(); i++){
        yazdir << "x=" << myVect[i].x << " y=" << myVect[i].y << " l=" << myVect[i].left << " r=" << myVect[i].right << " u=" << myVect[i].up << " d=" << myVect[i].down << endl;
    }
    myCell = findCell(0, 0, myVect, row, col);
    
    int mazeId = 1;
    int entryX, entryY, exitX, exitY;
    cout << "Please enter entryX and entryY: " << endl;
    cin >> entryX >> entryY;
    cout << "Now please enter exitX and exitY: " << endl;
    cin >> exitX >> exitY;
    string filename2 = "maze_";
    string sM = to_string(mazeId) + "_";
    string sX = to_string(entryX) + "_";
    string sY = to_string(entryY) + "_";
    string sXX = to_string(exitX) + "_";
    string sYY = to_string (exitY);
    filename2 = filename2 + sM + "path_" + sX + sY + sXX + sYY + ".txt";
    cout << filename2 << endl;
    stack<cell> stack2;
    cell xCell(entryX, entryY);
    vector<cell> izlevegör;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cell myCell(i, j);
            izlevegör.push_back(myCell);
        }
    }
    vector<cell> corVect;
    while(xCell.x != exitX || xCell.y != exitY ){
        if(!ExistInVect(xCell, corVect)){
            corVect.push_back(xCell);
        }
        stack2.push(xCell);
        changeCell(xCell.x, xCell.y, izlevegör);
        cout << stack2.top().x << "   " << stack2.top().y << endl; //debug to see clearly
        cout << xCell.x << "   " << xCell.y << endl;
        while(!canGo2(findCell(stack2.top().x, stack2.top().y, myVect, row, col), izlevegör, row, col)){
            stack2.pop();
            xCell = findCell(stack2.top().x, stack2.top().y, izlevegör, row, col);
        }
        changeCell(xCell.x, xCell.y, izlevegör);
        string direction = chooseDirection();
        cell oldCell = findCell(xCell.x, xCell.y, izlevegör, row, col);
        if(direction == "up" && !findCell(xCell.x, xCell.y, myVect, row, col).up){
            xCell = findCell((xCell.x)+1, (xCell.y), izlevegör, row, col);
            if(xCell.visited){
                xCell = oldCell;
            }
            cout << "up" << endl;
        }
        else if(direction == "right" && !findCell(xCell.x, xCell.y, myVect, row, col).right){
            xCell = findCell((xCell.x), (xCell.y)+1, izlevegör, row, col);
            if(xCell.visited){
                xCell = oldCell;
            }
            cout << "right" << endl;
        }
        else if(direction == "down" && !findCell(xCell.x, xCell.y, myVect, row, col).down){
            xCell = findCell((xCell.x)-1, (xCell.y), izlevegör, row, col);
            if(xCell.visited){
                xCell = oldCell;
            }
            cout << "down" << endl;
        }
        else if(direction == "left" && !findCell(xCell.x, xCell.y, myVect, row, col).left){
            xCell = findCell((xCell.x), (xCell.y)-1, izlevegör, row, col);
            if(xCell.visited){
                xCell = oldCell;
            }
            cout << "left" << endl;
        }
        cout << "---------------" << endl;
    }
    
    ofstream yaz;
    yaz.open(filename2.c_str());
    for(int i = 0; i < corVect.size(); i++){
        yaz << corVect[i].x << " " << corVect[i].y << endl;
    }
    yaz << exitX << " " << exitY << endl;
    yaz.close();
    return 0;
}
