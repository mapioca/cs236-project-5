//
// Created by moisa on 6/15/2021.
//

#include "Rule.h"


std::string Rule::toString() {
    std::stringstream ss;
    ss << headPredicate.toString() << " :- ";
    for(int i = 0; i < (int)bodyPredicate.size(); i++){
        if(i < (int)bodyPredicate.size() - 1) {
            ss << bodyPredicate.at(i).toString() << ",";
        }
        else if(i >= (int)bodyPredicate.size() - 1){
            ss << bodyPredicate.at(i).toString() << ".";
        }
    }
    return ss.str();
}

void Rule::CreatePredicateVector(std::vector<Predicate> predicateVector) {
    bodyPredicate = predicateVector;
}

void Rule::setHeadBody(std::vector<Parameter> parameterVector) {

}

void Rule::addToBodyPredicate(Predicate predicateInput) {
    bodyPredicate.push_back(predicateInput);
}

void Rule::setHeadName(std::string predicateName) {
}

void Rule::setRuleHeadID(std::string RuleHead) {
    headPredicate.setPredicateName(RuleHead);
}

void Rule::setRuleHeadBody(std::vector<Parameter> RuleBody) {
    headPredicate.setVector(RuleBody);
}

std::vector<Predicate> Rule::getRuleBodyPredicates() {
    return bodyPredicate;
}

Predicate Rule::getRuleHeadPredicate() {
    return headPredicate;
}

void Rule::setIdentifier(int givenID) {
    identifier = givenID;
}

int Rule::getIdentifier() const {
    return identifier;
}
