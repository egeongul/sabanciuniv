#ifndef SORT_H_
#define SORT_H_

#define merge Merge
#define swap Swap
/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>

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

bool wordIn(string s1, string s2){
    if(s2 == s1)
        return true;
    else if(s1.length() > s2.length()){
        int wordLen = s2.length();
        for(int i = 0; i < wordLen-1; i++){
            if(s1[i] != s2[i])
                return false;
        }
        return true;
    }
    return false;
}

template <class Comparable>
void insertionSort(vector<Comparable>& a)
{
    for (int p = 1; p < a.size(); p++)
    {
        Comparable tmp = a[p];
        
        int j;
        for (j = p; j > 0 && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}


template <class Comparable>
void shellsort(vector<Comparable>& a)
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (int i = gap; i < a.size(); i++)
        {
            Comparable tmp = a[i];
            int j = i;

            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
}


template <class Comparable>
void heapsort(vector<Comparable>& a)
{
    for (int i = a.size() / 2; i >= 0; i--)
        percDown(a, i, a.size());
    for (int j = a.size() - 1; j > 0; j--)
    {
        swap(a[0], a[j]);
        percDown(a, 0, j);
    }
}


inline int leftChild(int i)
{
    return 2 * i + 1;
}

template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{
    int child;
    Comparable tmp;
    
    for (tmp = a[i]; leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && a[child] < a[child + 1])
            child++;
        if (tmp < a[child])
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;
}


template <class Comparable>
void mergeSort(vector<Comparable>& a)
{
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}


template <class Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}


template <class Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (a[leftPos] < a[rightPos])
            tmpArray[tmpPos++] = a[leftPos++];
        else
            tmpArray[tmpPos++] = a[rightPos++];

    while (leftPos <= leftEnd)    // Copy rest of first half
        tmpArray[tmpPos++] = a[leftPos++];

    while (rightPos <= rightEnd)  // Copy rest of right half
        tmpArray[tmpPos++] = a[rightPos++];

    // Copy tmpArray back
    for (int i = 0; i < numElements; i++, rightEnd--)
        a[rightEnd] = tmpArray[rightEnd];
}

/**
 * Quicksort algorithm (driver).
 */
template <class Comparable>
void quicksort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}


template <class Comparable>
inline void swap(Comparable& obj1, Comparable& obj2)
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}


template <class Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;
    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    // Place pivot at position right - 1
    swap(a[center], a[right - 1]);
    return a[right - 1];
}


template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right)
{
    if (left + 10 <= right)
    {
        Comparable pivot = median3(a, left, right);
        
        
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        
        swap(a[i], a[right - 1]);  // Restore pivot
        
        quicksort(a, left, i - 1);     // Sort small elements
        quicksort(a, i + 1, right);    // Sort large elements
    }
    else
        insertionSort(a, left, right);
}


template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
    for (int p = left + 1; p <= right; p++)
    {
        Comparable tmp = a[p];
        int j;

        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}


template <class Comparable>
void quickSelect(vector<Comparable>& a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}


template <class Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k)
{
    if (left + 10 <= right)
    {
        Comparable pivot = median3(a, left, right);
        
        
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        
        swap(a[i], a[right - 1]);  // Restore pivot
        
        // Recurse; only this part changes
        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    }
    else
        insertionSort(a, left, right);
}


template <class Comparable>
class Pointer
{
public:
    Pointer(Comparable* rhs = NULL) : pointee(rhs) { }

    bool operator<(const Pointer& rhs) const
    {
        return *pointee < *rhs.pointee;
    }
    operator Comparable* () const
    {
        return pointee;
    }
private:
    Comparable* pointee;
};


template <class Comparable>
void largeObjectSort(vector<Comparable>& a)
{
    vector<Pointer<Comparable> > p(a.size());
    int i, j, nextj;

    for (i = 0; i < a.size(); i++)
        p[i] = &a[i];

    quicksort(p);

    // Shuffle items in place
    for (i = 0; i < a.size(); i++)
        if (p[i] != &a[i])
        {
            Comparable tmp = a[i];
            for (j = i; p[j] != &a[i]; j = nextj)
            {
                nextj = p[j] - &a[0];
                a[j] = *p[j];
                p[j] = &a[j];
            }
            a[j] = tmp;
            p[j] = &a[j];
        }
}

template <class Comparable>
bool sequentialSearch(vector<Comparable>& a, string s){
    bool isIn = false;
    for(int i = 0; i < a.size(); i++){
        if(wordIn(a[i].name, s)){
            cout << s  << " "<< a[i].surname << " " << a[i].phoneNum << " " << a[i].city << endl;
            isIn =  true;
            
        }
    }
    return isIn;
}

template <class Comparable>
bool sequentialSearch(vector<Comparable>& a, string s, string x){
    for(int i = 0; i < a.size(); i++){
        if(a[i].name == s && a[i].surname == x){
            cout << s << " " << x << " " << a[i].phoneNum << " " << a[i].city << endl;
            return true;
        }
    }
    return false;
}

template <class Comparable>
void binarySearch(vector<Comparable> vect, int l, int r, string x, bool & found)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        
        if (wordIn(vect[mid].name, x))
            found = true;
        if (CompareSTR(vect[mid].name, x))
            return binarySearch(vect, l, mid - 1, x, found);
        
        return binarySearch(vect, mid + 1, r, x, found);
    }

}

template <class Comparable>
bool binarySearch(vector<Comparable> vect, int l, int r, string x, string s)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        
        if (vect[mid].name == x && vect[mid].surname == s){
            cout << x << " " << s << " " << vect[mid].phoneNum << " " << vect[mid].city << endl;
            return true;
        }
        if (CompareSTR(vect[mid].name, x))
            return binarySearch(vect, l, mid - 1, x, s);
        
        return binarySearch(vect, mid + 1, r, x, s);
    }
    
    return false;
}

#endif
