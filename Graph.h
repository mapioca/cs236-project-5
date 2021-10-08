//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H


#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include "Node.h"

class Graph {

public:
    Graph()= default;;
    void addToGraph(Node node);
    void toString();
    std::stack<int> getPostorder();
    std::queue<std::set<int>> getSCC(std::stack<int> postorderInput);
    void addToNodesVisited(int key, bool isVisited);
    void addToPostorder(int vertex);
    static bool checkIfVisited(int vertexToCheck, std::map<int, bool> vertexVisitedList);
    void depthFirstSearchSCC(int &vertex);
    void depthFirstSearchPO(int vertex);
    void dfsPostorderFinder(); //Postorder
    void dfsSCCFinder(std::stack<int> postorderInput);    //StronglyConnectComponents
    void markPONodeAsVisited(const int vertex, bool isVisited);
    void dfsHelper(std::map<int, std::set<int>>::iterator vertexItr, std::set<int>& SCC);
    bool getPONodeVisited(int vertex);
    std::map<int, std::set<int>> getGraph();

private:
    //Example  of a map value: R0 (int), R1, R2, R4 (set)
    std::map<int, std::set<int>> graph;//Have one Graph forwardGraph and one Graph reversedGraph (Graph will hold adjacency lists)
    std::map<int, std::set<Node>> nodesGraph;

    std::map<int, bool> nodesVisited;
    std::map<int, bool> postorderVisited;
    std::stack<int> postorderStack;
    std::queue<std::set<int>> SCCQueue;
    void markAsVisited(int &vertex);
};


#endif //PROJECT5_GRAPH_H
