#ifndef INC_20S_3353_PA00_GRAPH_H
#define INC_20S_3353_PA00_GRAPH_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <cstring>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <ostream>
#include <math.h>
using namespace std;
//////////////////////////////////
////Class and function definitions
//////////////////////////////////
template <typename T>
class graph {
private:
    ////////////////////////////////////////////////////////////////////////////////////
    //information about my graph implementation:
    //vector to hold each vertex and list of adjacent elements
    //each inner vector is a list
    //at index 0 of the list is a vertex of the graph
    //the rest of the list is adjacent elements from said vertex
    //////////////////////////////////////////////////////////////////////////////////////
    //private member data:
    vector<list<T>> theGraph;
    int numVertex = 0; //num of Vertex added total
    ofstream outFile; //output file
    vector<T> vertexList; //list of every vertex in the graph
    //private functions:
    vector<T> listToVector(list<T>); //given a list returns a vector representation of that list (SO CAN USE [] TO ACCESS)
    void printVectorPair(vector<pair<T,T>>); //for debugging purposes
    bool isContinous(); //if graph is continous returns true; can reach every other node from a node
    list<T> getInnerList(T head); //given a head returns a linked list
    //begin girvin newman calculation functions
    vector<pair<T, double>> getLevelValues(vector<pair<T,T>>); //given a tree returns how many traversals or "levels" to get to head/parent node
    vector<pair<pair<T,T>, double>> calculateEdgeBetweenessWeight(vector<pair<T,double>> , vector<pair<T,T>>); //calculate edge weight/ betweeness value
    vector<vector<T>> identifyCommuntities(); //after edges have been removed, returns a vector of communties
public:
    void addVertex(T vertex); //add a new element or list to the vector. The Head contains the
    void addEdge(T vertex1, T vertex2); //add a connection between two vertecies (undirected)
    void removeEdge(T vertex1 , T vertex2); //delete an edge of the graph
    void printDFS(T start); //does a depth first traversal given the started vertex
    void printBFS(T start); //does a breadth first traversal given the starting vertex
    void printBFS(T start, T end); //finds the shortest path between the start and end
    vector<pair<T, T>> bfs(T start); //does a breadth first search given a starting node, returns a vector with corresponding edges
    vector<pair<pair<T,T>, double>> calculateBetweeness(); //calculates betweeness of all edges of the graph
    void GirvinNewman(); //called when user types dc
    void makeConnection(T arg1, T arg2); //finds shortest path between two elements (calls bfs with T start, T end)
    void makeIntoTree(vector<pair<T,T>>& head); //takes in the head and returns a tree
    void setOutFile(const char*);  //handles file input/output
    void setInFile(const char*);  //handles file input/output
};

////////////////////////////////////////////////////////////
////adds a vertex in the form of a linked list to the graph
////////////////////////////////////////////////////////////
template <typename T>
void graph<T>::addVertex(T vertex) {
    numVertex = numVertex + 1;
    vertexList.push_back(vertex);
    list<T> temp; //to be inserted to the graph
    temp.push_back(vertex); // add the vertex as the head of a list
    theGraph.push_back(temp);
}
/////////////////////////////////////////////////
////adds an undirected edge; adds A->B and B->A
/////////////////////////////////////////////////
template <typename T>
void graph<T>::addEdge(T vertex1, T vertex2) {
    if (vertex1 == vertex2) { return; } //do nothing in this case
    //find vertex 1 in the graph linearly.
    for (int i = 0; i < theGraph.size(); i++) {
        list <T> cmp = theGraph[i];
        if (vertex1 == cmp.front()) {
            theGraph[i].push_back(vertex2); //push back the vertex2 as an edge of vertex 1
        }
        if (vertex2 == cmp.front()) {
            theGraph[i].push_back(vertex1); //push back the vertex1 as an edge of vertex 2
        }
    }
}

/////////////////////////////////
////delete an edge of the graph
//////////////////////////////////
template <typename T>
void graph<T>::removeEdge(T vertex1 , T vertex2) {
    ////remove both of these edges
    pair<T,T> removeThis;
    removeThis.first = vertex1;
    removeThis.second = vertex2;
    pair<T,T> removeThisOppo;
    removeThisOppo.first = vertex2;
    removeThisOppo.second = vertex1;
    ////loop until the edge is found then remove it
    for (int i = 0; i < theGraph.size(); i++) {
        list<T> currentInnerList = theGraph[i];
        T head = currentInnerList.front();
        vector<T> current = listToVector(currentInnerList); //what will overwrite the theGraph[i]
        for(int j = 0; j < current.size(); j++) {
            pair<T,T> cmpEdge; //check if needs to be deleted
            cmpEdge.first = head;
            cmpEdge.second = current[j];
            if(cmpEdge == removeThis || cmpEdge == removeThisOppo) { //edge found
                currentInnerList.remove(current[j]); //deletion of edge
            }
        }
        //overwrite the current inner list
        theGraph[i] = currentInnerList;
    }
}

