//
// Created by mattb on 4/11/2020.
//

#ifndef INC_20S_3353_PA00_KRUSKAL_H
#define INC_20S_3353_PA00_KRUSKAL_H

#include "disjointSetInterface.h"
#include "linkedListDisjointSet.h"
#include "customDisjointSet.h"
#include "weightedGraph.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;


class kruskal {
private:
    disjointSetInterface<Vertex<string>>* vertexList; //used for comparsion
    disjointSetInterface<Edge<string>>* MinSpanningTree; //contents of minumum spanning tree
public:
    kruskal();
    kruskal(string);
    vector<Edge<string>> kruskalsAlgothrim(WeightedGraph<string>);
    //void kruskalsAlgothrim(WeightedGraph<string>);

};

kruskal::kruskal() { //by default use the trivial disjiont set
    vertexList = new linkedListDisjointSet<Vertex<string>>;
    MinSpanningTree = new linkedListDisjointSet<Edge<string>>;
}

kruskal::kruskal(string choice) {
    if (choice == "custom") {
//        vertexList = new customDisjointSet<Vertex<string>>;
//        MinSpanningTree = new customDisjointSet<Edge<string>>;
    }
    else {
        vertexList = new linkedListDisjointSet<Vertex<string>>;
        MinSpanningTree = new linkedListDisjointSet<Edge<string>>;
    }

}



vector<Edge<string>> kruskal::kruskalsAlgothrim(WeightedGraph<string> theGraph) {
    ////KRUSKALS ALGOTHRIM IMPLEMENTATION TO FIND MST BASED OFF CLASS HANDOUT
    vector<Edge<string>> returnVal;
    vector<Vertex<string>> listOfVertecies = theGraph.getListOfVertecies();
    ////1) for each vertex in theGraph, makeSet();
    for(int i = 0; i < listOfVertecies.size(); i++) {
        Vertex<string> current = listOfVertecies[i];
        vertexList->makeSet(current);
    }
    ////2) sort edges of graph in ascending weight
    vector<Edge<string>> ascendingOrderWeight = theGraph.getListOfEdges(); //result of step 2 stored here
    std::stable_sort(ascendingOrderWeight.begin(), ascendingOrderWeight.end()); //sort in ascending order
    ////3) for each edge in ascending order either add it to MST or discard
    for(int i = 0; i < ascendingOrderWeight.size(); i++) {
        Edge<string> currEdge = ascendingOrderWeight[i];
        //MIGHT NEED TO CHANGE
        Vertex<string> first = currEdge.getfirstVertex();
        string hello = first.getVertex();
        //find set of the first and second vertex in the list
//        list<Vertex<string>>* tempset1 = vertexList->find(currEdge.getfirstVertex().getVertex());
//        list<Vertex<string>>* tempset2 = vertexList->find(currEdge.getsecondVertex().getVertex());
        auto tempset1 = vertexList->find(currEdge.getfirstVertex().getVertex());
        auto tempset2 = vertexList->find(currEdge.getsecondVertex().getVertex());
        if(!(tempset1 == tempset2)) { // if FindSet(u) != FindSet(v)
            //add to MST
            //a) union(u,v)
            string one = currEdge.getfirstVertex().getVertex();
            string two = currEdge.getsecondVertex().getVertex();
            vertexList->unionSets(one, two);
            //b) add to minumum spanning tree
            MinSpanningTree->makeSet(currEdge);
            returnVal.push_back(currEdge);
        }
    }
    return returnVal; //returns a vector of edges in the minumum spanning tree
}

#endif //INC_20S_3353_PA00_KRUSKAL_H
