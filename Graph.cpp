//
// Created by moisa on 6/15/2021.
//

#include "Graph.h"

void Graph::addToGraph(Node node) {
    graph[node.getID()] = node.getAdjacencyList();
}

void Graph::toString() {

    std::map<int, std::set<int> >::iterator mapItr;
    for(mapItr = graph.begin(); mapItr != graph.end(); mapItr++){
        std::cout << "R" << mapItr->first << ":";

        std::set<int>::iterator setItr;
        for(setItr = mapItr->second.begin(); setItr != mapItr->second.end(); setItr++){
            if(setItr == mapItr->second.begin()){
                std::cout << "R" << *setItr;
            }
            else{
                std::cout << ",R" << *setItr;
            }
        }
        std::cout << std::endl;
    }
}

std::stack<int> Graph::getPostorder() {
    dfsPostorderFinder();
    return postorderStack;
}

void Graph::dfsPostorderFinder() {

    //Adds all node to a visited vector - Will be used to check if been visited
    std::map<int, std::set<int> >::iterator mapItr;
    for (mapItr = graph.begin(); mapItr != graph.end(); mapItr++) {
        addToNodesVisited(mapItr->first, false);
    }

    std::map<int, std::set<int> >::iterator it;
    for (it = graph.begin(); it != graph.end(); it++) {
        if (!checkIfVisited(it->first, nodesVisited)) {
            depthFirstSearchPO(it->first);
        }
    }
}

void Graph::depthFirstSearchPO(int vertex) {
    //Marking vertex as visited
    std::map<int, bool>::iterator nodesVisItr;   //NODESVISITED iterator (nodesVisItr)
    nodesVisItr = nodesVisited.find(vertex);
    nodesVisItr->second = true;  //mark v

    std::map<int, std::set<int>>::iterator graphItr; //GRAPH iterator (graphItr)
    graphItr = graph.find(vertex);
    if(!graphItr->second.empty()){   //Is adjacent list empty?
        std::set<int>::iterator adjListItr;    //ADJACENCYLIST iterator (adjListItr)
        for(adjListItr = graphItr->second.begin(); adjListItr != graphItr->second.end(); adjListItr++){    //for each vertex w adjacent from v
            int adjacentVertex = *adjListItr;

            //Adjacent vertex has not been visited
            if(!checkIfVisited(adjacentVertex, nodesVisited)){    //if w is not marked we will mark it
                depthFirstSearchPO(adjacentVertex); //DepthFirstSearch(w)
            }
        }
    }
        addToPostorder(vertex);
        //std::cout << "added to post-order:" << vertex << std::endl;
}


std::queue<std::set<int>> Graph::getSCC(std::stack<int> postorderInput) {
    dfsSCCFinder(postorderInput);
    return SCCQueue;
}

/**
 *
 * Finds the Strongly Connected Components by using
 * DFS in the reversed postorder on the Forward Graph
 *
 * @param postorderInput
 */
void Graph::dfsSCCFinder(std::stack<int> postorderInput) {

    //Adds all node to a visited vector - Will be used to check if been visited
    std::map<int, std::set<int> >::iterator mapItr;
    for (mapItr = graph.begin(); mapItr != graph.end(); mapItr++) {
        markPONodeAsVisited(mapItr->first, false);
    }

    //DFS in reversed postorder order
    while(!postorderInput.empty()) {
        if(!getPONodeVisited(postorderInput.top())) {
            //std::cout << "Running DFS on Node: [" << postorderInput.top() << "] (top of postorder stack)" << std::endl;
            depthFirstSearchSCC(postorderInput.top());
            postorderInput.pop();
        } else {
            //std::cout << "Can't run DFS on this node. Node [" << postorderInput.top() << "] has already been visited." << std::endl;
            postorderInput.pop();
        }
    }
}

void Graph::depthFirstSearchSCC(int &vertex) {

    markPONodeAsVisited(vertex, true);

    std::set<int> SCC;  /** Strongly Connected Component **/
    auto graphVertexItr = graph.find(vertex);   /** Graph Iterator **/

    //No kids - Single SCC
    if(graphVertexItr->second.empty()){
        //std::cout << vertex << " has no kids." << std::endl;
        //std::cout << "Adding Node[" << vertex << "] to the SCC" << std::endl;
        SCC.insert(vertex);
    } else {    //Has kids
        for(int kid : graphVertexItr->second) {
            //Kid has been visited
            if(getPONodeVisited(kid)){
                continue;
            } else {
                dfsHelper(graph.find(kid), SCC);
            }
        }
        //Adding NOde to SCC
        //std::cout << "Adding Node[" << vertex << "] to the SCC" << std::endl;
        SCC.insert(vertex);
    }




    //Adding the SCC-Tree to the forest
    //std::cout << "Added SCC to Forest" << std::endl;
    SCCQueue.push(SCC);
    //Return
}

void Graph::dfsHelper(std::map<int, std::set<int>>::iterator vertexItr, std::set<int>& SCC) {

    //---Marking vertex as visited---//
    markPONodeAsVisited(vertexItr->first, true);

    //If this vertex has children
    if(!vertexItr->second.empty()) {

        //For each vertex children
        for(int kid : vertexItr->second) {
            //If Kid has been visited
            if(getPONodeVisited(kid)){
                continue;
            } else {
                dfsHelper(graph.find(kid), SCC);
            }
        }
        //std::cout << "Adding Node[" << vertexItr->first << "] to the SCC" << std::endl;
        SCC.insert(vertexItr->first);
        return;
    } else {    //The vertex has no children
        //std::cout << vertexItr->first << " has no more children" << std::endl;
        //std::cout << "Adding Node[" << vertexItr->first << "] to the SCC" << std::endl;
        SCC.insert(vertexItr->first);
        return;
    }
}


void Graph::addToNodesVisited(int key, bool isVisited) {
    nodesVisited[key] = isVisited;
}

bool Graph::checkIfVisited(int vertexToCheck, std::map<int, bool> vertexVisitedList) {
    std::map<int, bool>::iterator it;
    it = vertexVisitedList.find(vertexToCheck);
    if(it->second){
        return true;
    }
    else{
        return false;
    }
}

void Graph::addToPostorder(int vertex) {
    postorderStack.push(vertex);
}

void Graph::markPONodeAsVisited(const int vertex, bool isVisited) {
    if(isVisited) {
        //std::cout << "Marked Node[" << vertex << "] as visited" << std::endl;
    } else {
        //std::cout << "Added Node[" << vertex << "] as not visited yet" << std::endl;
    }
    postorderVisited[vertex] = isVisited;
}

bool Graph::getPONodeVisited(int vertex) {
    return postorderVisited.find(vertex)->second;
}

std::map<int, std::set<int>> Graph::getGraph() {
    return graph;
}

