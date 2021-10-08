//
// Created by moisa on 6/15/2021.
//

#include "Interpreter.h"

/*
 * Creates a new datalog taking all data from the parser
 */
Interpreter::Interpreter(DatalogProgram datalogFromParser) {
    datalog = datalogFromParser;
    runHelper();
    createRelation();
    createRelationHelper();
}

//For every query we are running all selectOne or selectTwo project, rename
void Interpreter::run() {
    std::cout << "Rule Evaluation" << std::endl;
    int iterations = 0;
    int databaseSize = 0;
    int newDatabaseSize = 0;

    do{
        databaseSize = database.databaseSize();
        for(Rule r : rules){
            std::cout << r << std::endl;    //PRINT THE RULE BEING EVALUATED
            Relation temp = evaluateRule(r);
        }
        newDatabaseSize = database.databaseSize();
        iterations++;
    }while((newDatabaseSize - databaseSize) != 0);
    std::cout << std::endl << "Schemes populated after " << iterations << " passes through the Rules." << std::endl;

    std::cout << std::endl << "Query Evaluation" << endl;
    evaluator(queries);
    queriesPrinter();
}

void Interpreter::runHelper() {
    setSchemes();
    setFacts();
    setRules();
    setQueries();
    setDatabase(schemes, facts);
    /*cout << "[Database Data] " << endl;
    cout << "Schemes: " << endl;
    cout << printSchemes();
    cout << "Facts: " << endl;
    cout << printFacts();
    cout << "Rules: " << endl;
    cout << printRules();
    cout << "Queries" << endl;
    cout << printQueries();*/

}

void Interpreter::setDatabase(std::vector<Predicate> schemesInput, std::vector<Predicate> factsInput) {
    schemes = std::move(schemesInput);
    facts = std::move(factsInput);
}

void Interpreter::setSchemes() {
    schemes = datalog.getSchemes();
}

std::string Interpreter::printSchemes() {
    stringstream ss;
    std::string output;
    for(int i = 0; i < (int)schemes.size(); i++){
        ss << "  " << schemes.at(i).toString() << endl;
    }
    output = ss.str();
    ss.clear();
    return output;
}

void Interpreter::setFacts() {
    facts = datalog.getFacts();
}

std::string Interpreter::printFacts() {
    stringstream ss;
    std::string output;
    for(int i = 0; i < (int)facts.size(); i++){
        ss << "  " << facts.at(i).toString() << endl;
    }
    output = ss.str();
    ss.clear();
    return output;
}

void Interpreter::setRules() {
    rules = datalog.getRules();
}

std::string Interpreter::printRules() {
    stringstream ss;
    string output;
    for(int i = 0; i < (int)rules.size(); i++){
        ss << "  " << rules.at(i).toString() << endl;
    }
    output = ss.str();
    ss.clear();
    return output;
}

void Interpreter::setQueries() {
    queries = datalog.getQueries();
}

std::string Interpreter::printQueries() {
    stringstream ss;
    string output;
    for(int i = 0; i < (int)queries.size(); i++){
        ss << "  " << queries.at(i).toString() << "?" << endl;
    }
    output = ss.str();
    ss.clear();
    return output;
}

/*
 * Evaluates every predicate in the query list using select, project, and rename
 */
Relation Interpreter::evaluatePredicate(Predicate& predicateToEvaluate) {
    Relation newRelation = database.getRelation(predicateToEvaluate.getID());
    std::vector<int> indexes;   //Will pass on to project
    std::vector<std::string> newName; //Will pass on to rename
    bool match = false;
    //Select
    int index = 0;
    std::vector<Parameter> parameterList = predicateToEvaluate.getParameters();
    for(Parameter p : parameterList){
        if(p.getBoolType()){    //true = constant/String
            newRelation = newRelation.selectOne(index, p.toString());
        }
        else{
            for(int i : indexes){
                if(p.toString() == predicateToEvaluate.getParameters()[i].toString()){
                    match = true;
                    newRelation = newRelation.selectTwo(i, index);
                    break;
                }
                else{
                    match = false;
                }
            }
            if(!match){
                indexes.push_back(index);
            }
        }
        index++;
    }
    //Project
    newRelation = newRelation.project(indexes);
    //Rename
    for(int i : indexes){
        newName.push_back(predicateToEvaluate.getParameters()[i].toString());
    }
    newRelation = newRelation.rename(newName);
    return newRelation;
}

/*
 * Creates a new relation + sets the relation name
 * Creates a new header + adds attributes to header
 * Adds relation to database(with empty set of tuples - called rows)
 */
void Interpreter::createRelation() {
    for(int i = 0; i < (int)schemes.size(); i++) {   //For each scheme in the list
        Relation newRelation;
        Header newHeader;
        std::vector<Parameter> parameterList = schemes.at(i).getParameters();
        for (int j = 0; j < (int)parameterList.size(); j++) {  //For each parameter in the predicate
            newHeader.addToHeader(parameterList.at(j).toString());
        }
        newRelation.setRelationName(schemes.at(i).getID());
        newRelation.setHeaderAttributes(newHeader);
        database.addToDatabase(newRelation.getRelationName(), newRelation);
    }
}

