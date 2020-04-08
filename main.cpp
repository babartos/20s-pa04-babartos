#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "graph.h"
#include "disjointSetInterface.h"
#include "linkedListDisjointSet.h"
using namespace std;

////READS INPUT FILE (FILE OF DATA AND INPUT TO A GRAPH)
void readGraphInputFile(graph<string>& theMap, string fileName) { //reads in a directed file
    const char *here = fileName.c_str();
    theMap.setInFile(here);
    ifstream inFile(here); //opens g1.txt
    if(!inFile.is_open()) {
        cout << "could not find input file" << endl;
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
        inFile >> vertex1;
        inFile >> dash;
        inFile >> vertex2;
        theMap.addEdge(vertex1, vertex2); //add edge to an undirected graph
    }
    ////TEMPORARY
    inFile.close();
}

/////READS A CONTROL FILE AND EXECUTES BASED UPON INSTRUCTIONS
void readControlFile(char* controlFileName) {
    graph<string> theMap; //a graph to be used
    ifstream iFile(controlFileName); //CONTROL FILE NAME (data01.txt)
    if(!iFile.is_open()) {
        cout << "could not open file: " << controlFileName << endl;
    }
    while(!iFile.eof()) {
        string instruction;
        iFile >> instruction;
        string fileName;
        if(instruction == "readGraph") { ////reads a graph input file (from pa02)
            iFile >> fileName;
            readGraphInputFile(theMap, fileName); //reads g1.txt
        }
        else if(instruction == "ow") { ////intilizes output file
            iFile >> fileName;
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
        else if(instruction == "dc") { ////girvin newman algo to discover communties
            //cout << ": "  << endl;
        }

    }
    iFile.close();
}


////DRIVER, argv[1] = filename;
////control file is data01.txt (contains a GML)
int main(int argc, char* argv[]) {
    readControlFile(argv[1]); //command line arg executes program
    disjointSetInterface<int>* name = new linkedListDisjointSet<int>;
    name->makeSet(10);
    name->makeSet(15);
    name->makeSet(20);
    name->makeSet(25);
    name->unionSets(15, 25);
    name->printSet();
    name->unionSets(15,20);
    name->printSet();
    cout << "helloworld";
    return 0;
}