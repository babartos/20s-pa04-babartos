//
// Created by mattb on 4/1/2020.
//

#ifndef INC_20S_3353_PA00_DISJOINTSETINTERFACE_H
#define INC_20S_3353_PA00_DISJOINTSETINTERFACE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class disjointSetInterface {
public:
    disjointSetInterface() {}
    virtual void makeSet(T) = 0;
    virtual void unionSets(T,T) = 0;
    virtual list<T>* find(T) = 0;
    virtual void printSet() = 0;
};


#endif //INC_20S_3353_PA00_DISJOINTSETINTERFACE_H