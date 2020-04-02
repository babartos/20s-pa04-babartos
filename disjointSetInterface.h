//
// Created by mattb on 4/1/2020.
//

#ifndef INC_20S_3353_PA00_DISJOINTSETINTERFACE_H
#define INC_20S_3353_PA00_DISJOINTSETINTERFACE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class disjointSetInterface {
public:
    disjointSetInterface() {}
    virtual void makeSet() = 0;
    virtual void unionSets() = 0;
    //virtual auto* find() = 0;
    virtual void printType() = 0;
};


#endif //INC_20S_3353_PA00_DISJOINTSETINTERFACE_H