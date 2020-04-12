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
     T getVertex() const {
         return vertex;
     }
    void setVertex(T value) {
         vertex = value;
     }
    Vertex(T value) {
        vertex = value;
    }
    Vertex() {;}
    bool operator==(const Vertex<T>& passed) const {
         if(passed.getVertex() == this->getVertex()) {return true;}
         else {return false;}
     }
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
    Vertex<T> getfirstVertex() const { return firstVertex; }
    Vertex<T> getsecondVertex() const { return secondVertex; }
    int getWeight() const { return weight; }
    bool operator==(const Edge<T>& passed) const {
        if (passed.getfirstVertex() == this->firstVertex && passed.getsecondVertex() == this->secondVertex &&
            this->weight == passed.getWeight()) {
            return true;
        }
        if (passed.getfirstVertex() == this->secondVertex && passed.getsecondVertex() == this->firstVertex &&
            this->weight == passed.getWeight()) {
            return true;
        }
        return false;
    }
    bool operator<(const Edge<T>& passed) const {
        if(this->getWeight() > passed.getWeight()) { return false; }
        else { return true; }

    }
};




template <typename T>
class WeightedGraph {
private:
    vector<pair<Vertex<T>, vector<Edge<T>>>> myGraph;
    vector<Edge<T>> listOfEdges;
    vector<Vertex<T>> listOfVertecies;
    //[i].first = current vertex
    //[i].second = list of adjacent edges
public:
    void addVertex(T);
    void addVertex(Vertex<T>);
    void addEdge(T, T, unsigned int weight);
    void addEdge(Vertex<T>, Vertex<T>, unsigned int weight);
    vector<Edge<T>> getListOfEdges();
    vector<Vertex<T>> getListOfVertecies();
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
    listOfVertecies.push_back(element);
}

template <typename T>
void WeightedGraph<T>::addEdge(T val1, T val2, unsigned int weight) {
    Vertex<T> v1 = Vertex(val1);
    Vertex<T> v2 = Vertex(val2);
    addEdge(v1, v2, weight);
}

template <typename T>
void WeightedGraph<T>::addEdge(Vertex<T> v1, Vertex<T> v2, unsigned int weight) {
    Edge<T> insertEdge = Edge(v1, v2, weight);
    Edge<T> insertEdge2 = Edge(v2, v1, weight);
    listOfEdges.push_back(insertEdge);
    for(int i = 0; i < myGraph.size(); i++) {
        if(myGraph[i].first.getVertex() == v1.getVertex()) { //makes sure vertecies are equal
            myGraph[i].second.push_back(insertEdge); //push back the
        }
        if(myGraph[i].first.getVertex() == v2.getVertex()) {
            myGraph[i].second.push_back(insertEdge2);
        }
    }
}

template <typename T>
vector<Edge<T>> WeightedGraph<T>::getListOfEdges() {
    return listOfEdges;
}
template <typename T>
vector<Vertex<T>> WeightedGraph<T>::getListOfVertecies() {
    return listOfVertecies;
}
#endif //INC_20S_3353_PA00_WEIGHTEDGRAPH_H
