//
// Created by mattb on 4/13/2020.
//

#ifndef INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
#define INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
#include <iostream>
#include "disjointSetInterface.h"
#include <list>
using namespace std;
//Custom implementation:
//using arrays to create "virtual trees" in a sense
//will be explotiing O(1) arrays to get better performance
//have a size with the number of elements
template <typename T>
class customDisjointSet : public disjointSetInterface<T> {
private:
    T* parentArray;
    list<T>* currListRepresentation; //when finding an element, we return a pointer to a linked list representation of our element
    int size;
    int ArrayLength;
public:
    customDisjointSet() {size = 0; ArrayLength = 0;}
    void makeSet(T);
    void unionSets(T,T);
    list<T>* find(T); //return a list representation
    int getSize();
};

template <typename T>
void customDisjointSet<T>::makeSet(T) {
    T* temp = parentArray;
    if(parentArray == nullptr) {
    }
    else {


    }
}

template <typename T>
void customDisjointSet<T>::unionSets(T,T) {

}

template <typename T>
list<T>* customDisjointSet<T>::find(T) { //when finding an element, we return a pointer to a linked list representation of our element
    cout << "not implemented";
}

template <typename T>
int customDisjointSet<T>::getSize() {

}


#endif //INC_20S_3353_PA00_CUSTOMDISJOINTSET_H
