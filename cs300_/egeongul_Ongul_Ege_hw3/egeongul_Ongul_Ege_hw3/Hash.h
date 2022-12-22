#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

template <class HashedObj>
struct List{
    HashedObj info;
    List * next;
    map<string, int> mp{
        
    };
};

template <class HashedObj>
class Hash{
public:
    Hash(int);
    int hash(HashedObj key);
    void insert(HashedObj name);
    void deleteNode(HashedObj name);
    void debugger();
    void makeEmpty();
    void resizeMe();
    void find(HashedObj myInfo);
    Hash<HashedObj>  resize();
    Hash<HashedObj> & operator = (Hash<HashedObj> rhs);
    int tableSize;
    int numOfItems;
    double loadFactor;
    vector<List<HashedObj>> myVect;
    int uniqueCount;
    string fileName;
};

template <class HashedObj>
int Hash<HashedObj>::hash(HashedObj key){
    int hashValue = 0;
    for(int i = 0; i < key.length(); i++){
        hashValue += (int)key[i];
    }
    return hashValue % tableSize;
}

template <class HashedObj>  //CONSTRUCTOR
Hash<HashedObj>::Hash(int x){
    for(int i = 0 ; i < x ; i++){
        List<HashedObj>  list;
        list.info = "unknown";
        list.next = NULL;
        list.mp["unknown"] = -1;
        myVect.push_back(list);
    }
    tableSize = x;
    loadFactor = 1;
    numOfItems = 0;
    uniqueCount = 0;
    fileName = "unknown";
}

template <class HashedObj>
void Hash<HashedObj>::insert(HashedObj name){
    
    int idx = hash(name);
    if(myVect[idx].info == "unknown"){
        myVect[idx].info = name;
        uniqueCount++;
        myVect[idx].mp[fileName] = 1;
    }
    else if(myVect[idx].info == name){
        myVect[idx].mp[fileName] += 1;
//        if(myVect[idx].mp[fileName] == 2)
//            uniqueCount--;
    }
    else{
        List<HashedObj> * ptr = myVect[idx].next;
        if( ptr == NULL){
            ptr = new List<HashedObj>;
            ptr->info = name;
            ptr->next = NULL;
            myVect[idx].next = ptr;
            uniqueCount++;
            ptr->mp[fileName] = 1;
        }
        else{
            while( ptr->next != NULL && ptr->info != name){
                ptr = ptr->next;
            }
            if(ptr->info == name){
                ptr->mp[fileName] += 1;
//                if(ptr->mp[fileName] == 2)
//                    uniqueCount--;
            }
            else if(ptr->next == NULL){
                List<HashedObj> * temp = new List<HashedObj>;
                temp->info = name;
                temp->next = NULL;
                ptr->next = temp;
                uniqueCount++;
                temp->mp[fileName] = 1;
            }
            
        }
    }
    numOfItems ++;
    loadFactor = double(numOfItems)/tableSize;
}

template <class HashedObj>
void Hash<HashedObj>::debugger(){
    for(int i = 0; i < tableSize; i++){
        cout <<"-----" << endl;
        cout << i << " ---> " << myVect[i].info;
        List<HashedObj> * ptr = myVect[i].next;
//        for ( auto it = myVect[i].mp.begin(); it != myVect[i].mp.end(); ++it  )
//        {
//            if(it->first != "unknown")
//                cout << it->first << '\t' << it->second << endl;
//        }
        while(ptr != NULL){
            cout << " ---> " << ptr->info;
            ptr = ptr->next;
        }
        cout << endl;
    }
}

template <class HashedObj>
void Hash<HashedObj>::deleteNode(HashedObj name){
    int idx = hash(name);
    if(myVect[idx].info == "unknown"){
        cout << "Does not exist " << endl;
    }
    else if(myVect[idx].info == name){
        List<HashedObj> * ptr = myVect[idx].next;
        myVect[idx].info = ptr->info;
        List<HashedObj> * temp = ptr->next;
        myVect[idx].next = temp;
        delete ptr;
    }
    else{
        List<HashedObj> * ptr = myVect[idx].next;
        if(ptr->info != name){
            while( ptr->next->info != name){
                ptr = ptr->next;
                if( ptr == NULL){
                    return;
                }
            }
            List<HashedObj> * temp = ptr->next;
            ptr->next = temp->next;
            delete temp;
        }
        else{
            List<HashedObj> * temp = ptr->next;
            myVect[idx].next = temp;
            delete ptr;
        }
    }
}

