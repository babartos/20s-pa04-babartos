//
// Created by mattb on 5/3/2020.
//

#ifndef INC_20S_3353_PA00_TRIVIALSOLN_H
#define INC_20S_3353_PA00_TRIVIALSOLN_H

#include <iostream>
#include <string>
#include "graph.h"
using namespace std;

class trivialSoln {
public:
    //trivialSoln();
    void readGraphInputFile(string fileName); //reads in a graph file
    void outputCommunties();
private:
    graph<string> theMap;

};


#endif //INC_20S_3353_PA00_TRIVIALSOLN_H
