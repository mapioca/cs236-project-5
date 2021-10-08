//
// Created by moisa on 6/15/2021.
//

#include "Predicate.h"

void Predicate::setPredicateName(std::string myID) {
    ID = myID;
}

std::string Predicate::getID() {
    return ID;
}

std::string Predicate::toString() {
    std::stringstream ss;
    ss << ID << "(";
    for(int i = 0; i < (int)parameterList.size(); i++){
        if(i < (int)parameterList.size() - 1){
            ss << parameterList.at(i).toString() << ",";
        }
        else if(i >= (int)parameterList.size() - 1){
            ss << parameterList.at(i).toString() << ")";
        }
    }
    return ss.str();
}

Predicate::Predicate(std::string name) {
    ID = name;
}

void Predicate::addToPredicateList(Parameter paramToAdd) {
    parameterList.push_back(paramToAdd);
}

std::vector<Parameter> Predicate::getParameters() {
    return parameterList;
}

void Predicate::setVector(std::vector<Parameter> reciever) {
    parameterList = reciever;
}

void Predicate::clear() {
    ID = "";
    parameterList.clear();
}
