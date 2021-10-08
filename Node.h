//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_NODE_H
#define PROJECT5_NODE_H


#include <vector>
#include <iostream>
#include <set>
#include <utility>
#include "Predicate.h"

class Node {
public:
    void setID(int givenID);
    int getID();
    void addToAdjacency(int identifier);
    void addEdge(std::pair<int, int> edgeToAdd);
    std::set<int> getAdjacencyList();
    void setPredicates(std::vector<Predicate> predicateList);
    std::vector<Predicate> getPredicates();
    std::vector<std::pair<int, int> > getAssociatedEdges();
    void visitNode();
private:
    bool isVisited = false;
    int ID = 0;
    std::vector<Predicate> associatedPredicates;
    std::set<int> adjacencyList;
    std::vector<std::pair<int, int> > associatedEdges;

};


#endif //PROJECT5_NODE_H