////////////////////////////////////////////////////////////////////////////
////BREADTH FIRST SEARCH OF ALL PATHS FOR A START VERTEX; OUTPUT TO FILE
///////////////////////////////////////////////////////////////////////////
template <typename T>
void graph<T>::printBFS(T start) {
    if(!outFile.is_open()) { //do nothing if output file is not open
        cout << "please specify an output file first" << endl;
        return;
    }
    outFile << "bfs:" << endl;
    ////variable declarations
    vector<T> shortestPath;
    vector<pair<T, int>> vertexValues; //list of vertecies value and what value they contain
    vector<pair<T, T>> edges; //list of edges between things
    int startOfGraph;
    ///////////////////////////////////////////////////
    //// PUSHES EVERY VERTEX INTO VERTEXVALUES, [0] = starting node (first)
    //// PUSHED A VALUE OF  i = 0 (second)
    ////////////////////////////////////////////////////
    for(int u = 0; u < theGraph.size(); u++) {
        pair<T, int> value;
        list<T> temp = theGraph[u];
        if(temp.front() == start) {
            startOfGraph = u;
            int b = startOfGraph;
            for(b; b < theGraph.size(); b++) {
                list<T> val = theGraph[b];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
            for(int s = 0; s < u; s++) {
                list<T> val = theGraph[s];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
        }

    }
    int i = 1;
    queue<T> priority; //FIFO helps breadth first structure
    /////////////////////////////////////////////////
    ////while there is a vertex such that num[v] = 0
    ///////////////////////////////////////////////
    for(int v = 0; v < vertexValues.size(); v++) {
        if(v == 1) {
            break;
        }
        if (vertexValues[v].second != 0) { continue; } //if value has already been assigned
        vertexValues[v].second = i++;
        priority.push(vertexValues[v].first); //enque the char
        while (!priority.empty()) {
            ////dequeue the top element of the que
            T element = priority.front();
            priority.pop();
            vector<T> adjElements;
            ////find list of vertecies adjacent to element and assign it to adjElements
            for (int q = 0; q < theGraph.size(); q++) {
                list <T> curr = theGraph[q];
                if(curr.front() == element) {
                    vector<T> myVector(curr.begin(), curr.end());
                    myVector.erase(myVector.begin());
                    adjElements = myVector; //pushed adjacent elements into the vector
                    break;
                }
            }
            ////for all vertecies adjacent to element; find the adjacent vertecies
            for (int b = 0; b < adjElements.size(); b++) {
                pair<T, int> currentAdjacentVertex;
                int foundIndex = 0;
                for (int c = 0; c < vertexValues.size(); c++) {
                    if (adjElements[b] == vertexValues[c].first) { ////find the adjacent vertecies
                        currentAdjacentVertex = vertexValues[c];
                        foundIndex = c;
                        //current edge equals
                        pair<T, T> currentEdge;
                        currentEdge.first = element;
                        currentEdge.second = currentAdjacentVertex.first;
                        if (currentAdjacentVertex.second == 0) { //if value is equal to zero
                            vertexValues[foundIndex].second = i;
                            i = i + 1;
                            priority.push(currentAdjacentVertex.first); //enqueue the character
                            ////add to current Edge lsit
                            edges.push_back(currentEdge);
                        }
                        ////pushes back other edges
                        bool contains  = true;
                    }
                } ////element is found, enqueue the element
            }
        }//end while loop
    } //BREADTH FIRST SEARCH COMPLETED
    //OUTPUT ALL EDGES
    for (int w = 0; w < edges.size(); w++) {
        pair<T,T> current = edges[w];
        T a = current.first;
        T b = current.second;
        outFile << " (" << a << " - " << b << ")" << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////
////BREADTH FIRST SEARCH FOR SHORTEST PATH BETWEEN TWO ELEMENTS; OUTPUT TO FILE
///////////////////////////////////////////////////////////////////////////////////
template <typename T>
void graph<T>::printBFS(T start, T end) { //determines shortest distance between two elements on a graph
    ////do nothing if output file is not open
    if(!outFile.is_open()) {
        cout << "please specify an output file first" << endl;
        return;
    }
    ////variable declarations
    vector<T> shortestPath;
    vector<pair<T, int>> vertexValues; //list of vertecies value and what value they contain
    vector<pair<T, T>> edges; //list of edges between things
    int startOfGraph;
    ///////////////////////////////////////////////////
    // PUSHES EVERY VERTEX INTO VERTEXVALUES, [0] = starting node (first)
    // PUSHED A VALUE OF  i = 0 (second)
    ////////////////////////////////////////////////////
    for(int u = 0; u < theGraph.size(); u++) {
        pair<T, int> value;
        list<T> temp = theGraph[u];
        if(temp.front() == start) {
            startOfGraph = u;
            int b = startOfGraph;
            for(b; b < theGraph.size(); b++) {
                list<T> val = theGraph[b];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
            for(int s = 0; s < u; s++) {
                list<T> val = theGraph[s];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
        }
    }
    int i = 1;
    queue<T> priority;
    /////////////////////////////////////////////////
    //while there is a vertex such that num[v] = 0
    ///////////////////////////////////////////////
    for(int v = 0; v < vertexValues.size(); v++) {
        if (vertexValues[v].second != 0) { continue; } //if value has already been assigned
        vertexValues[v].second = i++;
        priority.push(vertexValues[v].first); //enque the char
        while (!priority.empty()) { ////While que is not empty
            //deque top element of the que
            T element = priority.front();
            priority.pop();
            vector<T> adjElements;
            //find list of vertecies adjacent to element
            for (int q = 0; q < theGraph.size(); q++) {
                list <T> curr = theGraph[q];
                if(curr.front() == element) {
                    vector<T> myVector(curr.begin(), curr.end());
                    myVector.erase(myVector.begin());
                    //pushed adjacent elements into the vector
                    adjElements = myVector;
                    break;
                }
            }
            ////for all vertecies adjacent to element; find the adjacent vertecies
            for (int b = 0; b < adjElements.size(); b++) {
                //find the adj element
                pair<T, int> currentAdjacentVertex;
                int foundIndex = 0;
                for (int c = 0; c < vertexValues.size(); c++) {
                    if (adjElements[b] == vertexValues[c].first) {
                        currentAdjacentVertex = vertexValues[c];
                        foundIndex = c;
                        break;
                    }
                } //element is found
                if (currentAdjacentVertex.second == 0) { //if value is equal to zero
                    ////add edge to edge list in the form of pair<T,T>
                    vertexValues[foundIndex].second = i;
                    i = i + 1;
                    priority.push(currentAdjacentVertex.first); //enque the character
                    pair<T, T> currentEdge;
                    currentEdge.first = element;
                    currentEdge.second = currentAdjacentVertex.first;
                    edges.push_back(currentEdge);
                    ////copy the edges from the edge vector into the shortest path vector to get to destination
                    if(currentEdge.second == end) { //this if statement finds the shortest path
                        //insert at start
                        shortestPath.insert(shortestPath.begin(), currentEdge.second);
                        T compr = currentEdge.first;
                        if(start == compr) {shortestPath.insert(shortestPath.begin(), currentEdge.first);}
                        while(start != compr) { ////while start doesnt equal the end
                            ////traverse from T start untill T end is found
                            for(int p = 0; p < edges.size(); p++) {
                                if(edges[p].second == compr) {
                                    shortestPath.insert(shortestPath.begin(), edges[p].second);
                                    compr = edges[p].first;
                                    if(edges[p].first == start) {
                                        compr = start;
                                        shortestPath.insert(shortestPath.begin(), compr);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } //BREADTH FIRST SEARCH COMPLETED
    //OUTPUT THE SHORTEST PATH
    for (int i = 0; i < shortestPath.size(); i++) {
        if(i + 1 < shortestPath.size()) {
            outFile << " (" << shortestPath[i] << " - " << shortestPath[i + 1] << ')' << endl;
        }
    }
}

/////////////////////////////////
////Depth first search; output to file
//////////////////////////////////

template <typename T>
void graph<T>::printDFS(T start) {
    ////variable declarations
    //outFile << "dfs: " << endl;
    vector<T> shortestPath;
    vector<pair<T, int>> vertexValues; //list of vertecies value and what value they contain
    vector<pair<T, T>> edges; //list of edges between things
    int startOfGraph;
    ///////////////////////////////////////////////////
    //// PUSHES EVERY VERTEX INTO VERTEXVALUES, [0] = starting node (first)
    //// PUSHED A VALUE OF  i = 0 (second)
    ////////////////////////////////////////////////////
    for(int u = 0; u < theGraph.size(); u++) {
        pair<T, int> value;
        list<T> temp = theGraph[u];
        if(temp.front() == start) {
            startOfGraph = u;
            int b = startOfGraph;
            for(b; b < theGraph.size(); b++) {
                list<T> val = theGraph[b];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
            for(int s = 0; s < u; s++) {
                list<T> val = theGraph[s];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
        }
    }
    int i = 1;
    stack<T> priority; //used to "push." LIFO structure helps depth first
    /////////////////////////////////////////////////
    ////while there is a vertex such that num[v] = 0
    ///////////////////////////////////////////////
    for(int v = 0; v < vertexValues.size(); v++) {
        if (vertexValues[v].second != 0) { continue; } //if value has already been assigned
        vertexValues[v].second = i++;
        priority.push(vertexValues[v].first); ////push the char
        while (!priority.empty()) { ////While stack is not empty
            //pop top element of the stack
            T element = priority.top();
            vector<T> adjElements;
            //////////////////////////////////////////////
            ////find list of vertecies adjacent to element
            //////////////////////////////////////////////
            for (int q = 0; q < theGraph.size(); q++) {
                list <T> curr = theGraph[q];
                if(curr.front() == element) {
                    vector<T> myVector(curr.begin(), curr.end());
                    myVector.erase(myVector.begin());
                    //pushed adjacent elements into the vector
                    adjElements = myVector;
                    break;
                }
            }
            /////////////////////////////////////////////////////////
            ////for all vertecies adjacent to element push first 1 found
            //////////////////////////////////////////////////////////
            bool found = false;
            for (int b = 0; b < adjElements.size(); b++) {
                //find the adj elements
                pair<T, int> currentAdjacentVertex;
                int foundIndex = 0;
                for (int c = 0; c < vertexValues.size(); c++) {
                    if (adjElements[b] == vertexValues[c].first) {
                        currentAdjacentVertex = vertexValues[c];
                        foundIndex = c;
                        //break;
                        ///////////////////////////////////////
                        ////increment the counter i and push to stack
                        ///////////////////////////////////////
                        if (currentAdjacentVertex.second == 0) { //if value is equal to zero
                            found = true;
                            vertexValues[foundIndex].second = i;
                            i = i + 1;
                            //code to push edge to edge list
                            priority.push(currentAdjacentVertex.first); //enque the character
                            pair<T, T> currentEdge;
                            currentEdge.first = element;
                            currentEdge.second = currentAdjacentVertex.first;
                            edges.push_back(currentEdge);
                        }
                    }
                    if(found){break;} //break a if found a new path (going deep first)
                } //element is found
                if(found) {break;} //break if a found a new path to (going deep first)
            }
            ///only pop if there is no more adjacent vertecies
            if(!found) {
                priority.pop();
            }
        } //end while loop
    } //DEPTH FIRST SEARCH COMPLETED
    ////OUTPUT ALL EDGES
    for (int w = 0; w < edges.size(); w++) {
        pair<T,T> current = edges[w];
        T a = current.first;
        T b = current.second;
        //outFile << " (" << a << " - " << b << ")" << endl;
        std::cout << " (" << a << " - " << b << ")" << endl;

    }
}

//////////////////////////////////////////////////////////////////////////
//// Breadth first search instead of outputting to file returns a vector
///////////////////////////////////////////////////////////////////////////
template <typename T>
vector<pair<T, T>> graph<T>::bfs(T start) {////do nothing if output file is not open
    ////variable declarations
    vector<T> shortestPath;
    vector<pair<T, int>> vertexValues; //list of vertecies value and what value they contain
    vector<pair<T, T>> edges; //list of edges between things
    int startOfGraph;
    bool adjunct = false;
    ///////////////////////////////////////////////////
    //// PUSHES EVERY VERTEX INTO VERTEXVALUES, [0] = starting node (first)
    //// PUSHED A VALUE OF  i = 0 (second)
    ////////////////////////////////////////////////////
    for(int u = 0; u < theGraph.size(); u++) {
        pair<T, int> value;
        list<T> temp = theGraph[u];
        if(temp.front() == start) {
            startOfGraph = u;
            int b = startOfGraph;
            for(b; b < theGraph.size(); b++) {
                list<T> val = theGraph[b];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
            for(int s = 0; s < u; s++) {
                list<T> val = theGraph[s];
                value.first = val.front();
                value.second = 0;
                vertexValues.push_back(value);
            }
        }

    }
    int i = 1;
    queue<T> priority; //FIFO helps breadth first structure
    /////////////////////////////////////////////////
    ////while there is a vertex such that num[v] = 0
    ///////////////////////////////////////////////
    for(int v = 0; v < vertexValues.size(); v++) {
        if(v == 1) {break;}
        if (vertexValues[v].second != 0) { continue; } //if value has already been assigned
        vertexValues[v].second = i++;
        priority.push(vertexValues[v].first); //enque the char
        while (!priority.empty()) {
            ////dequeue the top element of the que
            T element = priority.front();
            priority.pop();
            vector<T> adjElements;
            ////find list of vertecies adjacent to element and assign it to adjElements
            for (int q = 0; q < theGraph.size(); q++) {
                list <T> curr = theGraph[q];
                if(curr.front() == element) {
                    vector<T> myVector(curr.begin(), curr.end());
                    myVector.erase(myVector.begin());
                    adjElements = myVector; //pushed adjacent elements into the vector
                    break;
                }
            }
            ////for all vertecies adjacent to element; find the adjacent vertecies
            for (int b = 0; b < adjElements.size(); b++) {
                pair<T, int> currentAdjacentVertex;
                int foundIndex = 0;
                for (int c = 0; c < vertexValues.size(); c++) {
                    if (adjElements[b] == vertexValues[c].first) { ////find the adjacent vertecies
                        currentAdjacentVertex = vertexValues[c];
                        foundIndex = c;
                        break;
                    }
                } ////element is found, enqueue the element
                if (currentAdjacentVertex.second == 0) { //if value is equal to zero
                    vertexValues[foundIndex].second = i;
                    i = i + 1;
                    priority.push(currentAdjacentVertex.first); //enqueue the character
                    ////add to current Edge lsit
                    pair<T, T> currentEdge;
                    currentEdge.first = element;
                    currentEdge.second = currentAdjacentVertex.first;
                    edges.push_back(currentEdge);
                }

            }
        } //end while
        if(adjunct) {break;}
    } //BREADTH FIRST SEARCH COMPLETED
    //OUTPUT ALL EDGES
    return edges;
}
//////////////////////////////////////////////
//begin GirvinNewman algothrim:
////GIRVIN NEWMAN NOTES:
////betweeness calculation is time consuming so cannot be recalculated each iteration (needs more computing power or time)
////timeout error would be caused w/recalc
////for a smallGraph and mediumGraph (karate data set) size betweeness is recalculated at half size
////for a largeGraph (football data set) size betweeness is calculated once
////"when to stop condition" is when then the graph is no longer continous to a large section of the other
////this is checked in the bool isContinous() function
////basically there will be two large communties and maybe a few smaller ones
////ideally the girvin newman algothrim could be called on these sub communties breaking them up even futher untill a desired size is reached
////was not implemented due to time constraints of yaml file
////severe errors due occur because  of the frequency of edge betweeness calcualtion, however I believe the general steps are correct

template <typename T>
void graph<T>::GirvinNewman() { //steps are outlined in comments
    outFile << "dc:" << endl;
    ////start girvin newman algo:
    /////1) CALCULATE BETWEENESS VALUE
    vector<pair<pair<T, T>, double>> currEdgeBetweeness = calculateBetweeness();
    int everyEdgeinGraphSize = currEdgeBetweeness.size(); //iterate this many times
    ////determine graph size:   (see notes for more info)
    bool smallGraph = false;
    bool medGraph = false;
    bool largeGraph = true;
    if(everyEdgeinGraphSize < 90 && everyEdgeinGraphSize > 20)  { //What I define to be medium size graph
        medGraph = true;
        largeGraph = false;
    }
    else if(everyEdgeinGraphSize < 20) { //what I define to be a small graph
        smallGraph = true;
        largeGraph = false;
    }
    int half = currEdgeBetweeness.size() / 2; //can only have manpower to recalc edges once
    //end graph size
    ////begin edge removal:     (Will go until graph is not continous)
    for(int k = 0; k < everyEdgeinGraphSize; k++) {
        if(smallGraph || medGraph) {
            ////3) THE EDGES BETWEENESS ARE RECALULATED AFTER REMOVAL
            ////This step was ommitted or else a massive timeout would occur; see notes
            if(k == half) {currEdgeBetweeness = calculateBetweeness();}
        }
        double highest = 0.0;
        pair<T, T> deleteEdge;
        int index;
        for (int i = 0; i < currEdgeBetweeness.size(); i++) {  //search for the greatest value edge
            pair<pair<T, T>, double> calc = currEdgeBetweeness[i];
            if (calc.second > highest) {
                highest = calc.second;
                deleteEdge = calc.first;
                index = i;
            }
        }
        //delete edge == highest betweeness edge
        double score = currEdgeBetweeness[index].second;
        currEdgeBetweeness.erase(currEdgeBetweeness.begin() + index);
        ////CHECK IF CONTINOUS BEFORE REMOVING
        bool continous = isContinous();
        if(!continous) { //when to stop conditions; cannot reach another substantial (>2) portion of graph
            ////4) stop when communties are formed
            break;
        }
        /////2) REMOVE EDGES WITH GREATES "BETWEENESS" VALUE
        removeEdge(deleteEdge.first, deleteEdge.second);//remove this edge
        //cout << "removal complete" << endl;
    } //girvin newman steps finished
    //////////////////////////////////////
    ////outputting the found Communtities:
    /////////////////////////////////////
    vector<vector<T>> here = identifyCommuntities(); //finds communties that exist in graph made by girvin newman algo
    vector<T> unid;
    for(int i = 0 ; i < here.size(); i++) {
        vector<T> currCommunity = here[i];
        if(currCommunity.size() == 1) {
            unid.push_back(currCommunity[0]);
        }
        else {
            outFile << " community #" << i << ": ";
            for(int j = 0; j < currCommunity.size(); j++) {
                outFile << currCommunity[j] << " ";
            }
            outFile << endl;
        }
    }
    ////output unidentified nodes (small nodes), would be lessend by more betweeness calculations
    ////for an instance if a node is unconnected with zero edges, output with the unidentified nodes
    outFile << " unidentified: ";
    for(int i = 0; i < unid.size(); i++) {
        T v = unid[i];
        outFile << v << " ";
    }
    outFile << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////function to calculate the betweenes for every edge; pair1 = edge pair2 = edgeBetweenessValue
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
vector<pair<pair<T,T>, double>> graph<T>::calculateBetweeness() {
    ////for ever vertex perform a breadth first search in order to get "trees" starting with said vertex
    vector<pair<pair<T,T>, double>> returnVal;
    ////INTILIZE EVERY VALUE TO IN RETURN VAL TO CORRESPONDING GRAPH LOCATION
    for (int i = 0; i < theGraph.size(); i++) {
        list<T> currentList = theGraph[i];
        T head = currentList.front();
        vector<T> currentVector = listToVector(currentList);
        currentVector.erase(currentVector.begin());
        for(int j = 0; j < currentVector.size(); j++) { //for adj elements
            //var declarations
            pair<T,T> currEdge;
            pair<T,T> oppoEdge;
            currEdge.first = head;
            currEdge.second = currentVector[j];
            oppoEdge.first = currEdge.second;
            oppoEdge.second = currEdge.first;
            bool found = false;
            for(int k = 0 ; k < returnVal.size(); k ++) {
                pair<T,T> currIndexReturnVal = returnVal[k].first;
                if(currIndexReturnVal == currEdge || currIndexReturnVal == oppoEdge) { //found edge do not insert
                    found = true;
                    break;
                }
            }
            if(!found) {
                //add non existing edge
                pair<pair<T,T>, double> element;
                element.first = currEdge;
                element.second = 0.0;
                returnVal.push_back(element);
            }
              ////If edge exists do not add it
        }
    }
    for(int i = 0; i < theGraph.size(); i++) { //for every list in teh graph
        list<T> currList = theGraph[i]; ////CHANGE TO I
        T head = currList.front();
        //get all adj edges
        vector<pair<T,T>> tree = bfs(head);
        makeIntoTree(tree); ////cleans up tree
        //calculate the actual betweeness
        vector<pair<T,double>> levelValues = getLevelValues(tree);
        vector<pair<pair<T,T>, double>> edgeVals = calculateEdgeBetweenessWeight(levelValues, tree); //calcualte the edge weight
        for(int p = 0; p < edgeVals.size(); p++) {
            pair<T,T> currEdge = edgeVals[p].first;
        }
            for(int j = 0; j < returnVal.size(); j++) { //push back found values
                pair<T,T> edge1 = returnVal[j].first;
                for(int k = 0; k < edgeVals.size(); k++) {
                    pair<T,T> edge2 = edgeVals[k].first;
                    if(edge1.first == edge2.first && edge1.second == edge2.second || edge1.second == edge2.first && edge1.first == edge2.second) {
                        if(isnan(edgeVals[k].second)) { //ignore garbage outputs that occasionly happen
                            int x = 5;
                        }
                        else{ //incrment the value of betweeness with the current tree's value
                        returnVal[j].second = edgeVals[k].second + returnVal[j].second; }
                    }
                }
            }
       // } //end else
    } //end for
    ///// AVERAGE THE BETWEENESS AND RETURN THE VALUE
    for(int i = 0; i < returnVal.size(); i++) {
        pair<T,T> currentEdge = returnVal[i].first;
        if(returnVal[i].second != 0) {returnVal[i].second = returnVal[i].second / returnVal.size();}
    }
    return returnVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////takes in a breadth first search, and adds edges not found; Result is a tree with vertex[0] being head of tree
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void graph<T>::makeIntoTree(vector<pair<T,T>>& tree) {
    vector<pair<T,T>> temp;
    for (int i = 0; i < tree.size(); i++) {temp.push_back(tree[i]);}
    /////for every element in the graph
    for(int i = 0; i < theGraph.size(); i++) {
        ////find that linked list
        list<T> curr = theGraph[i];
        T head = curr.front(); ////current element
        vector<T> adjElements = listToVector(curr); ////List of adjacent elements
        adjElements.erase(adjElements.begin());
        vector<pair<T, T>> allEdges;
        for(int j = 0; j < adjElements.size(); j++) {
            pair<T,T> value;
            value.first = head;
            value.second = adjElements[j];
            allEdges.push_back(value);
        }
        ////if there is an adjacent edge not in the tree add it
        for (int j = 0; j < allEdges.size(); j++) {
            pair<T,T> currentEdge = allEdges[j];
            pair<T,T> InverseCurrentEdge;
            InverseCurrentEdge.first = currentEdge.second;
            InverseCurrentEdge.second = currentEdge.first;
            bool found = false;
            int index;
            for (int k = 0; k < tree.size(); k++) {
                pair<T,T> current;
                current.first = tree[k].first;
                current.second = tree[k].second;
                if(current == currentEdge || current == InverseCurrentEdge) {
                    found = true;
                    index = k;
                    break;
                }
            }
            if(!found) {
                tree.push_back(currentEdge);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////
/////given a tree returns how many traversals or "levels" to get to head/parent node
///////////////////////////////////////////////////////////////////////////////////
template <typename T>
vector<pair<T, double>> graph<T>::getLevelValues(vector<pair<T,T>> tree) {
    T head = tree[0].first; //gets access to the head of the graph
    ////values of the vertex levels
    vector<pair<T, double>> vertexLevels;
    pair<T, double> headVertex;
    headVertex.first = head;
    headVertex.second = 1;
    vertexLevels.push_back(headVertex);
    ////values of visited levels
    vector<T> visited;
    visited.push_back(head);
    ////intilize the rest of the vertex level vector
    for (int i = 0; i < theGraph.size(); i++) {
        list<T> currentList = theGraph[i];
        T currentHead = currentList.front();
        pair<T, double> currVertex;
        if(currentHead != head) {
            currVertex.first = currentHead;
            currVertex.second = 0;
            vertexLevels.push_back(currVertex);
        }
    }

    bool allEqualToZero = false;
    int counter = 0;
    vector<T> beenHere;
    while (!allEqualToZero) { ////while there is a value not equal to zero'
        counter = counter + 1;
        vector<T> toVisited;
        for (int i = 0; i < visited.size(); i++) {
            toVisited.push_back(visited[i]);
            T currentElement = visited[i];
            list<T> currentElementAdjacent = getInnerList(currentElement);
            vector<T> here = listToVector(currentElementAdjacent);
            here.erase(here.begin());
            for (int j = 0; j < here.size(); j++) { ////go through every adjacent element
                T theAdajacentElement = here[j];
                for(int k = 0; k < vertexLevels.size(); k++) { ////increment the return vector
                    pair<T,double> currentPair = vertexLevels[k];
                    if(currentPair.first == theAdajacentElement) {
                        ////increment it if not in visited
                        bool inVisited = false;
                        for(int m = 0; m < visited.size(); m++) {
                            if(visited[m] == theAdajacentElement) {
                                inVisited = true; //do nothing if visited
                            }
                        }
                        if(!inVisited) {
                            //if not visited insert the element
                            toVisited.push_back(theAdajacentElement);
                            beenHere.push_back(theAdajacentElement);
                            vertexLevels[k].second = vertexLevels[k].second + 1.0;
                        }
                    }
                }

            }
        }
        ////add toVisited
        visited = toVisited;
        ////see if all vertecies have a value
        for (int n = 0; n < vertexLevels.size(); n++) {
            int sizer = vertexLevels.size();
            if (vertexLevels[n].second == 0) {
                break;
            }
            else if(n >= (vertexLevels.size() - 1 ) ) {
                allEqualToZero = true;
            }
            else if(counter >= 500) {
                allEqualToZero = true;
            }
        }
    }

    return vertexLevels;
}

////////////////////////////////////////////////////////////////////
////This calculates the betweeness value for all edges of a tree
///////////////////////////////////////////////////////////////////
template <typename T>
vector<pair<pair<T,T>, double>> graph<T>::calculateEdgeBetweenessWeight(vector<pair<T,double>> levelValues, vector<pair<T,T>> tree) {
    ////intilize the edgeValues vector
    vector<pair<pair<T,T>, double>> edgeValues; //stores an edge along with a value
    for (int i = 0; i < tree.size(); i++) {
        pair<T, T> edge = tree[i];
        pair<pair<T, T>, double> value;
        value.first = edge;
        value.second = 0.0;
        edgeValues.push_back(value);
    }
    ////find highest value(s) vertecies
    int highest = 0;
    vector<T> greatestValues;
    for(int i = 0; i < levelValues.size(); i++) {
        pair<T, double> currentVertex = levelValues[i];
        int value = currentVertex.second;
        if(value == highest) {
            greatestValues.push_back(currentVertex.first);
        }
        else if(value > highest) {
            highest = value;
            vector<T> newVec;
            newVec.push_back(currentVertex.first);
            greatestValues = newVec;
        }
    }
    ////now have the start nodes in greatestValues
    bool control = true;
    int counter = 0;
    while(control) { ////loop until all edges have a weight
        counter++;
        ////get adjacent vertecies and there values
        vector<pair<T,double>> adjVertecies;
        vector<T> pushToGreatestValues;
        for(int i = 0; i < greatestValues.size(); i++) {
            T currElement = greatestValues[i];
            list<T> adjElements = getInnerList(greatestValues[i]);
            vector<T> vecAdjElements = listToVector(adjElements);
            vecAdjElements.erase(vecAdjElements.begin());
            ////intilize adjVertecies
            adjVertecies.clear(); //get rid of from last repitition
            for(int j = 0; j < vecAdjElements.size(); j++) {
                T currentVertex = vecAdjElements[j];
                for(int k = 0; k < levelValues.size(); k++) {
                    pair<T,double> valVertex = levelValues[k];
                    if(valVertex.first == currentVertex) {
                        bool here = true;
                        for(int z = 0; z < adjVertecies.size(); z++) {
                           if(valVertex.first == adjVertecies[z].first) {
                               here = false;
                           }
                        }
                        if(here) {adjVertecies.push_back(valVertex);}
                    }
                }
            }//adjacent vertecies and values are stored
            ////create adjacent edges values
            vector<pair<T,T>> currEdgesVertexEdges;
            for(int j = 0; j < vecAdjElements.size(); j++) {
                pair<T,T> currEdge;
                currEdge.first = currElement;
                currEdge.second = vecAdjElements[j];
                currEdgesVertexEdges.push_back(currEdge);
            }
            ////find the edge and assign its value
            vector<pair<pair<T,T>, double>> assigned;
            vector<pair<pair<T,T>, double>> toBeAssigned;
            for(int j = 0; j < edgeValues.size(); j++) {
                pair<pair<T,T>, double> currentEdgeWithValue = edgeValues[j];
                for(int k = 0; k < currEdgesVertexEdges.size(); k++) {
                    pair<T, T> myEdge1 = currEdgesVertexEdges[k];
                    pair<T, T> myEdge2 = currentEdgeWithValue.first;
                    if (myEdge1.first == myEdge2.first && myEdge1.second == myEdge2.second || myEdge1.second == myEdge2.first && myEdge1.first == myEdge2.second) {
                        double here = edgeValues[j].second;
                        if(here == 0) {
                            toBeAssigned.push_back(currentEdgeWithValue);
                        }
                        else {
                            assigned.push_back(currentEdgeWithValue);
                        }
                    }
                }
            }
            //TEST
            ////sum up the assigned vector
            for(int j = 0; j < toBeAssigned.size(); j++) {
                pair<pair<T,T>, double> rightHere = toBeAssigned[j];
                pair<T,T> testEdge = rightHere.first;
                double val = rightHere.second;
                double totalVerticalValue = 0;
                for(int m = 0; m < adjVertecies.size(); m++) {
                    bool increment = true;
                    for(int n = 0; n < assigned.size(); n++) {
                        pair<T,T> preEdge = assigned[n].first;
                        T cmpr1 = adjVertecies[m].first;
                        T cmpr2 = preEdge.first;
                        T cmpr3 = preEdge.second;
                        if(preEdge.first == adjVertecies[m].first || preEdge.second == adjVertecies[m].first) {
                            increment = false;
                        }
                    }
                    if(increment) {totalVerticalValue = totalVerticalValue + adjVertecies[m].second;}
                }
                for(int n = 0; n < edgeValues.size(); n++) {
                    pair<T,T> testEdge2 = edgeValues[n].first;
                    if (testEdge.first == testEdge2.first && testEdge.second == testEdge2.second || testEdge.second == testEdge2.first && testEdge.first == testEdge2.second) {
                        T oppositeVertex;
                        if(testEdge2.first == currElement) {
                            oppositeVertex = testEdge2.second;
                        }
                        if(testEdge2.second == currElement) {
                            oppositeVertex = testEdge2.first;
                        }
                        /////push to greatest values if already does not exist
                        bool found = false;
                        for(int u = 0; u < pushToGreatestValues.size(); u++) {
                            if(pushToGreatestValues[u] == oppositeVertex) {
                                found = true;
                                break;
                            }
                        }
                        if(!found) {pushToGreatestValues.push_back(oppositeVertex);} //if not found insert
                        double thelevelVal = 0;
                        for(int x = 0; x < levelValues.size(); x++) {
                            if(levelValues[x].first == oppositeVertex) {
                                thelevelVal = levelValues[x].second;
                            }
                        }
                        double startingLevel = 1; //starts at 1, increment with edges of adjacent values
                        for(int y = 0; y < assigned.size(); y++) {
                            pair<T,T> assignedEdge = assigned[y].first;
                            if(assignedEdge.first != testEdge2.first && assignedEdge.second != testEdge2.second || assignedEdge.second != testEdge2.first && assignedEdge.first != testEdge2.second) {
                                startingLevel = startingLevel + assigned[y].second; //increment the value
                            }
                         }

                        double betweenees = startingLevel * (thelevelVal / totalVerticalValue); //proportion I am using to calculate betweeness
                        edgeValues[n].second = betweenees;
                    }
                }
            }
        }
        greatestValues = pushToGreatestValues; //overwrite the greatestValues vector with our temp vector pushToGreatestValues
        for(int n = 0; n < edgeValues.size(); n++) { //stop condition
            if(edgeValues[n].second == 0) {
                break;
            }
            if(n >= (edgeValues.size() - 1) ) {
                control = false;
            }
            if(counter >= 100) { //just in case break out so doesnt loop indefinitly
                 control = false;
            }
        }
    } //end while
    return edgeValues;
}
//////////////////////////////////////////////////////////////////
////final step of Girvin-Newman algo, retrieves given communties
//////////////////////////////////////////////////////////////////
template <typename T>
vector<vector<T>> graph<T>::identifyCommuntities() {
    //intilize the return value "communityList"
    vector<vector<T>> communityList;
    //intilize the list
    for(int i = 0; i < numVertex; i++) {
        vector<T> dummy;
        communityList.push_back(dummy);
    }
    vector<T> visitedVertex;
    int numNodesVisited = 0;
    int counter = 0;
    while(numNodesVisited < numVertex) {
        ////find an unvisited vertex to bfs at
        T searchNode;
        for(int i = 0; i < theGraph.size(); i++) {
            T currHead = theGraph[i].front();
            bool searchAtThisNode = true;
            ////if the node is in visited vertex; do NOT bfs with it
            for(int j = 0; j < visitedVertex.size(); j++) {
                if(currHead == visitedVertex[j]) {
                    searchAtThisNode = false;
                }
            }
            if(searchAtThisNode) {
                searchNode = currHead;
                break;
            }
        }
        /////bfs at searchNode; add to both visitedVertex
        vector<pair<T,T>> first = bfs(searchNode);
        if(first.size() == 0) { ////if a singular node
            visitedVertex.push_back(searchNode);
            vector<T> current = communityList[counter];
            current.push_back(searchNode);
            communityList[counter] = current;
        }
        vector<T> vecNodes; //value of all visited vertecies
        for(int i = 0; i < first.size(); i++) {
            pair<T,T> edge = first[i];
            bool foundFirst = false;
            bool foundSecond = false;
            for(int j = 0; j < vecNodes.size(); j++) {
                T current = vecNodes[j];
                if(current == edge.first) {
                    foundFirst = true;
                }
                if(current == edge.second) {
                    foundSecond = true;
                }
            }
            if(!foundFirst) {
                vecNodes.push_back(edge.first);
            }
            if (!foundSecond) {
                vecNodes.push_back(edge.second);
            }
        }
        //push back to community list, push back to visited vertecies
        for(int j = 0; j < vecNodes.size(); j++) {
            visitedVertex.push_back(vecNodes[j]);
            vector<T> current = communityList[counter];
            current.push_back(vecNodes[j]);
            communityList[counter] = current;
        }

        //incremebt numNodesVisited and the coutner with new values
        numNodesVisited = visitedVertex.size();
        counter++;
    } //end while loop
    //clean up return vector
    int numLoops = communityList.size();
    for(int i = 0; i < numLoops; i++) {
        int banes = communityList[i].size();
        if(communityList[i].size() == 0) { //erase empty vectors
            communityList.erase(communityList.begin() + i);
        }
        if(communityList[i].size() == 1) {
//            for(int j = 0; j < theGraph.size(); j++) {
//                T head = theGraph[j].front();
//                if
//            }
        }
    }
    return communityList;
}

////end girvin newman functions
//////////////////////////////////////////////////////////////////////////////

//begin "utility functions:"
template <typename T>
vector<T> graph<T>::listToVector(list<T> curr) { //converts a linked list to a vector
    vector<T> myVector(curr.begin(), curr.end());
    return myVector;
}

template <typename T>
void graph<T>::printVectorPair(vector<pair<T,T>> tree) { //prints a vector of pairs to the screen
    cout << "tree" << endl;
    for (int j = 0; j < tree.size(); j++) {
        pair<T,T> current;
        current = tree[j];
        cout << current.first << " - " << current.second << endl;
    }
    cout << "--------------" << endl;
}

template <typename T>
list<T> graph<T>::getInnerList(T head) { //given a node linearly searches for that linked list in the graph
    for (int i = 0; i < theGraph.size(); i++) {
        list<T> curr = theGraph[i];
        if(curr.front() == head) {
            return curr;
        }
    }
}

template <typename T>
void graph<T>::makeConnection(T arg1, T arg2) { ////find shortest path and output to screen
    ////do nothing if output file is not open
    if(!outFile.is_open()) {
        cout << "please specify an output file first" << endl;
        return;
    }
    ////makes shortest path between two vertecies
    outFile << "mc:" << endl;
    printBFS(arg1, arg2);
}

template <typename T>
bool graph<T>::isContinous() {////returns true if every node is connected to another node; our stop condition
    //does a bfs and looks at all nodes it can get to
    vector<pair<T,T>> first = bfs(theGraph[0].front());
    //take the results of bfs and puts all nodes head vertex can get to
    vector<T> vecNodes;
    for(int i = 0; i < first.size(); i++) {
        pair<T,T> edge = first[i];
        bool foundFirst = false;
        bool foundSecond = false;
        for(int j = 0; j < vecNodes.size(); j++) {
            T current = vecNodes[j];
            if(current == edge.first) {
                foundFirst = true;
            }
            if(current == edge.second) {
                foundSecond = true;
            }
        }
        if(!foundFirst) {
            vecNodes.push_back(edge.first);
        }
        if (!foundSecond) {
            vecNodes.push_back(edge.second);
        }
    }
    //compare the size of the vectors, if they arent equal then cannot get to every other node
    bool connected = false;
    if(vecNodes.size() == numVertex) {
        connected = true;
    }
    else {
        /////NOT CONNECTED; CHECK TO MAKE SURE NOT A SUBSTINTIAL COMMUNTIY
        vector<T> communities;
        ////verify that the isolated nodes are community members
        for(int i = 0; i < vertexList.size(); i++) {
            T isItThis = vertexList[i];
            bool found = true;
            for(int j = 0; j < vecNodes.size(); j++) {
                if(vecNodes[j] == isItThis) {
                    found = false;
                }
            }
            if(found) {communities.push_back(isItThis);}
        }
        ////if for all of these the size equals 1, set to false
        bool flow = false;
        for(int c = 0; c < communities.size(); c++) {
            for(int b = 0; b < theGraph.size(); b++) {
                if(communities[c] == theGraph[b].front()) {
                    list<T> current = theGraph[b];
                    if(current.size() == 1) { //if only a single node do not return true!
                        connected = true;
                    }
                    else {
                        connected = false;
                        flow = true;
                    }
                }
                //if(flow) {break;}
            }
        }

    }
    return connected;
}

////////////////////////////////////////////////////
//// Open up a file for input/output in graph class
////////////////////////////////////////////////////
template <typename T>
void graph<T>::setOutFile(const char* fileName) { //
    outFile.open(fileName);
    if(!outFile.is_open()) { //output file is not open
        cout << "please specify an output file first" << endl;
        return;
    }
    //output the file name to the terminal
    outFile << "ow: " << endl;
    outFile << " " << fileName << endl;
}


template <typename T>
void graph<T>::setInFile(const char* fileName) { //output the input file name
    if(!outFile.is_open()) {}
    else {
        outFile << "or: " << endl;
        outFile << " " << fileName << endl;
    }
}

#endif //INC_20S_3353_PA00_GRAPH_H