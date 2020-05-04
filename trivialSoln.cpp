//
// Created by mattb on 5/3/2020.
//

#include "trivialSoln.h"
#include <string>
#include <vector>
#include <algorithm>

trivialSoln::trivialSoln() {
    this->CurrentFileName = "not intilized";
    outFile.open("outputTrivial.txt");
    outFile << "Trivial solution" << endl;
    start = std::chrono::system_clock::now();
}
trivialSoln::~trivialSoln() {
    outFile.close();
}

void trivialSoln::readGraphInputFile(string fileName) { //reads in a directed file
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

void trivialSoln::outputStronglyConnected()  {
    //variable declarations
    vector<string> vertecies = theMap.getVertecies();
    vector<int> numVertecies;
    outFile << "graph \"" << this->CurrentFileName << "\":" << endl;
    ////1) DFS from every vertex, v times
    for (int i = 0; i < vertecies.size(); i++) {
        outFile << "DFS @ " << vertecies[i] << ":" << endl;
        vector<pair<string, string>> edges = theMap.DFS(vertecies[i]);
        if(edges.size() == 0) {outFile << " none" << endl;}
        vector<string> reachableVertecies;
        for (int i = 0; i < edges.size(); i++) {
            outFile << " " << edges[i].first << " - " << edges[i].second << endl;
            //push back the found verteices into a "visited vertecies list"
            string key = edges[i].first;
            if (std::find(reachableVertecies.begin(), reachableVertecies.end(), key) == reachableVertecies.end()) {
                reachableVertecies.push_back(key);
            }
            key = edges[i].second;
            if (std::find(reachableVertecies.begin(), reachableVertecies.end(), key) == reachableVertecies.end()) {
                reachableVertecies.push_back(key);
            }
        }
        numVertecies.push_back(reachableVertecies.size());
    }
    //// 2) If any DFS doesn’t visit all vertices, then graph is not strongly connected
    int vertexNum = theMap.getNumVertex();
    bool isStronglyConnected = true;
    for(int i = 0; i < numVertecies.size(); i++) {
        //numVertecies is reachable vertecies
        //therefor if less than graph's numVertecies, the graph is not strongly connected
        if (numVertecies[i] < vertexNum) {
            isStronglyConnected = false;
            break;
        }
    }
    if(isStronglyConnected) {
        outFile << "Since every vertex can be reached from every other vertex: the graph is strongly connected" << endl;
    }
    else {
        outFile << "Since every vertex cannot be reached from every other vertex: the graph is not strongly connected" << endl;
    }
}
////source: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/?ref=rp

void trivialSoln::outputStronglyConnected(string fileName) {
    theMap.clear();
    readGraphInputFile(fileName);
    outFile << "------------------------" << endl;
    outputStronglyConnected();
}

void trivialSoln::collectTimingData() {
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_A = end - start;
    double lengthA = elapsed_seconds_A.count();
    outFile << "elapsed time: " << lengthA << endl;
}
