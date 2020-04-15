//
// Created by mattb on 4/13/2020.
//

#ifndef INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
#define INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
#include <iostream>
#include "disjointSetInterface.h"
#include <list>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <algorithm>
using namespace std;
//Custom implementation:
//using arrays to create "virtual trees" in a sense
//have a size array with the number of elements in each tree
//each parent will be "mapped" to the size arary
template <typename T>
class customDisjointSet : public disjointSetInterface<T> {
private:
    //private member data:
    T* parentArray; //starts off space for one hundred nodes
    int* sizeArray;
    int parentArray_length;
    int sizeArray_length;
    int maxLenghts;
    //private functions called in makeSet(), union() and makeSet()
    void printRep();
    T* findPriv(T element);
    int findRootIndex(T child);
    T* findRoot(T child);
    bool contains(list<T>&, T&);
    void printRep(T*, int);
public:
    customDisjointSet();
    void makeSet(T);
    void unionSets(T,T);
    list<T> find(T); //return a list representation
    int getSize();
};


template <typename T>
customDisjointSet<T>::customDisjointSet() {
    //intilize buffer arrays with length of 100
    this->maxLenghts = 100;
    this->parentArray = new T[maxLenghts];
    this->sizeArray = new int[maxLenghts];
    this->parentArray_length = 0;
    this->sizeArray_length = 0;
    //start with one hundred for size
}

template <typename T>
void customDisjointSet<T>::makeSet(T element) {
    if(parentArray_length + 1 == maxLenghts) { //resize the array
        this->maxLenghts = this->maxLenghts * 2;
        T* temp = new T[this->maxLenghts];
        delete [] this->parentArray;
        this->parentArray = temp;
    }
    //push to the end of the array in our "buffer space" for both size and parent array
    this->parentArray[this->parentArray_length] = element;
    this->sizeArray[this->sizeArray_length] = 1;
    this->parentArray_length++;
    this->sizeArray_length++;
}

template <typename T>
void customDisjointSet<T>::unionSets(T element1, T element2) {
    //variable intilization
    T* newArray = new T[maxLenghts];
    int* newSizeArray = new int[maxLenghts];
    list<T> root1 = find(element1);
    list<T> root2 = find(element2);
    pair<int, int> sizeIndex;
    sizeIndex.first = findRootIndex(root1.front());
    sizeIndex.second = findRootIndex(root2.front());
    //iterators
    int iterOfSizeArray = 0; //controls size array index
    int indexOfCurrParent = 0; //contains where the current parent is
    int newArrayIter = 0;
    //deal with size array
    for(int j = 0; j < this->sizeArray_length; j++) {
        if(j == sizeIndex.first || j == sizeIndex.second) {
            continue;
        }
        newSizeArray[iterOfSizeArray] = this->sizeArray[j];
        iterOfSizeArray++;
    }
    int mag1 = this->sizeArray[sizeIndex.first];
    int mag2 = this->sizeArray[sizeIndex.second];
    newSizeArray[iterOfSizeArray] = ( (this->sizeArray[sizeIndex.first]) + (this->sizeArray[sizeIndex.second]) );
    this->sizeArray_length--;
    //deal with parent array
    for (int j = 0; j < this->parentArray_length; j++) { //copy this->parentArray into newArray
        T currElement = this->parentArray[j];
        if(contains(root1, currElement) || contains(root2, currElement)) { //part of the desired union set, don't copy to new array
            continue;
        }
        //copy new array
        newArray[newArrayIter] = currElement;
        newArrayIter++;
    }
    //printRep();
    //copy root1 and root2 contents into the newArray
    typename std::list<T>::iterator it1 = root1.begin(); //iterator at head of linked list
    for(int i = 0; i < root1.size(); i++) {
        T element = *it1;
        newArray[newArrayIter] = element;
        std::advance(it1, 1); //advance iterator
        newArrayIter++;
    }
    typename std::list<T>::iterator it2 = root2.begin(); //iterator at head of linked list
    for(int i = 0; i < root2.size(); i++) {
        T element = *it2;
        newArray[newArrayIter] = element;
        std::advance(it2, 1); //advance iterator
        newArrayIter++;
    }
    //parent array handled
    //printRep();
    delete [] this->parentArray;
    delete [] this->sizeArray;
    this->parentArray = newArray;
    this->sizeArray = newSizeArray;
}

