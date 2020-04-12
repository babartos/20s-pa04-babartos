//
// Created by mattb on 4/11/2020.
//

#ifndef INC_20S_3353_PA00_KRUSKAL_H
#define INC_20S_3353_PA00_KRUSKAL_H

#include "disjointSetInterface.h"
#include "linkedListDisjointSet.h"
#include "weightedGraph.h"
#include <iostream>

template <typename T>
class kruskal {
private:
    disjointSetInterface<Vertex<T>>* vertexList; //used for comparsion
    disjointSetInterface<Edge<T>>* MinSpanningTree; //contents of minumum spanning tree
public:
    kruskal();
    vector<Edge<T>> kruskalsAlgothrim(WeightedGraph<T>);
};

template <typename T>
kruskal<T>::kruskal() {
    vertexList = new linkedListDisjointSet<Vertex<T>>;
    MinSpanningTree = new linkedListDisjointSet<Edge<T>>;
}


#endif //INC_20S_3353_PA00_KRUSKAL_H
