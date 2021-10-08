//
// Created by moisa on 6/15/2021.
//

#include "DatalogProgram.h"

std::string DatalogProgram::toString() {
    std::string output;
    std::stringstream ss;
    ss << "Schemes(" << Schemes.size() << "):" << std::endl;
    for(int i = 0; i < (int)Schemes.size(); i++){
        ss << "  " << Schemes.at(i).toString() << std::endl;
    }

    ss << "Facts(" << Facts.size() << "):" << std::endl;
    for(int i = 0; i < (int)Facts.size(); i++){
        ss << "  " << Facts.at(i).toString() << "." << std::endl;
    }

    ss << "Rules(" << Rules.size() << "):" << std::endl;
    for(int i = 0; i < (int)Rules.size(); i++){
        ss << "  " << Rules.at(i).toString() << std::endl;
    }

    ss << "Queries(" << Queries.size() << "):" << std::endl;
    for(int i = 0; i < (int)Queries.size(); i++){
        ss << "  " << Queries.at(i).toString() << "?" << std::endl;
    }

    ss << "Domain(" << Domain.size() << "):" << std::endl;
    std::set<std::string>::iterator it;
    for(it = Domain.begin(); it != Domain.end(); ++it)
    {
        ss << "  " << *it << std::endl;
    }
    output = ss.str();
    output.pop_back();
    return output;
}

void DatalogProgram::addToSchemes(Predicate SchemesInput) {
    Schemes.push_back(SchemesInput);
}

void DatalogProgram::addToFacts(Predicate FactsInput) {
    Facts.push_back(FactsInput);
}

void DatalogProgram::addToDomain(std::string DomainInput) {
    Domain.insert(DomainInput);
}

void DatalogProgram::addToRules(Rule RulesInput) {
    Rules.push_back(RulesInput);
}

void DatalogProgram::addToQueries(Predicate QueriesInput) {
    Queries.push_back(QueriesInput);
}

std::vector<Predicate> DatalogProgram::getSchemes() {
    return Schemes;
}

std::vector<Predicate> DatalogProgram::getFacts() {
    return Facts;
}

std::vector<Predicate> DatalogProgram::getQueries() {
    return Queries;
}

std::vector<Rule> DatalogProgram::getRules() {
    return Rules;
}
