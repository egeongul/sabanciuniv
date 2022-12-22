//
//  BST.h
//  egeongul_ongul_ege_hw2
//
//  Created by Ege Öngül on 6.04.2022.
//
#ifndef BST_h
#define BST_h

using namespace std;
#include "iostream"
#include "string"
#include "chrono"

bool compareSTR(string s1, string s2){
    if(s1.length() >= s2.length()){
        unsigned long int count = s2.length();
        for(int i = 0; i < count; i++){
            if(s1[i] > s2[i]){
                return true;
            }
            else if(s1[i] < s2[i]){
                return false;
            }
        }
    }
    else if(s1.length() < s2.length()){
        unsigned long int count = s1.length();
        for(int i = 0; i < count; i++){
            if(s1[i] > s2[i]){
                return true;
            }
            else if(s1[i] < s2[i]){
                return false;
            }
        }
    }
    return true;
}

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
public:
    Comparable element;
    string name;
    BinaryNode  *left;
    BinaryNode  *right;
    BinaryNode * otherNode;
    
    BinaryNode( const Comparable & theElement, string nam,
               BinaryNode *lt, BinaryNode *rt )
    : element( theElement ), left( lt ), right( rt ), name(nam) { }
    friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
    
public:
    explicit BinarySearchTree( const Comparable & notFound );
    BinarySearchTree( const BinarySearchTree & rhs );
//    ~BinarySearchTree( );
    
    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const;
    BinaryNode<Comparable> * find( const Comparable & x,
                                  BinaryNode<Comparable> *t ) const;
    bool isEmpty( ) const;
    void printTree( ) const;
    
    void makeEmpty( );
    void insert( const Comparable & x, string );
    void remove( const Comparable & x );
    
    const BinarySearchTree & operator=( BinaryNode<Comparable>* );
    BinaryNode<Comparable> *root;
    
    const Comparable & elementAtN( BinaryNode<Comparable> *t ) const;
    const Comparable & findN( const Comparable & x ) const;
    BinaryNode<Comparable> * findN( const Comparable & x,
                                  BinaryNode<Comparable> *t ) const;
    
private:
    
    const Comparable ITEM_NOT_FOUND;
    
    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
    
    
    
    void insert( const Comparable & x, BinaryNode<Comparable> * & t, string ) const;
    void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    void makeEmpty( BinaryNode<Comparable> * & t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};

template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree(const Comparable & notFound ) :
ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const{
    if(root == NULL){
        return true;
    }
    return false;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
elementAt( BinaryNode<Comparable> *t ) const
{
//    return t == NULL ? ITEM_NOT_FOUND : t->element;
    if(t != NULL){
        return t->name;
    }
    else
        return ITEM_NOT_FOUND;
}

template <class Comparable> //non-private find that takes only the comparable object that you search as parameter
const Comparable & BinarySearchTree<Comparable>::
find( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}

template <class Comparable>  // private find function that takes 2 parameters
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::
find( const Comparable & x, BinaryNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else if( !compareSTR(x, t->element))
        return find( x, t->left );
    else if( compareSTR(x, t->element) )
        if(x == t->element){
            return t;
        }
        return find( x, t->right );
    for(int i = 0; i < 10000000; i++){
    }
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

template <class Comparable> //private recursive findMin
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

template <class Comparable>   //private recursive findMax
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )
const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template <class Comparable> //public
void BinarySearchTree<Comparable>::
insert( const Comparable & x, string name)
{
    insert( x, root, name );
}

template <class Comparable>  //private
void BinarySearchTree<Comparable>::
insert( const Comparable & x, BinaryNode<Comparable> * & t, string name) const
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( x,name, NULL, NULL );
    else if( !compareSTR(x, t->element) )
        insert( x, t->left, name );  // insert at the left or
    else if( compareSTR(x, t->element) )
        insert( x, t->right, name );  // right subtree
    else
        ;  // Duplicate; do nothing
}


template <class Comparable>
void BinarySearchTree<Comparable>::remove
( const Comparable & x )
{
    remove( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::
remove( const Comparable & x, BinaryNode<Comparable> * & t )
const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

template <class Comparable>
        void BinarySearchTree<Comparable>::makeEmpty( )
        {
             makeEmpty( root );
        }

template <class Comparable>
        void BinarySearchTree<Comparable>::
        makeEmpty( BinaryNode<Comparable> * & t ) const
        {
            if( t != NULL )
            {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = NULL;
        }

template <class Comparable>
void BinarySearchTree<Comparable>::
printTree( BinaryNode<Comparable> * t ) const
{
    if ( t != NULL)
    {
        printTree( t->left );
        if(t->element != root->element){
            cout << t->element << " "  << endl;
        }
        
        printTree( t->right );
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::
printTree( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}

//template <class Comparable> //destructor
//BinarySearchTree<Comparable>::~BinarySearchTree( )
//{
//    makeEmpty();
//}

template <class Comparable>   //deep copy
BinarySearchTree<Comparable>::
BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::
clone( BinaryNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable>
        ( t->element,
         clone( t->left ),
         clone( t->right ) );
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
elementAtN( BinaryNode<Comparable> *t ) const
{
//    return t == NULL ? ITEM_NOT_FOUND : t->element;
    if(t != NULL){
        return t->element;
    }
    else
        return ITEM_NOT_FOUND;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
findN( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}

template <class Comparable> 
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::
findN( const Comparable & x, BinaryNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else if( !compareSTR(x, t->element))
        return find( x, t->left );
    else if( compareSTR(x, t->element) )
        if(x == t->element){
            return t;
        }
        return find( x, t->right );
}



#endif /* BST_h */