/*
 * In charge of creating the tuples + adding tuples to the tuple list
 * Adds tuples to their respective relation
 */
void Interpreter::createRelationHelper() {
    for(int i = 0; i < (int)facts.size(); i++){
        Tuple newTuple;
        std::vector<Parameter> tupleValuesList = facts.at(i).getParameters();
        for(int j = 0; j < (int)tupleValuesList.size(); j++){
            std::string value = tupleValuesList.at(j).toString();
            newTuple.addToTuple(value);
        }
        database.getRelation(facts.at(i).getID()).addTuple(newTuple);
    }
}

/*
 * Evaluates every single query in the queries vector from the datalog
 */
void Interpreter::evaluator(std::vector<Predicate> &listToEval) {
    for(Predicate currentPredicate : listToEval){
        Relation relationToEvaluate = evaluatePredicate(currentPredicate);
        std::string output = queriesPrinterOrganizer(currentPredicate, relationToEvaluate);
        printList.push_back(output);
    }
}

/*
 * Prints all queries from the printList
 */
void Interpreter::queriesPrinter() {
    for(std::string currentString : printList){
        cout << currentString;
    }
}

/*
 * Adds additional format to each query including the question mark, yes/no, the relation size when appropriate
 */
std::string Interpreter::queriesPrinterOrganizer(Predicate currentPredi, Relation relaToEval) {
    stringstream ss;
    string output;
    ss << currentPredi.toString() << "? ";
    if(relaToEval.getSize() == 0){
        ss << "No" << endl;
    }
    else{
        ss << "Yes(" << relaToEval.getSize()  << ")" << endl;
        ss << relaToEval.toString();
    }
    output = ss.str();
    ss.clear();
    return output;
}

Relation Interpreter::evaluateRule(Rule &ruleToEvaluate) {

    //Evaluates the very first predicate in the vector
    Predicate tempBodyPredicate = ruleToEvaluate.getRuleBodyPredicates().at(0);
    Relation temp = evaluatePredicate(tempBodyPredicate);


    for(int i = 1; i < (int)ruleToEvaluate.getRuleBodyPredicates().size(); i++){
        std::vector<Predicate> bodyPredicates = ruleToEvaluate.getRuleBodyPredicates();
        Relation newRelation = evaluatePredicate(bodyPredicates.at(i));
        temp = temp.joiner(newRelation);
    }


    std::vector<int> indexes;   //Indexes contains headParamteres
    for(int i = 0; i < (int)ruleToEvaluate.getRuleHeadPredicate().getParameters().size(); i++){
        for(int j = 0; j < (int)temp.getHeader().getAttributes().size(); j++){
            std::vector<Parameter> headParameters = ruleToEvaluate.getRuleHeadPredicate().getParameters();
            if(headParameters.at(i).toString() == temp.getHeader().getAttributes().at(j)){
                indexes.push_back(j);
            }
        }
    }


    temp = temp.project(indexes);
    std::string name = ruleToEvaluate.getRuleHeadPredicate().getID();
    temp.setRelationName(name);
    temp.setHeaderAttributes(database.getRelation(name).getHeader());

    temp = database.getRelation(name).unioner(temp);

    return temp;
}

void Interpreter::evaluateAllRules() {
    for(Rule ruleToEvaluate : rules){
        evaluateRule(ruleToEvaluate);
    }
}

void Interpreter::optimizedRun() {
    setIdentifier(rules);
    //std::cout << "Rules" << std::endl;
    //printIdentifiedRules();
    edgeBuilder();

    //Set Forward Graph
    Graph forwardGraph = buildDependencyGraph(forwardEdgeList);
    std::cout << "Dependency Graph" << std::endl;
    forwardGraph.toString();

    //Set Reversed Graph
    Graph reverseGraph = buildDependencyGraph(reverseEdgeList);
    std::cout << std:: endl << "Reverse Dependency Graph" << std::endl;
    reverseGraph.toString();
    std::cout << std:: endl;

    //Get postorder from Reversed Graph
    std::stack<int> postorder = reverseGraph.getPostorder();
    printReversedGraphPO(postorder);

    //Get Strongly Connected Components from Forward Graph
    std::queue<std::set<int>> SCCs = forwardGraph.getSCC(postorder);
    std::queue<std::set<int>> sccsCopy = SCCs;
    printAllSCCs(sccsCopy);

    //Evaluate each SCC
    std::cout << std::endl << "Rule Evaluation" << std::endl;
    optimizedRuleEvaluation(SCCs, reverseGraph);

    //Evaluate each Query
    std::cout << std::endl << "Query Evaluation" << endl;
    evaluator(queries);
    queriesPrinter();

}

