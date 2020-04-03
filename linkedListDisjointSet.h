//
// Created by mattb on 4/1/2020.
//

#ifndef INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H
#define INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H

#include <iostream>
#include "disjointSetInterface.h"
using namespace std;

template <typename T>
class linkedListDisjointSet : public disjointSetInterface<T> {
private:
    vector<list<T>> theSet;
    int size;
public:
    linkedListDisjointSet() {
        size = 0;
    }
    void makeSet(T);
    void unionSets();
    void printType();
    T* find();
    int getSize();
};

template <typename T>
void linkedListDisjointSet<T>::makeSet(T element) {
    cout << "makeSet" << element << endl;
    list<T> newList;
    newList.push_back(element);
    theSet.push_back(newList);
    size++;
}

template <typename T>
void linkedListDisjointSet<T>::unionSets() {
    cout << "union sets" << endl;
}

template <typename T>
void linkedListDisjointSet<T>::printType() {
    cout << "trivial linked list implementation" << endl;
}

template <typename T>
T* linkedListDisjointSet<T>::find() {
    cout << "find function" << endl;
}

template <typename T>
int linkedListDisjointSet<T>::getSize() {
    cout << "find function" << endl;
    return size;
}
#endif //INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H