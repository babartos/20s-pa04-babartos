//
// Created by mattb on 5/3/2020.
//

#ifndef INC_20S_3353_PA00_TRIVIALSOLN_H
#define INC_20S_3353_PA00_TRIVIALSOLN_H

#include <iostream>
#include <string>
#include "directedGraph.h"
using namespace std;

class trivialSoln {
public:
    trivialSoln();
    ~trivialSoln();
    void readGraphInputFile(string fileName); //reads in a directedGraph file
    void outputStronglyConnected();
    void outputStronglyConnected(string fileName);
private:
    directedGraph<string> theMap;
    string CurrentFileName;
    ofstream outFile;
};


#endif //INC_20S_3353_PA00_TRIVIALSOLN_H
