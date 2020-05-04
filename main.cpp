#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "directedGraph.h"
#include "trivialSoln.h"
using namespace std;

int main(int argc, char* argv[]) {
    //PROBLEM: check if a directed graph is strongly connected
    //a graph is strongly connected if there is a path between every two pairs of verticies
    string fileName1 = "g1.txt"; //is a strongly connected graph
    string fileName2 = "g2.txt"; //is not a strongly connected graph
    ////1) Trivial solution using a DFS
    trivialSoln firstSolution;
    firstSolution.outputStronglyConnected(fileName1);
    firstSolution.outputStronglyConnected(fileName2);
    ////2) Non-Trivial solution using Kosajru's algorithm
    
    cout << "helloworld" << endl;
    return 0;
}