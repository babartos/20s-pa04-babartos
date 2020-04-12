#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "graph.h"
#include "disjointSetInterface.h"
#include "linkedListDisjointSet.h"
#include "weightedGraph.h"
#include "kruskal.h"
using namespace std;

////READS INPUT FILE (FILE OF DATA AND INPUT TO A GRAPH)
void readWeightedGraphInputFile(WeightedGraph<string>& theMap, string fileName) { //reads in a directed file
    const char *here = fileName.c_str();
    ifstream inFile(here); //opens g1.txt
    if(!inFile.is_open()) {
        cout << "could not find input file" << endl;
        return;
    }
    int lineNum;
    inFile.ignore();// ignore [
    inFile >> lineNum; //number of vertex
    inFile.ignore(); //ignore ]
    for (int i = 0; i < lineNum; i++) { //add all vertecies ot the graph
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
        unsigned int weight;
        inFile >> vertex1;
        inFile >> dash;
        inFile >> vertex2;
        inFile >> weight;
        theMap.addEdge(vertex1, vertex2, weight); //add edge to a weighted graph
    }
    ////TEMPORARY
    inFile.close();
}

/////READS A CONTROL FILE AND EXECUTES BASED UPON INSTRUCTIONS
void readControlFile(char* controlFileName) {
    ofstream outFile;
    ifstream iFile(controlFileName); //CONTROL FILE NAME (data01.txt)
    if(!iFile.is_open()) {
        cout << "could not open control file: " << controlFileName << endl;
        return;
    }
    while(!iFile.eof()) {
        WeightedGraph<string> globalMap;
        string instruction;
        iFile >> instruction;
        string fileName;
        if(instruction == "readGraph") { ////reads a graph input file (from pa02)
            iFile >> fileName;
            readWeightedGraphInputFile(globalMap, fileName); //reads g1.txt
        }
        else if(instruction == "ow") { ////intilizes output file
            iFile >> fileName;
            outFile.open(fileName);
            if(!outFile.is_open()) { //output file is not open
                cout << "please specify an output file first" << endl;
                return;
            }
        }
        else if(instruction == "makeSet") { ////makes a new disjoint set with the given node
            string newSetNode;
            iFile >> newSetNode;
            //cout << "bfs: " << startNode << endl;
        }
        else if(instruction == "find") { ////finds the given node in the graph and returns a ref
            string nodeToFind;
            iFile >> nodeToFind;
        }
        else if(instruction == "union") { ////finds each disjoint set the element is in then combines both sets
            string arg1, arg2;
            iFile >> arg1;
            iFile >> arg2;
        }
        else if(instruction == "MST") { ////output min spanning tree for a graph text file specified using Kruskal'
            string fileName;
            iFile >> fileName;
            //intilize weighted graph:
            WeightedGraph<string> theMap; //a graph to be used
            readWeightedGraphInputFile(theMap, fileName);
            //execute Kruskal Algo
            kruskal kruskalAccessor;
            vector<Edge<string>> minSpanTree = kruskalAccessor.kruskalsAlgothrim(theMap);
            //output to file
            outFile << "Min Spanning Tree for File \"" << fileName << "\":" << endl;
            for(int i = 0; i < minSpanTree.size(); i++) {
                outFile << " " << minSpanTree[i].getfirstVertex().getVertex() << " - " << minSpanTree[i].getsecondVertex().getVertex();
                outFile << "\tweight: " << minSpanTree[i].getWeight();
                outFile << endl;
            }

        }

    }
    iFile.close();
    outFile.close();
}

////control file is data01.txt (contains a GML; defined by instructions)
int main(int argc, char* argv[]) {
    readControlFile("data01.txt"); //command line arg executes program using a "GML"
    cout << "helloworld";
    return 0;
}