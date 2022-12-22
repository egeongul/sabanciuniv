#ifndef DYNINTQUEUE_H //fifo
#define DYNINTQUEUE_H
using namespace std;
#include <string>
struct QueueNode
{
    string name;
    string function_name;
    int ID;
    
	QueueNode *next;
    QueueNode(string _name, string _function_name, int _ID, QueueNode *ptr = NULL)
	{
		name = _name;
        ID = _ID;
        function_name = _function_name;
		next = ptr;
	}
};

class DynIntQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;
public:
	// Constructor.
	DynIntQueue();
	
	// Member functions.
	void enqueue(string, string, int);
	void dequeue(string&, string&, int&);
	bool isEmpty() const;
	void clear();
};
#endif