void Interpreter::setIdentifier(std::vector<Rule> &ruleList){
    for(int i = 0; i < (int)ruleList.size(); i++){
        ruleList[i].setIdentifier(i);
    }
}

void Interpreter::printIdentifiedRules(){
    for(Rule r : rules){
        cout << "# R" << r.getIdentifier() << " " << r.toString()  << std::endl;
    }
}

Graph Interpreter::buildDependencyGraph(std::vector<std::pair<int, int>>& edgeList){
    Graph dependencyGraph;
    std::vector<Node> nodeList = nodeBuilder(edgeList);
    for(Node n : nodeList){
        dependencyGraph.addToGraph(n);
    }
    return dependencyGraph;
}

void Interpreter::edgeBuilder() {

    std::pair<int, int> forwardEdge;
    std::pair<int, int> reverseEdge;

    for(int i = 0; i < (int)rules.size(); i++){
        Node newNode;
        newNode.setID(i);
        newNode.setPredicates(rules.at(i).getRuleBodyPredicates());

        for(Predicate p : newNode.getPredicates()){
            for(int j = 0; j < (int)rules.size(); j++){
                if(p.getID() == rules[j].getRuleHeadPredicate().getID()){
                    forwardEdge.first = i;
                    forwardEdge.second = j;
                    reverseEdge.first = j;
                    reverseEdge.second = i;
                    forwardEdgeList.push_back(forwardEdge);
                    reverseEdgeList.push_back(reverseEdge);
                }
            }
        }
    }
}

std::vector<Node> Interpreter::nodeBuilder(const std::vector<std::pair<int, int>>& edgeList){
    std::vector<Node> nodeList;
    for(int i = 0; i < (int)rules.size(); i++){
        Node newNode;
        newNode.setID(i);
        for(std::pair<int, int> pair : edgeList) {
            if (pair.first == i) {
                newNode.addToAdjacency(pair.second);
            }
        }
        nodeList.push_back(newNode);
    }
    return nodeList;
}


void Interpreter::printSCC(const map<int, set<int>>& SCCMapToPrint) {
    for(pair<const int, set<int>> index : SCCMapToPrint) {
        std::cout << " R" << index.first;
    }

}

void Interpreter::printReversedGraphPO(stack<int> stack) {
    std::stack<int> stackToPrint = stack;
    std::cout << std:: endl;
    cout << "Reversed Graph Postorder: " << endl;
    while(!stackToPrint.empty()) {
        cout << "[ " <<  stackToPrint.top() << " ]";
        stackToPrint.pop();
    }
    cout << endl;
    std::cout << std:: endl;
}

void Interpreter::optimizedRuleEvaluation(queue<set<int>> sccForest, Graph graph) {

    while(!sccForest.empty()) {
        int iterations = 0;
        int databaseSize = 0;
        int newDatabaseSize = 0;
        int databaseSizeDiff = 0;
        set<int> sccToEvaluate = sccForest.front();

        //Print SCC being evaluated
        printSCC(sccToEvaluate);

        //Doing Actual Evaluation
        do{
            databaseSize = database.databaseSize();
            for(int i : sccToEvaluate) {
                printRuleHeadAndBody(rules.at(i));
                evaluateRule(rules.at(i));
            }
            newDatabaseSize = database.databaseSize();
            iterations++;

            int node = *sccToEvaluate.begin();

            if(sccToEvaluate.size() == 1) {
                if(!graph.getGraph().find(node)->second.empty()) {
                    databaseSizeDiff = newDatabaseSize - databaseSize;
                } else {
                    databaseSizeDiff = 0;
                }
            } else {
                databaseSizeDiff = newDatabaseSize - databaseSize;
            }
        } while((databaseSizeDiff != 0));

        //Print Passes
        cout << iterations << " passes: ";
        printSCCNodes(sccToEvaluate);

        //Move on to next SCC
        sccForest.pop();
    }
}

void Interpreter::printSCC(const set<int> &SCCSet) {
    cout << "SCC: ";
    printSCCNodes(SCCSet);
}

void Interpreter::printRuleHeadAndBody(Rule &rule) {
    int count = 1;

    //Prints Rule Head
    cout << rule.getRuleHeadPredicate().toString() << " :- ";

    //Prints Rule Body
    for(Predicate predicate : rule.getRuleBodyPredicates()) {
        cout << predicate.toString();
        if(count < (int)rule.getRuleBodyPredicates().size()) {
            cout << ",";
            count ++;
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

void Interpreter::printSCCNodes(const set<int> &scc) {
    int count = 1;

    for(int i : scc) {
        if(count < (int)scc.size()) {
            cout << " R" << i  << ",";
            count++;
        } else if(count == (int)scc.size()) {
            cout << "R" << i << endl;
        }
    }
}

void Interpreter::printAllSCCs(queue<set<int>> SCCForest) {
    while(!SCCForest.empty()) {
        printSCC(SCCForest.front());
        SCCForest.pop();
    }
}

