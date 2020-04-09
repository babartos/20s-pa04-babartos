//
// Created by mattb on 4/9/2020.
//

#ifndef INC_20S_3353_PA00_WEIGHTEDGRAPH_H
#define INC_20S_3353_PA00_WEIGHTEDGRAPH_H
#include <vector>
#include<iostream>
using namespace std;

template <typename T>
class Vertex {
private:
    T vertex;
public:
     T getVertex(){
         return vertex;
     }
    void setVertex(T value) {
         vertex = value;
     }
    Vertex(T value) {
        vertex = value;
    }
    Vertex() {vertex = NULL;}
};

template <typename T>
class Edge {
private:
    Vertex<T> firstVertex;
    Vertex<T> secondVertex;
    unsigned int weight;
public:
    Edge() {firstVertex = NULL; secondVertex = NULL; weight = 0;}
    Edge(Vertex<T> v1, Vertex<T> v2, unsigned int weight) : firstVertex(v1.getVertex()), secondVertex(v2.getVertex()), weight(weight) {}
};




template <typename T>
class WeightedGraph {
private:
    vector<pair<Vertex<T>, vector<Edge<T>>>> myGraph;
    //[i].first = current vertex
    //[i].second = list of adjacent edges
public:
    void addVertex(T);
    void addVertex(Vertex<T>);
    void addEdge(T, T, unsigned int weight);
    void addEdge(Vertex<T>, Vertex<T>, unsigned int weight);
};

template <typename T>
void WeightedGraph<T>::addVertex(T element) {
    Vertex<T> newVertex = Vertex(element);
    addVertex(newVertex);
}

template <typename T>
void WeightedGraph<T>::addVertex(Vertex<T> element) {
    pair<Vertex<T>, vector<Edge<T>>> newGraphEntry;
    newGraphEntry.first = element;
    vector<Edge<T>> newEdgeList;
    newGraphEntry.second = newEdgeList;
    myGraph.push_back(newGraphEntry);
}

template <typename T>
void WeightedGraph<T>::addEdge(T val1, T val2, unsigned int weight) {
    Vertex<T> v1 = Vertex(val1);
    Vertex<T> v2 = Vertex(val2);
    addEdge(v1, v2, weight);
}

template <typename T>
void WeightedGraph<T>::addEdge(Vertex<T> v1, Vertex<T> v2, unsigned int weight) {
    


}

#endif //INC_20S_3353_PA00_WEIGHTEDGRAPH_H
