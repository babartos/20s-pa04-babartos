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
using namespace std;
//Custom implementation:
//using arrays to create "virtual trees" in a sense
//will be explotiing O(1) arrays to get better performance
//have a size array with the number of elements in each tree
//each parent will be "mapped" to the size arary
template <typename T>
class customDisjointSet /*: public disjointSetInterface<T> */ {
private:
    T* parentArray; //starts off space for one thousand nodes
    int* sizeArray;
    int parentArray_length;
    int sizeArray_length;
    int maxLenghts;
public:
    customDisjointSet();
    void makeSet(T);
    void unionSets(T,T);
    list<T> find(T); //return a list representation
    int getSize();
    void printRep();
    T* findPriv(T element);
    T* findRoot(T child);
};


template <typename T>
customDisjointSet<T>::customDisjointSet() {
    this->maxLenghts = 100;
    this->parentArray = new T[maxLenghts];
    this->sizeArray = new int[maxLenghts];
    this->parentArray_length = 0;
    this->sizeArray_length = 0;
    //start with one hundred
}

template <typename T>
void customDisjointSet<T>::makeSet(T element) {
    if(parentArray_length + 1 == maxLenghts) { //resize the array
        //implement me
    }
    //push to the end of the array in our "buffer space"
    this->parentArray[this->parentArray_length] = element;
    this->sizeArray[this->sizeArray_length] = 1;
    this->parentArray_length++;
    this->sizeArray_length++;
}

template <typename T>
void customDisjointSet<T>::unionSets(T element1, T element2) {
//    T* newArray = new T[maxLenghts];
//    list<T> root1 = find(element1);
//    list<T> root2 = find(element2);
//    int iterOfSizeArray = 0;
//    int indexOfCurrParent = 0;
//    while (true) {
//        int parentArrayIterations = this->sizeArray[iterOfSizeArray];
//        for(int i = 0; i < parentArrayIterations; i++) {
//            if(this->parentArray[i + indexOfCurrParent] == element) { //found
//                return &this->parentArray[i + indexOfCurrParent];
//            }
//        }
//        //if not found
//        iterOfSizeArray++;
//        indexOfCurrParent += parentArrayIterations;
//        if(indexOfCurrParent + 1 >= this->parentArray_length) {break;} //could not find
//    }

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
    return 5;
}

//functions that are called by the class itself

template <typename T>
void customDisjointSet<T>::printRep() {
    cout << "parentArr[]: ";
    for(int i = 0; i < parentArray_length; i++) {
        cout << parentArray[i] << " ";
    }
    cout << endl << "size[]: ";
    for (int i = 0; i < sizeArray_length; i++) {
        cout << sizeArray[i] << " ";
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
#endif //INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
