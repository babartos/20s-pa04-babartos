//
// Created by mattb on 5/4/2020.
//

#ifndef INC_20S_3353_PA00_ROBUSTSOLN_H
#define INC_20S_3353_PA00_ROBUSTSOLN_H

#include <iostream>
#include <string>
#include "directedGraph.h"
#include <chrono>
#include <ctime>
using namespace std;

class robustSoln {
public:
    robustSoln();
    ~robustSoln();
    void readGraphInputFile(string fileName); //reads in a directedGraph file
    void outputStronglyConnected();
    void outputStronglyConnected(string fileName);
    void collectTimingData();
private:
    directedGraph<string> theMap;
    string CurrentFileName;
    ofstream outFile;
    std::chrono::time_point<std::chrono::system_clock> start, end; //varaible declaration
};


#endif //INC_20S_3353_PA00_ROBUSTSOLN_H
