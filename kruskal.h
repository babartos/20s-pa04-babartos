//
// Created by mattb on 4/11/2020.
//

#ifndef INC_20S_3353_PA00_KRUSKAL_H
#define INC_20S_3353_PA00_KRUSKAL_H

#include "disjointSetInterface.h"
#include "linkedListDisjointSet.h"
#include "weightedGraph.h"
#include <iostream>
#include <string>

class kruskal {
private:
    disjointSetInterface<Vertex<string>>* vertexList; //used for comparsion
    disjointSetInterface<Edge<string>>* MinSpanningTree; //contents of minumum spanning tree
public:
    kruskal();
    //vector<Edge<string>> kruskalsAlgothrim(WeightedGraph<string>);
    void kruskalsAlgothrim(WeightedGraph<string>);

};

kruskal::kruskal() {
    vertexList = new linkedListDisjointSet<Vertex<string>>;
    MinSpanningTree = new linkedListDisjointSet<Edge<string>>;
}

void kruskal::kruskalsAlgothrim(WeightedGraph<string> theGraph) {
    //to implement
    cout << "here" << endl;

}

#endif //INC_20S_3353_PA00_KRUSKAL_H