template <class HashedObj>
void Hash<HashedObj>::find(HashedObj myInfo){
    int idx = hash(myInfo);
    string itemNoFo = "ITEM_NOT_FOUND";
    if(myVect[idx].info == myInfo){
        for ( auto it = myVect[idx].mp.begin(); it != myVect[idx].mp.end(); ++it  )
        {
            if(it->first != "unknown")
                cout << "In Document " << it->first << ", " << myVect[idx].info << " found " << it->second  << " times. " ;
        }
        cout << endl;
    }
    else{
        List<HashedObj> * ptr = myVect[idx].next;
        if(ptr != NULL && ptr->info != myInfo){
            while( ptr != NULL && ptr->info != myInfo){
                ptr = ptr->next;
            }
        }
        if(ptr != NULL){
            for ( auto it = ptr->mp.begin(); it != ptr->mp.end(); ++it  )
            {
                if(it->first != "unknown")
                    cout << "In Document " << it->first << ", " << ptr->info << " found " << it->second  << " times. " ;
            }
            cout << endl;
        }
        else{
            cout << myInfo << " does not exist" << endl;
            ptr = NULL;
        }
    }
}



template <class HashedObj>
void Hash<HashedObj>:: makeEmpty(){
    for(int i = 0; i < tableSize; i++){
        myVect[i].next = NULL;
        myVect[i].info = "unknown";
        myVect[i].mp.clear();
    }
}


template <class HashedObj>
Hash<HashedObj> & Hash<HashedObj>::operator =(Hash<HashedObj> rhs){
    
    this->makeEmpty();
    int diff = rhs.tableSize - tableSize;
    for(int i = 0; i < diff; i++){
        List<HashedObj>  list;
        list.info = "unknown";
        list.next = NULL;
        myVect.push_back(list);
    }
    tableSize = rhs.tableSize;
    for(int i = 0; i < rhs.tableSize; i++){
        if(rhs.myVect[i].info != "unknown"){
            insert(rhs.myVect[i].info);
            int hashVal = hash(rhs.myVect[i].info);
            for ( auto it = rhs.myVect[i].mp.begin(); it != rhs.myVect[i].mp.end(); ++it  )
            {
                    myVect[hashVal].mp[it->first] = it->second;
            }
            
            List<HashedObj> * ptr = rhs.myVect[i].next;
            while( ptr != NULL){
                insert(ptr->info);
                hashVal = hash(ptr->info);
                List<HashedObj> * itr = myVect[hashVal].next;
                while( itr != NULL){
                    if(itr->info == ptr->info)
                        break;
                    itr = itr->next;
                }
                if(itr != NULL){
                    for ( auto it = ptr->mp.begin(); it != ptr->mp.end(); ++it  )
                    {
                            itr->mp[it->first] = it->second;
                    }
                }
                ptr = ptr->next;
            }
        }
        
    }
    numOfItems = rhs.numOfItems;
    tableSize = rhs.tableSize;
    uniqueCount = rhs.uniqueCount;
    loadFactor = double(numOfItems) / tableSize;
    return *this;
}

template <class HashedObj>
Hash<HashedObj>  Hash<HashedObj>::resize(){
    int num = this->tableSize;
    int newTableSize = nextPrime(tableSize*2);
    Hash<HashedObj> HCopy(newTableSize);
//    int diff = newTableSize - HCopy.tableSize;
//    for(int i = 0; i < diff; i++){
//        List<HashedObj>  list;
//        list.info = "unknown";
//        list.next = NULL;
//        list.mp["unknown"] = -1;
//        HCopy.myVect.push_back(list);
//    }
    for(int i = 0; i < tableSize; i++){
        if(myVect[i].info != "unknown"){
            HCopy.insert(myVect[i].info);
            int hashVal = HCopy.hash(myVect[i].info);
            if(HCopy.myVect[hashVal].info == myVect[i].info){
                for ( auto it = myVect[i].mp.begin(); it != myVect[i].mp.end(); ++it  )
                {
                        HCopy.myVect[hashVal].mp[it->first] = it->second;
                }
            }
            else{
                List<HashedObj> * ptr = HCopy.myVect[hashVal].next;
                while(ptr->info != myVect[i].info){
                    ptr = ptr->next;
                }
                for ( auto it = myVect[i].mp.begin(); it != myVect[i].mp.end(); ++it  )
                {
                        ptr->mp[it->first] = it->second;
                }
            }
            List<HashedObj> * ptr = myVect[i].next;
            while( ptr != NULL){
                HCopy.insert(ptr->info);
                hashVal = HCopy.hash(ptr->info);
                if(HCopy.myVect[hashVal].info == ptr->info){
                    for ( auto it = ptr->mp.begin(); it != ptr->mp.end(); ++it  )
                    {
                            HCopy.myVect[hashVal].mp[it->first] = it->second;
                    }
                }
                else{
                    List<HashedObj> * itr = HCopy.myVect[hashVal].next;
                    while( itr->info != ptr->info){
                        itr = itr->next;
                    }
                    for ( auto it = ptr->mp.begin(); it != ptr->mp.end(); ++it  )
                    {
                            itr->mp[it->first] = it->second;
                    }
                }
                ptr = ptr->next;
            }
        }
    }
    HCopy.uniqueCount = uniqueCount;
    HCopy.numOfItems = num;
    HCopy.loadFactor = numOfItems / newTableSize;
    return HCopy;
}

