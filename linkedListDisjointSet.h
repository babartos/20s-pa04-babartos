//
// Created by mattb on 4/1/2020.
//

#ifndef INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H
#define INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H

#include <iostream>
#include "disjointSetInterface.h"
using namespace std;

//TRIVIAL IMPLEMENTATION
template <typename T>
class linkedListDisjointSet : public disjointSetInterface<T> {
private:
    vector<list<T>> theSet;
public:
    linkedListDisjointSet() {}
    void makeSet(T);
    void unionSets(T,T);
    void printSet();
    list<T>* find(T);
    int getSize();
};

template <typename T>
void linkedListDisjointSet<T>::makeSet(T element) {
    //trivial implementation of make "set" (pushes back a linked list as a set with the element)
    list<T> newList;
    newList.push_back(element);
    theSet.push_back(newList);
}

template <typename T>
void linkedListDisjointSet<T>::unionSets(T element1, T element2) {
    //variable intilization
    list<T> toInsert;
    list<T>* ref1 = find(element1);
    if(ref1 == nullptr) { //if not an exisiting set, make it and then find a ref to it
        makeSet(element1);
        ref1 = find(element1);
    }
    list<T>* ref2 = find(element2);
    if (ref2 == nullptr) {
        makeSet(element2);
        ref2 = find(element2);
    }
    if(ref1 == nullptr || ref2 == nullptr) { //if could not find
        cout << "UNION SETS: elements do not exist inside sets ERROR";
        return;
    }
    //insert contents of ref1 into the "toInsert" linked list
    typename std::list<T>::iterator it = ref1->begin(); //iterator at head of linked list
    for(int i = 0; i < ref1->size(); i++) {
        T element = *it;
        toInsert.push_back(element);
        std::advance(it, 1); //advance iterator
    }
    //insert contents of ref2 into the "toInsert" linked list
    typename std::list<T>::iterator it2 = ref2->begin(); //iterator at head of linked list
    for(int i = 0; i < ref2->size(); i++) {
        T element = *it2;
        toInsert.push_back(element);
        std::advance(it2, 1); //advance iterator
    }
    //linear search for each linked list and delete
    int iterations = theSet.size();
    for (int i = 0; i < iterations; i++) {
        if(theSet[i] == *ref1 || theSet[i] == *ref2) {
            theSet.erase(theSet.begin() + i);
        }
    }
    theSet.push_back(toInsert);
}

template <typename T>
void linkedListDisjointSet<T>::printSet() {
    cout << "{";
    for(int i = 0; i < theSet.size(); i++) {
        list<T> currList = theSet[i];
        cout <<"[";
        typename std::list<T>::iterator it = currList.begin(); //iterator at head of linked list
        for (int j = 0; j < currList.size(); j++) {
            cout << *it << ",";
            std::advance(it, 1); //advance iterator
        }
        cout << "] ";
    }
    cout << "}" << endl;
}

template <typename T>
list<T>* linkedListDisjointSet<T>::find(T findThis) {
    //returns a ref to the element passed in the parameters
    int iterations = theSet.size();
    for (int i = 0; i < iterations; i++) { //goes through the OUTER vector
        list<T> currList = theSet[i];
        typename std::list<T>::iterator it = currList.begin(); //iterator at head of linked list
        for(int j = 0; j < currList.size(); j++) { //goes through INNER vector
            if(findThis == *it) { //we have found the element
                return &theSet[i]; //exit function once found
            }
            std::advance(it, 1); //advance iterator
        }
    }
    list<T>* returnValues = nullptr; //couldnt find anything
    return returnValues;
}

template <typename T>
int linkedListDisjointSet<T>::getSize() { return theSet.size(); }

#endif //INC_20S_3353_PA00_LINKEDLISTDISJOINTSET_H