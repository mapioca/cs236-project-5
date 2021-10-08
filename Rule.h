//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_RULE_H
#define PROJECT5_RULE_H


#include <iostream>
#include <sstream>
#include <vector>
#include "Predicate.h"

class Rule {
public:
    Rule(){};
    friend std::ostream& operator << (std::ostream& os, Rule& Rule){
        os << Rule.toString();
        return os;
    }
    void setRuleHeadID(std::string RuleHead);
    void setRuleHeadBody(std::vector<Parameter> RuleBody);
    void setRuleBody(std::vector<Predicate> RulePredicateBody);
    std::string toString();
    void setHeadName(std::string predicateName);
    void setHeadBody(std::vector<Parameter> parameterVector);
    void CreatePredicateVector(std::vector<Predicate> predicateVector);
    void addToBodyPredicate(Predicate predicateInput);
    std::vector<Predicate> getRuleBodyPredicates();
    Predicate getRuleHeadPredicate();
    void setIdentifier(int givenID);
    int getIdentifier() const;

private:
    Predicate headPredicate;    //Left-hand side
    std::vector<Predicate> bodyPredicate;   //Right-hand side
    int identifier = 0;
};


#endif //PROJECT5_RULE_H
