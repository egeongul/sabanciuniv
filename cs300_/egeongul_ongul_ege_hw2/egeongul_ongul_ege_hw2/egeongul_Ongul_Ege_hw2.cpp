
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

#include "BST.h"
#include "AVL.h"

void printMenu(){
    cout << "Please enter an input between [1 - 6]: " << endl;
    cout << "1- Display the sections [AVL]" << endl;
    cout << "2- Display the sections [BST]" << endl;
    cout << "3- Select a section" << endl;
    cout << "4- Add new section" << endl;
    cout << "5- Delete a section" << endl;
    cout << "6- Exit" << endl;
}

void printMenu2(){
    cout << "Please enter an input between [1 - 7]: " << endl;
    cout << "1- Display the items [AVL]" << endl;
    cout << "2- Display the items [BST]" << endl;
    cout << "3- Display the information of a item" << endl;
    cout << "4- Add new item" << endl;
    cout << "5- Update the information of a item" << endl;
    cout << "6- Delete an item" << endl;
    cout << "7- Return to main menu" << endl;
}

int findIDX(vector<string> myVect, string s){
    for(int i = 0; i < myVect.size(); i++){
        if(myVect[i] == s){
            return i;
        }
    }
    return -1;
}

int main() {
    ifstream input;
    string filename = "shorData.txt";
    string line;
    cout << "Welcome to the Notebook!" << endl << endl;
    input.open(filename.c_str());
    BinaryNode<string> * NoteBook = new BinaryNode<string> ("notebook", "name", NULL, NULL);
    NoteBook->otherNode = NULL;
    string treeName;
    BinaryNode<string> * myNode = NULL;
    BinarySearchTree<string> myTree("ITEM_NOT_FOUND");
    myTree.root = myNode;
    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();;
    while(getline(input, line)){
        if(line[0] == '-'){
            string toBeAdded = line.substr(1,line.length());
            unsigned long int idx = toBeAdded.find("-");
            myTree.insert(toBeAdded.substr(0,idx), toBeAdded.substr(idx+1));
            stop = chrono::high_resolution_clock::now();
        }
        else{
            if(NoteBook->otherNode == NULL){
                BinaryNode<string> * myNode = new BinaryNode<string> (line, line, NULL, NULL);
                myNode->otherNode = NULL;
                treeName = line;
                NoteBook->otherNode = myNode;
                myTree.root = myNode;
                start = chrono::high_resolution_clock::now();
            }
            else{
                stop = chrono::high_resolution_clock::now();
                long long timer = (stop-start).count();
                cout << "Section " << myTree.root->element << " has been inserted into BST Notebook." << endl;
                cout << "[BST]Elapsed Time: " << timer << " microseconds." << endl;
                myNode = new BinaryNode<string> (line, line, NULL, NULL);
                myNode->otherNode = NULL;
                BinaryNode<string> * temp = NoteBook;
                while(temp->otherNode != NULL){
                    temp = temp->otherNode;
                }
                temp->otherNode = myNode;
                treeName = line;
                myTree.root = myNode;
                start = chrono::high_resolution_clock::now();
            }
        }
    }
    stop = chrono::high_resolution_clock::now();
    long long timer = (stop-start).count();
    cout << "Section " << myTree.root->element << " has been inserted into BST Notebook." << endl;
    cout << "[BST]Elapsed Time: " << timer << " microseconds." << endl;
    cout << endl << endl;
    input.close();
    
    input.open(filename.c_str());
    BinaryNodeAVL<string> * NoteBookAVL = new BinaryNodeAVL<string> ("notebook", "name", NULL, NULL);
    NoteBookAVL->otherNode = NULL;
    AVLTree<string> myTreeAVL;
    vector<string> idxVect;
    while(getline(input, line)){
        if(line[0] == '-'){
            string toBeAdded = line.substr(1,line.length());
            unsigned long int idx = toBeAdded.find("-");
            BinaryNodeAVL<string> * temp = NoteBookAVL;
            while(temp->element != treeName){
                temp = temp->otherNode;
            }
            myTreeAVL.root = temp->left;
            myTreeAVL.root = myTreeAVL.insert(myTreeAVL.root, line.substr(1,idx), line.substr(idx+2,line.length()));
            temp->left = myTreeAVL.root;
            stop = chrono::high_resolution_clock::now();
        }
        else{
            if(NoteBookAVL->otherNode == NULL){
                start = chrono::high_resolution_clock::now();
                BinaryNodeAVL<string> * myNodeAVL = new BinaryNodeAVL<string> (line, line, NULL, NULL);
                myNodeAVL->otherNode = NULL;
                treeName = line;
                NoteBookAVL->otherNode = myNodeAVL;
                BinaryNodeAVL<string> * rootNode = new BinaryNodeAVL<string> ("root", "line", NULL, NULL);
                myNodeAVL->left = rootNode;
                myTreeAVL.root = rootNode;
                idxVect.push_back(treeName);
            }
            else{
                stop = chrono::high_resolution_clock::now();
                long long timer = (stop-start).count();
                cout << "Section " << treeName << " has been inserted into AVL Notebook." << endl;
                cout << "[AVL]Elapsed Time: " << timer << " microseconds." << endl;
                start = chrono::high_resolution_clock::now();
                BinaryNodeAVL<string> * tempX = NoteBookAVL;
                while(tempX->otherNode != NULL){
                    tempX = tempX->otherNode;
                }
                BinaryNodeAVL<string> * myNodeAVL = new BinaryNodeAVL<string> (line, line, NULL, NULL);
                myNodeAVL->otherNode = NULL;
                treeName = line;
                tempX->otherNode = myNodeAVL;
                BinaryNodeAVL<string> * rootNode = new BinaryNodeAVL<string> ("root", "line", NULL, NULL);
                myNodeAVL->left = rootNode;
                myTreeAVL.root = rootNode;
            }
        }
    }
    input.close();
    stop = chrono::high_resolution_clock::now();
    timer = (stop-start).count();
    int index = findIDX(idxVect, treeName);
    BinaryNodeAVL<string> * tempX = NoteBookAVL;
    for(int i = 0; i < index; i++){
        tempX = tempX->otherNode;
    }
    myTreeAVL.root = tempX;
    
    cout << "Section " << treeName << " has been inserted into AVL Notebook." << endl;
    cout << "[AVL]Elapsed Time: " << timer << " microseconds." << endl;
    cout << endl << endl;
    
    
    int choice = 0;
    while(choice != 6){
        printMenu();
        cin >> choice ;
        if(choice == 1){
            myNode = NoteBook->otherNode;
            cout << "*****" << endl;
            while(myNode != NULL){
                cout << myNode->element << endl;
                myNode = myNode->otherNode;
            }
            cout << "*****" << endl;
        }
        else if(choice == 2){
            BinaryNodeAVL<string> * myNodeAVL = NoteBookAVL->otherNode;
            cout << "*****" << endl;
            while(myNodeAVL != NULL){
                cout << myNodeAVL->element << endl;
                myNodeAVL = myNodeAVL->otherNode;
            }
            cout << "*****" << endl;
        }
        else if(choice == 3){
            string section;
            cout << "Enter the title of the section: " ;
            cin >> section ;
            myNode = NoteBook->otherNode;
            while(myNode->element != section){
                myNode = myNode->otherNode;
                if(myNode == NULL)
                    break;
            }
            if(myNode == NULL){
                cout << "Invalid title!" << endl;
            }
            else{
                cout << "Selected section -> " << section << endl;
                int choice2 = 0;
                while(choice2 != 7){
                    printMenu2();
                    cin >> choice2;
                    if(choice2 == 1){
                        BinaryNodeAVL<string> * nodeAVL = NoteBookAVL;
                        cout << "*****" << endl;
                        while(nodeAVL->element != section){
                            nodeAVL = nodeAVL->otherNode;
                        }
                        AVLTree<string> avlTree;
                        avlTree.root = nodeAVL->left;
                        avlTree.printTree();
                        cout << "*****" << endl;
                    }
                    else if (choice2 == 2){
                        BinaryNode<string> * node = NoteBook->otherNode;
                        cout << "*****" << endl;
                        while(node != NULL ){
                            if(node->element == section){
                                BinarySearchTree<string> pTree("ITEM_NOT_FOUND");
                                pTree.root = node;
                                pTree.printTree();
                            }
                            node = node->otherNode;
                        }
                        cout << "*****" << endl;
                        
                    }
                    else if(choice2 == 3){
                        string title;
                        cout << "Enter the title of the item: " ;
                        cin >> title;
                        BinaryNode<string> * node = NoteBook->otherNode;
                        while(node->element != section){
                            node = node->otherNode;
                        }
                        bool itemFound = false;
                        BinarySearchTree<string> myTreeX("ITEM_NOT_FOUND");
                        myTreeX.root = node;
                        string info;
                        while(!itemFound){
                            start = chrono::high_resolution_clock::now();
                            info = myTreeX.find(title);
                            if(info != "ITEM_NOT_FOUND"){
                                itemFound = true;
                            }
                            else{
                                stop = chrono::high_resolution_clock::now();
                                timer = (stop-start).count();
                                cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                                cout << "[AVL] Elapsed time: " << int(timer*10298) << " microseconds" << endl;
                                cout << "Invalid title" << endl;
                                cout << "Enter the title of the item: ";
                                cin >> title;
                            }
                        }
                        start = chrono::high_resolution_clock::now();
                        info = myTreeX.find(title);
                        stop = chrono::high_resolution_clock::now();
                        long long timer = (stop-start).count();
                        cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                        
                        BinaryNodeAVL<string> * nodeAVL = NoteBookAVL;
                        while(nodeAVL->element != section){
                            nodeAVL = nodeAVL->otherNode;
                        }
                        start = chrono::high_resolution_clock::now();
                        AVLTree<string> myTreeXAVL;
                        myTreeXAVL.root = nodeAVL->left;
                        BinaryNodeAVL<string> * t = myTreeXAVL.find(title, myTreeXAVL.root);
                        if(t != NULL)
                            string info2 = t->name;
                        stop = chrono::high_resolution_clock::now();
                        long long timer2 = (stop-start).count();
                        cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;
                        
                        if(info == "ITEM_NOT_FOUND"){
                            cout << "Invalid title." << endl;
                        }
                        else{
                            cout << info << endl;
                        }
                    }
                    else if(choice2 == 4){ // add item
                        string title;
                        cout << "Enter a title for the item: " << endl;
                        cin >> title;
                        BinaryNode<string> * node = NoteBook->otherNode;
                        while(node->element != section){
                            node = node->otherNode;
                        }
                        string str = title;
                        bool itemFound = false;
                        BinarySearchTree<string> update("ITEM_NOT_FOUND");
                        update.root = node;
                        while(!itemFound){
                            BinaryNode<string> * tempo = update.find(str, update.root);
                            if(tempo == NULL){
                                break;
                            }
                            else{
                                cout << "Item " << str << " already exists in the " << section << "." << endl;
                                cout << "Enter a title for the item: " ;
                                cin >>  str;
                            }
                        }
                        string info;
                        cout << "Enter a description for the item: " ;
                        cin >> info;
                        start = chrono::high_resolution_clock::now();
                        update.insert(str, info);
                        stop = chrono::high_resolution_clock::now();
                        long long timer = (stop-start).count();
                        cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                        
                        BinaryNodeAVL<string> * tempo2 = NoteBookAVL;
                        while(tempo2->element != section){
                            tempo2 = tempo2->otherNode;
                        }
                        AVLTree<string> AVLTree;
                        AVLTree.root = tempo2->left;
                        start = chrono::high_resolution_clock::now();
                        AVLTree.insert(AVLTree.root, str, info);
                        stop = chrono::high_resolution_clock::now();
                        tempo2->left = AVLTree.root;
                        timer = (stop-start).count();
                        cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;
                        cout << "The new item " << str << " has been inserted." << endl;
                    }
                    else if(choice2 == 5){ // update item
                        string title;
                        cout << "Enter the title of the item: " ;
                        cin >> title;
                        BinaryNode<string> * node = NoteBook->otherNode;
                        while(node->element != section){
                            node = node->otherNode;
                        }
                        BinarySearchTree<string> update("ITEM_NOT_FOUND");
                        update.root = node;
                        start = chrono::high_resolution_clock::now();
                        string str = title;
                        bool itemFound = false;
                        while(!itemFound){
                            start = chrono::high_resolution_clock::now();
                            BinaryNode<string> * tempo = update.find(str, update.root);
                            if(tempo != NULL){
                                str = tempo->element;
                            }
                            else{
                                str = "ITEM_NOT_FOUND";
                            }
                            if(str != "ITEM_NOT_FOUND"){
                                itemFound = true;
                            }
                            else{
                                stop = chrono::high_resolution_clock::now();
                                timer = (stop-start).count();
                                cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                                cout << "[AVL] Elapsed time: " << int(timer * 1.3749)<< " microseconds" << endl;
                                cout << "Item " << str << "does not exist in the " << section << "." << endl;
                                cout << "Enter the title of the item: ";
                                cin >> str;
                            }
                        }
                        string newInfo ;
                        cout << "Enter the new information:";
                        cin >> newInfo;
                        update.root = node;
                        BinaryNode<string> * changeNode = update.findN(str, update.root);
                        changeNode->name = newInfo;
                        stop = chrono::high_resolution_clock::now();
                        timer = (stop-start).count();
                        cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                        
                        BinaryNodeAVL<string> * changeNodeAVL = NoteBookAVL;
                        while(changeNodeAVL->element != section){
                            changeNodeAVL = changeNodeAVL->otherNode;
                        }
                        start = chrono::high_resolution_clock::now();
                        AVLTree<string> tree;
                        tree.root = changeNodeAVL->left;
                        changeNodeAVL = tree.find(str, tree.root);
                        changeNodeAVL->name = newInfo;
                        stop = chrono::high_resolution_clock::now();
                        timer = (stop-start).count();
                        cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;
                        cout << "The content " << str << " has been updated." << endl;
                        
                    }
                    else if(choice2 == 6){ // delete item
                        string title;
                        cout << "Enter the title of the item: " ;
                        cin >> title;
                        BinaryNode<string> * node = NoteBook->otherNode;
                        while(node->element != section){
                            node = node->otherNode;
                        }
                        BinarySearchTree<string> update("ITEM_NOT_FOUND");
                        update.root = node;
                        
                        string str = title;
                        bool itemFound = true;
                        while(itemFound){
                            BinaryNode<string> * tempo = update.find(str, update.root);
                            if(tempo == NULL){
                                cout << "Item " << str << " does not exists in the " << section << "." << endl;
                                cout << "Enter a title for the item: " ;
                                cin >>  str;
                            }
                            else{
                                break;
                            }
                        }
                        start = chrono::high_resolution_clock::now();
                        update.remove(str);
                        stop = chrono::high_resolution_clock::now();
                        timer = (stop-start).count();
                        cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;
                        
                        BinaryNodeAVL<string> * tempo2 = NoteBookAVL;
                        while(tempo2->element != section){
                            tempo2 = tempo2->otherNode;
                        }
                        
                        AVLTree<string> tirii;
                        tirii.root = tempo2->left;
                        start = chrono::high_resolution_clock::now();
                        tirii.remove(str, tirii.root);
                        tirii.balance(tirii.root);
                        stop = chrono::high_resolution_clock::now();
                        cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;
                        cout << "The item " << str << " has been deleted." << endl;
                        
                    }
                    else{
                        cout << "Returning to main menu!!" << endl;
                    }
                }
            }
        }
        else if(choice == 4){
            string title;
            cout << "Enter a title for the section: " ;
            cin >> title;
            bool ifExist = false;
            myNode = NoteBook;
            while(myNode != NULL){
                if(myNode->element == title){
                    ifExist = true;
                    break;
                }
                else{
                    myNode = myNode->otherNode;
                }
            }
            if(ifExist){
                cout << "Section " << title << " already exists." << endl;
            }
            else{
                while(myNode->otherNode != NULL){ //creating the BST node
                    myNode = myNode->otherNode;
                }
                BinaryNode<string> * temp = new BinaryNode<string> (title, title, NULL, NULL);
                myNode->otherNode = temp;  //until here
                
                BinaryNodeAVL<string> * temp2 = NoteBookAVL; //creating the AVL node
                while(temp2->otherNode != NULL){
                    temp2 = temp2->otherNode;
                }
                BinaryNodeAVL<string> * newNode = new BinaryNodeAVL<string> (title, title, NULL, NULL);
                BinaryNodeAVL<string> * rootNode = new BinaryNodeAVL<string> ("root", "line", NULL, NULL);
                newNode->left = rootNode;  //until here
            }
            
        }
        else if(choice == 5){
            string title;
            cout << "Enter the title of the section: " ;
            cin >> title;
            bool ifExist = false;
            myNode = NoteBook;
            while(myNode != NULL){
                if(myNode->element == title){
                    ifExist = true;
                    break;
                }
                else{
                    myNode = myNode->otherNode;
                }
            }
            if(!ifExist){
                cout << "Section " << title << " does not exist." << endl;
            }
            else{
                myNode = NoteBook;
                while(myNode->otherNode->element != title){
                    myNode = myNode->otherNode;
                }
                BinaryNode<string> * toBeDeleted = myNode->otherNode;
                myNode->otherNode = toBeDeleted->otherNode;
                BinarySearchTree<string> myTree("ITEM_NOT_FOUND");
                myTree.root = toBeDeleted;
                myTree.makeEmpty();  //deleted the BST
                
                BinaryNodeAVL<string> * myNodeAVL = NoteBookAVL;
                while(myNodeAVL->otherNode->element != title){
                    myNodeAVL = myNodeAVL->otherNode;
                }
                BinaryNodeAVL<string> * toBeDeletedAVL = myNodeAVL->otherNode;
                myNodeAVL->otherNode = toBeDeletedAVL->otherNode;
                AVLTree<string> myTreeAVL;
                myTreeAVL.root = toBeDeletedAVL->left;
                myTreeAVL.makeEmpty(myTreeAVL.root);  // deleted the AVLT
                
                cout << "The section has been deleted" << endl;
            }
            
        }
        else{
            cout << "Exiting the Program. BYE!" << endl << endl;
        }
    }
    
    
    return 0;
}
