//
// Created by mattb on 5/4/2020.
//

#include "robustSoln.h"
#include <string>
#include <vector>
#include <algorithm>

robustSoln::robustSoln() {
    this->CurrentFileName = "not intilized";
    outFile.open("outputTrivial.txt");
    outFile << "Trivial solution" << endl;
}

robustSoln::~robustSoln() {
    outFile.close();
}

void robustSoln::readGraphInputFile(string fileName) { //reads in a directedGraph file
    this->CurrentFileName = fileName;
    const char *here = fileName.c_str();
    theMap.setInFile(here);
    ifstream inFile(here); //opens g1.txt
    if(!inFile.is_open()) {
        cout << "could not find directedGraph input file: " << fileName << endl;
        return;
    }
    int lineNum;
    inFile.ignore();// ignore [
    inFile >> lineNum; //number of vertex
    inFile.ignore(); //ignore ]
    for (int i = 0; i < lineNum; i++) { //add all vertecies ot the directedGraph
        string temp;
        inFile >> temp;
        theMap.addVertex(temp);
    }
    string buffer;
    getline(inFile, buffer); //ignore the last new line character
    getline(inFile, buffer); //reads in [undirected]
    //buffer = "[undirected]"
    //read in the rest of the file (ALL EDGES)
    while(!inFile.eof()) {
        string vertex1;
        string dash;
        string vertex2;
        inFile >> vertex1;
        inFile >> dash;
        inFile >> vertex2;
        theMap.addEdge(vertex1, vertex2); //add edge to an undirected directedGraph
    }
    ////TEMPORARY
    inFile.close();
}

void robustSoln::outputStronglyConnected() {

}

