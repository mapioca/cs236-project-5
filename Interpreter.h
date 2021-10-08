//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_INTERPRETER_H
#define PROJECT5_INTERPRETER_H


#include <iostream>
#include <vector>
#include <utility>
#include "Lexer.h"
#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"
#include "Node.h"

class Interpreter {
public:
    Interpreter()= default;
    Interpreter(DatalogProgram datalogFromParser);
    void run();
    void runHelper();
    void optimizedRun();
    Graph buildDependencyGraph(std::vector<std::pair<int, int>>&);
private:
    DatalogProgram datalog;
    Database database;
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::string printSchemes();
    std::string printFacts();
    std::string printQueries();
    std::vector<std::string> printList;
    std::string printRules();
    std::vector<Relation> resultingRelations;
    void setSchemes();
    void setFacts();
    void setRules();
    void setQueries();
    void setDatabase(std::vector<Predicate> schemesInput, std::vector<Predicate> factsInput);
    Relation evaluatePredicate(Predicate& predicateToEvaluate);
    void evaluator(std::vector<Predicate> &listToEval);
    void createRelation();
    void createRelationHelper();
    void queriesPrinter();
    static std::string queriesPrinterOrganizer(Predicate currentPredi, Relation relaToEval);
    //Evaluating Rules Methods
    Relation evaluateRule(Rule &ruleToEvaluate);
    void evaluateAllRules();
    void printIdentifiedRules();

    static void setIdentifier(std::vector<Rule> &ruleList);

    void edgeBuilder();

    std::vector<std::pair<int, int>> forwardEdgeList;
    std::vector<std::pair<int, int>> reverseEdgeList;

    std::vector<Node> nodeBuilder(const vector<pair<int, int>>& nodeList);

    void printSCC(const set<int>& SCCSet);

    static void printSCC(const map<int, set<int>> &SCCMap);

    static void printReversedGraphPO(stack<int> stack);

    void optimizedRuleEvaluation(queue<set<int>> sccForest, Graph graph);

    void printRuleHeadAndBody(Rule &rule);

    void printSCCNodes(const set<int> &set);
};


#endif //PROJECT5_INTERPRETER_H
