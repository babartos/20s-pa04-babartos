//
// Created by mattb on 4/1/2020.
//

#ifndef INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H
#define INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H

#include <iostream>
#include "disjointSetInterface.h"
using namespace std;

class linkedListDisjointSet : public disjointSetInterface {
private:
    //int x;
public:
    linkedListDisjointSet() {}
    void makeSet();
    void unionSets();
    void printType();
};

void linkedListDisjointSet::makeSet() {
    cout << "makeSet" << endl;
}

void linkedListDisjointSet::unionSets() {
    cout << "union sets" << endl;
}

void linkedListDisjointSet::printType() {
    cout << "trivial linked list implementation" << endl;
}

#endif //INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H
