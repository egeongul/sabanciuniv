

#ifndef AVL_h
#define AVL_h


#include "iostream"
#include "string"

using namespace std;

bool CompareSTR(string s1, string s2){
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
class AVLTree;

template <class Comparable>
class BinaryNodeAVL
{
public:
    Comparable element;
    string name;
    BinaryNodeAVL  *left;
    BinaryNodeAVL  *right;
    BinaryNodeAVL  *otherNode;
    BinaryNodeAVL( const Comparable & theElement, string nam,
               BinaryNodeAVL<Comparable> *lt, BinaryNodeAVL<Comparable> *rt )
    : element( theElement ), left( lt ), right( rt ), name(nam) { }
    friend class AVLTree<Comparable>;
    
};


template <class Comparable>
class AVLTree
{
public:
    int height(BinaryNodeAVL<Comparable> *);
    int difference(BinaryNodeAVL<Comparable> *);
    BinaryNodeAVL<Comparable> * rr_rotat(BinaryNodeAVL<Comparable> *);
    BinaryNodeAVL<Comparable> * ll_rotat(BinaryNodeAVL<Comparable> *);
    BinaryNodeAVL<Comparable> * lr_rotat(BinaryNodeAVL<Comparable>*);
    BinaryNodeAVL<Comparable> * rl_rotat(BinaryNodeAVL<Comparable> *);
    BinaryNodeAVL<Comparable> * balance(BinaryNodeAVL<Comparable> *);
    BinaryNodeAVL<Comparable> * insert(BinaryNodeAVL<Comparable> *, Comparable, Comparable);
    BinaryNodeAVL<Comparable> * find( const Comparable & x, BinaryNodeAVL<Comparable> *t ) const;
    BinaryNodeAVL<Comparable> * findMin( BinaryNodeAVL<Comparable> *t ) const;
    void show(BinaryNodeAVL<Comparable> *, int);
    void inorder(BinaryNodeAVL<Comparable> *) ;
    void printTree();
    void makeEmpty( BinaryNodeAVL<Comparable> * & t ) const;
    void remove( const Comparable & x, BinaryNodeAVL<Comparable> * & t ) const;
    BinaryNodeAVL<Comparable> * root;
    AVLTree() {
        root = NULL;
    }
private:
    void printTree( BinaryNodeAVL<Comparable> *) const;
};

template <class Comparable>
int AVLTree<Comparable>::height(BinaryNodeAVL<Comparable> * t){
    int h = 0;
    if (t != NULL) {
          int leftHeight = height(t->left);
          int rightHeight = height(t->right);
          int maxHeight = max(leftHeight, rightHeight);
          h = maxHeight + 1;
       }
    return h;
}

template <class Comparable>
int AVLTree<Comparable>::difference(BinaryNodeAVL<Comparable> * t){
    int leftHeight = height(t->left);
    int rightHeight = height(t->right);
    int diff = leftHeight - rightHeight;
    return diff;
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::rr_rotat(BinaryNodeAVL<Comparable> * p){
    BinaryNodeAVL<Comparable> *t;
    t = p->right;
    p->right = t->left;
    t->left = p;
    return t;
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::ll_rotat(BinaryNodeAVL<Comparable> * p){
    BinaryNodeAVL<Comparable> *t;
    t = p->left;
    p->left = t->right;
    t->right = p;
    return t;
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::lr_rotat(BinaryNodeAVL<Comparable> * p){
    BinaryNodeAVL<Comparable> *t;
    t = p->left;
    p->left = rr_rotat(t);
    return ll_rotat(p);
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::rl_rotat(BinaryNodeAVL<Comparable> * p){
    BinaryNodeAVL<Comparable> *t;
    t = p->right;
    p->right = ll_rotat(t);
    return rr_rotat(p);
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::balance(BinaryNodeAVL<Comparable> * t){
    int num = difference(t);
    if (num > 1) {  //inbalanced on left
        if (difference(t->left) > 0)
            t = ll_rotat(t);
        else
            t = lr_rotat(t);
    } else if (num < -1) { //inbalanced on right
        if (difference(t->right) > 0)
            t = rl_rotat(t);
        else
            t = rr_rotat(t);
    }
    return t;
}

template <class Comparable>
BinaryNodeAVL<Comparable> *AVLTree<Comparable>::insert(BinaryNodeAVL<Comparable> * t, Comparable s, Comparable str){
    if (t == NULL) {
        t = new BinaryNodeAVL<Comparable>(s, str, NULL, NULL);
        t->element = s;
        t->name = str;
        t->left = NULL;
        t->right = NULL;
        return t;
       }
    else if (!CompareSTR(s, t->element)) {
        t->left = insert(t->left, s, str);
        t = balance(t);
       }
    else if (CompareSTR(s, t->element)) {
        t->right = insert(t->right, s, str);
        t = balance(t);
       }
    return t;
}
template <class Comparable>
void AVLTree<Comparable>::inorder(BinaryNodeAVL<Comparable> *t) {
    if (t != NULL){
        inorder(t->left);
        cout << t->element << endl;
        inorder(t->right);
    }
}

template <class Comparable>
void AVLTree<Comparable>::
printTree( BinaryNodeAVL<Comparable> * t ) const
{
    if ( t != NULL)
    {
        printTree( t->left );
        if(t->element != root->element){
            if(t->element != "root")
                cout << t->element << " "  << endl;
        }
        
        printTree( t->right );
    }
}

template <class Comparable>
void AVLTree<Comparable>::
printTree( )
{
    if( root == NULL )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}

template <class Comparable>
void AVLTree<Comparable>::
makeEmpty( BinaryNodeAVL<Comparable> * & t ) const
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
BinaryNodeAVL<Comparable> *
AVLTree<Comparable>::
find( const Comparable & x, BinaryNodeAVL<Comparable> * t ) const
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

template <class Comparable> //private recursive findMin
BinaryNodeAVL<Comparable> *
AVLTree<Comparable>::findMin( BinaryNodeAVL<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Comparable>
void AVLTree<Comparable>::
remove( const Comparable & x, BinaryNodeAVL<Comparable> * & t )
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
        BinaryNodeAVL<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}




#endif /* AVL_h */
