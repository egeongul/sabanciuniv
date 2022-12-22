using namespace std;
#include <string>
#include <vector>
struct StackNode // filo
{
	string str;
	StackNode *next;
};

class DynIntStack
{
private:
	
    vector<string> vect;

public:
    StackNode *top;
	DynIntStack(void);
	void push(string);
	void pop(string&);
	bool isEmpty(void);
    void printstack(void);
    void clearstack(StackNode*);
};
