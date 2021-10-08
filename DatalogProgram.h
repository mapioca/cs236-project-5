//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_DATALOGPROGRAM_H
#define PROJECT5_DATALOGPROGRAM_H


#include <iostream>
#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include <set>
#include <sstream>


class DatalogProgram {
private:
    std::vector<Predicate> Schemes;
    std::vector<Predicate> Facts;
    std::vector<Predicate> Queries;
    std::vector<Rule> Rules;
    std::set<std::string> Domain;
public:
    std::string toString();
    void addToSchemes(Predicate SchemesInput);
    void addToFacts(Predicate FactsInput);
    void addToDomain(std::string DomainInput);
    void addToRules(Rule RulesInput);
    void addToQueries(Predicate QueriesInput);
    std::vector<Predicate> getSchemes();
    std::vector<Predicate> getFacts();
    std::vector<Predicate> getQueries();
    std::vector<Rule> getRules();


};


#endif //PROJECT5_DATALOGPROGRAM_H
