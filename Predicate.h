//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_PREDICATE_H
#define PROJECT5_PREDICATE_H


#include <iostream>
#include <vector>
#include <sstream>


#include "Parameter.h"


/*Predicates are made up of two elements:
 * -An ID/name (string)
 * AND
 * -A list of parameters (vector of parameters)*/

class Predicate {
public:
    Predicate(){};
    Predicate(std::string name);
    std::string toString();
    std::string getID();
    std::vector<Parameter> getParameters();
    void clear();
    void setPredicateName(std::string myID);
    void setVector(std::vector<Parameter> reciever);
    void addToPredicateList(Parameter paramToAdd);

private:
    std::string ID;
    std::vector<Parameter> parameterList;

};


#endif //PROJECT5_PREDICATE_H