template <typename T>
T* customDisjointSet<T>::findPriv(T element) { //when finding an element, we return a pointer to a linked list representation of our element
    int iterOfSizeArray = 0;
    int indexOfCurrParent = 0;
    while (true) {
        int parentArrayIterations = this->sizeArray[iterOfSizeArray];
        for(int i = 0; i < parentArrayIterations; i++) {
            if(this->parentArray[i + indexOfCurrParent] == element) { //found
                return &this->parentArray[i + indexOfCurrParent];
            }
        }
        //if not found
        iterOfSizeArray++;
        indexOfCurrParent += parentArrayIterations;
        if(indexOfCurrParent >= this->parentArray_length) {break;} //could not find
    }
    T* voidList;
    return voidList;
}

template <typename T>
int customDisjointSet<T>::getSize() {
    return this->maxLenghts;
}

//functions that are called by the class itself

template <typename T>
void customDisjointSet<T>::printRep() {
    //for debugging purposes:
    cout << "parentArr[]: ";
    for(int i = 0; i < parentArray_length; i++) {
        T element = parentArray[i] ;
        int x = 4;
        cout << parentArray[i] << " ";
    }
    cout << endl << "size[]: ";
    for (int i = 0; i < sizeArray_length; i++) {
        cout << sizeArray[i] << " ";
    }
}

template <typename T>
void customDisjointSet<T>::printRep(T* temp, int n) {
    for(int i = 0; i < n; i++) {
        cout << temp[i] << " ";
    }
}

template <typename T>
T* customDisjointSet<T>::findRoot(T child) { //finds the parent of the child
    int iterOfSizeArray = 0;
    int indexOfCurrParent = 0;
    while (true) {
        int parentArrayIterations = this->sizeArray[iterOfSizeArray];
        for(int i = 0; i < parentArrayIterations; i++) {
            if(this->parentArray[i + indexOfCurrParent] == child) { //found
                return &this->parentArray[indexOfCurrParent];
            }
        }
        //if not found
        iterOfSizeArray++;
        indexOfCurrParent += parentArrayIterations;
        if(indexOfCurrParent >= this->parentArray_length) {break;} //could not find
    }
    T* voidList;
    return voidList;
}

template <typename T>
list<T> customDisjointSet<T>::find(T findThis){
    int iterOfSizeArray = 0;
    int indexOfCurrParent = 0;
    while (true) {
        int parentArrayIterations = this->sizeArray[iterOfSizeArray];
        for(int i = 0; i < parentArrayIterations; i++) {
            if(this->parentArray[i + indexOfCurrParent] == findThis) { //found
                list<T> returnVal;
                for(int j = 0; j < parentArrayIterations; j++) {
                    returnVal.push_back(this->parentArray[indexOfCurrParent + j]);
                }
                return returnVal;
            }
        }
        //if not found
        iterOfSizeArray++;
        indexOfCurrParent += parentArrayIterations;
        if(indexOfCurrParent >= this->parentArray_length) {break;} //could not find
    }
    list<T> voidList;
    return voidList;
}

template <typename T>
bool customDisjointSet<T>::contains(list<T>& checkList, T& element) {
    //source: https://thispointer.com/c-list-find-contains-how-to-search-an-element-in-stdlist/
    typename std::list<T>::iterator it;
    // Find the iterator if element in list
    it = std::find(checkList.begin(), checkList.end(), element);
    //return if iterator points to end or not. It points to end then it means element
    // does not exists in list
    return (it != checkList.end());
}

template <typename T>
int customDisjointSet<T>::findRootIndex(T child) { //finds the parent of the child
    int iterOfSizeArray = 0;
    int indexOfCurrParent = 0;
    while (true) {
        int parentArrayIterations = this->sizeArray[iterOfSizeArray];
        for(int i = 0; i < parentArrayIterations; i++) {
            if(this->parentArray[i + indexOfCurrParent] == child) { //found
                return iterOfSizeArray; //NEWWWW
            }
        }
        //if not found
        iterOfSizeArray++;
        indexOfCurrParent += parentArrayIterations;
        if(indexOfCurrParent >= this->parentArray_length) {break;} //could not find
    }
    int notFound = -1;
    return notFound;
}



#endif //INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
