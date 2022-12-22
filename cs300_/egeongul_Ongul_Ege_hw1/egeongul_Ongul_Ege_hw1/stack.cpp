#include <iostream>
#include "stack.h"
using namespace std;

template <class Object>
Stack<Object>::Stack( )
{
      topOfStack = NULL;
}

template <class Object>
bool Stack<Object>::isFull( ) const
{
       return false;
}

template <class Object>
bool Stack<Object>::isEmpty( ) const
{
    if(topOfStack == NULL){
        return true;
    }
}

template <class Object>
void Stack<Object>::makeEmpty()
{
    while (!isEmpty())
         pop();
}

template <class Object>
void Stack<Object>::pop()
{
    if ( !isEmpty( ) ){
        ListNode *oldTop = topOfStack;
        topOfStack = topOfStack->next;
        delete oldTop;
    }
}

template <class Object>
void Stack<Object>::push( const Object & x )
{
     topOfStack = new ListNode( x, topOfStack );
}

template <class Object>
Object Stack<Object>::topAndPop( )
{
     Object topItem = top( );
     pop( );
     return topItem;
}

template <class Object>
const Object & Stack<Object>::top( ) const
{
    if ( isEmpty( ) )
        cout << "Stack is empty" << endl;
    return topOfStack->element;
}

template <class Object>
const Stack<Object> & Stack<Object>::
operator=( const Stack<Object> & rhs )
{
    if ( this != &rhs )
    {
        makeEmpty( );
        if ( rhs.isEmpty( ) )
            return *this;
        
        ListNode *rptr = rhs.topOfStack;
        ListNode *ptr  = new ListNode( rptr->element );
        topOfStack = ptr;
        
        for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
            ptr = ptr->next = new ListNode( rptr->element );
    }
    return *this;
}
