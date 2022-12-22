#include <iostream>
#include "DynIntQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynIntQueue::DynIntQueue()
{
	front = NULL;
	rear = NULL;
	#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynIntQueue::enqueue(string name, string function_name, int ID)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(name, function_name, ID);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(name, function_name, ID);
		rear = rear->next;
	}
	#ifdef _DEBUG
		cout << num << " enqueued\n";
	#endif
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynIntQueue::dequeue(string &name, string& function_name, int& ID)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		name = front->name;
        function_name = front->function_name;
        ID = front->ID;
		temp = front;
		front = front->next;
		delete temp;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynIntQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynIntQueue::clear()
{
	string name;   // Dummy variable for dequeue
    string functionname;
    int ID;
	while(!isEmpty())
		dequeue(name, functionname, ID); //delete all elements
}
