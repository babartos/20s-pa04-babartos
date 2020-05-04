//
// Created by mattb on 5/4/2020.
//

#include "robustSoln.h"
#include <string>
#include <vector>
#include <algorithm>

robustSoln::robustSoln() {
    this->CurrentFileName = "not intilized";
    outFile.open("outputRobust.txt");
    outFile << "Robust solution" << endl;
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
    ////Kosaraju’s DFS based simple algorithm that does two DFS traversals:
    ////1) Initialize all vertices as not visited.
    outFile << "graph \"" << this->CurrentFileName << "\":" << endl;
    vector<string> vertexList = theMap.getVertecies();
    vector<pair<string, bool>> visited; //bool value = 0 if not visited; bool value = 1 if visited
    if(vertexList.size() == 0) {cout << "error in making the map" << endl;}
    for(int i = 0; i < vertexList.size(); i++) {
        pair<string, bool> toPush;
        toPush.first = vertexList[i];
        toPush.second = false;
        visited.push_back(toPush);
    }
    ////2) Do a DFS traversal of graph starting from any arbitrary vertex v. If DFS traversal doesn’t visit all vertices, then return false.
    string arbirtaryVertex = vertexList[0];
    vector<pair<string, string>> DFSresults = theMap.DFS(arbirtaryVertex); //DFS from a random vertex
    outFile << "DFS @ arbitrary vertex " << arbirtaryVertex << ":" << endl;
    for(int i = 0; i < DFSresults.size(); i++) {
        string a = DFSresults[i].first;
        string b = DFSresults[i].second;
        outFile << " " << a << " - " << b << endl;
        for(int j = 0; j < visited.size(); j++) {
            if(visited[j].first == a || visited[j].first == b) {
                visited[j].second = true;
            }
        }
    }
    for(int i = 0; i < visited.size(); i++) {
        if(visited[i].second == false) {
            //If DFS traversal doesn’t visit all vertices, then return false.
            outFile << "Since the DFS traversal doesn't visit all vertices, the graph is not strongly connected" << endl;
            return;
        }
    }
    ////3) Reverse/transpose the graph
    theMap.transpose();
    /////4) Mark all vertices as not-visited in reversed graph
    for(int i = 0; i < visited.size(); i++) {
        visited[i].second = false;
    }
    /////5) 5) Do a DFS traversal of reversed graph starting from same vertex v (Same as step 2).
    /// If DFS traversal doesn’t visit all vertices, then return false. Otherwise return true.
    vector<pair<string, string>> DFSresults2 = theMap.DFS(arbirtaryVertex); //DFS from a random vertex
    outFile << "DFS @ arbitrary vertex " << arbirtaryVertex << ": (after transposing graph)" << endl;
    for(int i = 0; i < DFSresults2.size(); i++) {
        string a = DFSresults2[i].first;
        string b = DFSresults2[i].second;
        outFile << " " << a << " - " << b << endl;
        for(int j = 0; j < visited.size(); j++) {
            if(visited[j].first == a || visited[j].first == b) {
                visited[j].second = true;
            }
        }
    }
    if(DFSresults2.size() == 0) {outFile << " none" << endl;}
    for(int i = 0; i < visited.size(); i++) {
        if(visited[i].second == false) {
            //If DFS traversal doesn’t visit all vertices, then return false.
            outFile << "Since the DFS traversal doesn't visit all vertices, the graph is not strongly connected" << endl;
            return;
        }
    }
    outFile << "Since the DFS traversal visits all vertices (transposed or not), the graph is strongly connected" << endl;
}


void robustSoln::outputStronglyConnected(string fileName) {
    theMap.clear();
    outFile << "------------------------" << endl;
    readGraphInputFile(fileName);
    outputStronglyConnected();
}