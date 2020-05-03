#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "graph.h"
#include "trivialSoln.h"
using namespace std;

//////READS INPUT FILE (FILE OF DATA AND INPUT TO A GRAPH)
//void readInputFile(graph<string>& theMap, string fileName) { //reads in a directed file
//    const char *here = fileName.c_str();
//    theMap.setInFile(here);
//    ifstream inFile(here); //opens g1.txt
//    if(!inFile.is_open()) {
//        cout << "could not find graph input file: " << fileName << endl;
//        return;
//    }
//    int lineNum;
//    inFile.ignore();// ignore [
//    inFile >> lineNum; //number of vertex
//    inFile.ignore(); //ignore ]
//    for (int i = 0; i < lineNum; i++) { //add all vertecies ot the graph
//        string temp;
//        inFile >> temp;
//        theMap.addVertex(temp);
//    }
//    string buffer;
//    getline(inFile, buffer); //ignore the last new line character
//    getline(inFile, buffer); //reads in [undirected]
//    //buffer = "[undirected]"
//    //read in the rest of the file (ALL EDGES)
//    while(!inFile.eof()) {
//        string vertex1;
//        string dash;
//        string vertex2;
//        inFile >> vertex1;
//        inFile >> dash;
//        inFile >> vertex2;
//        theMap.addEdge(vertex1, vertex2); //add edge to an undirected graph
//    }
//    ////TEMPORARY
//    inFile.close();
//}
//
///////READS A CONTROL FILE AND EXECUTES BASED UPON INSTRUCTIONS
//void readControlFile(char* controlFileName) {
//    graph<string> theMap;
//    ifstream iFile(controlFileName); //CONTROL FILE NAME (data01.txt)
//    if (!iFile.is_open()) { //check to see if file is open
//        cout << "could not open specificed file: " << controlFileName << endl;
//        return;
//    }
//    while(!iFile.eof()) {
//        string instruction;
//        iFile >> instruction;
//        string fileName;
//        if(instruction == "or") { ////reads input file
//            iFile >> fileName;
//            readInputFile(theMap, fileName);
//        }
//        else if(instruction == "ow") { ////set the output file
//            iFile >> fileName;
//            theMap.setOutFile(fileName.c_str());
//        }
//        else if(instruction == "bfs") { ////does breadth first search
//            string startNode;
//            iFile >> startNode;
//            //cout << "bfs: " << startNode << endl;
//            theMap.printBFS(startNode);
//        }
//        else if(instruction == "mc") { ////finds shortest path
//            string arg1, arg2;
//            iFile >> arg1;
//            iFile >> arg2;
//            //cout << "mc: " << endl;
//            theMap.makeConnection(arg1, arg2);
//        }
//        else if(instruction == "dfs") { ////does depth first search
//            string arg1;
//            iFile >> arg1;
//            //cout << "dfs: " << arg1 << endl;
//            theMap.printDFS(arg1);
//        }
//    }
//    iFile.close();
//}

////DRIVER, argv[1] = filename;
int main(int argc, char* argv[]) {
    string fileName = "g1.txt";
    //readControlFile(fileName); //command line arg executes program
    trivialSoln firstSolution;
    firstSolution.readGraphInputFile(fileName);
    firstSolution.outputCommunties();

    cout << "helloworld" << endl;
    return 0;
}