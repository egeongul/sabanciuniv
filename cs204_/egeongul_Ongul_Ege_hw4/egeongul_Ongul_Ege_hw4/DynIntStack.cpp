#include <iostream>
#include "DynIntStack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(string str)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->str = str;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
    vect.push_back(newNode->str);
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(string &str)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		str = top->str;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

void DynIntStack::printstack(){
    
    unsigned long int size = vect.size();
    
    if(size == 0){
        cout << "The stack is empty" << endl;
    }
    else{
        for(int i= 0; i<size; i++){
            cout << vect[i] << endl;
        }
    }
}

//void DynIntStack::clearstack(void){
//    int counter = 0;
//    while(top != NULL){
//        StackNode* temp = top->next;
//        delete top;
//        top = temp;
//        counter += 1;
//    }
//    for(int i = 0; i < counter; i++){
//        vect.pop_back();
//    }
//}
void DynIntStack::clearstack(StackNode* node){
    int counter = 0;
    while(top != node){
        StackNode* temp = top->next;
        delete top;
        top = temp;
        counter += 1;
    }
    for(int i = 0; i < counter; i++){
        vect.pop_back();
    }
}
