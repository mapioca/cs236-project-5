//
// Created by moisa on 6/15/2021.
//

#include "Node.h"

void Node::setID(int givenID) {
    ID = givenID;
}

int Node::getID() {
    return ID;
}

std::set<int> Node::getAdjacencyList() {
    return adjacencyList;
}

void Node::visitNode() {
    isVisited = true;
}

void Node::setPredicates(std::vector<Predicate> predicateList) {
    associatedPredicates = predicateList;
}

std::vector<Predicate> Node::getPredicates() {
    return associatedPredicates;
}

void Node::addToAdjacency(int identifier){
    adjacencyList.insert(identifier);
}

void Node::addEdge(std::pair<int, int> edgeToAdd) {
    associatedEdges.push_back(edgeToAdd);
}

std::vector<std::pair<int, int> > Node::getAssociatedEdges() {
    return associatedEdges;
}
