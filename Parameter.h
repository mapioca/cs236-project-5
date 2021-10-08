//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_PARAMETER_H
#define PROJECT5_PARAMETER_H


#include <iostream>
#include <vector>

class Parameter {
public:
    Parameter(){};
    Parameter(std::string inputParameter);
    void setParameter(std::string parameterString);
    void determineConstant(bool trueOrFalse);
    std::string toString();
    bool getBoolType();

private:
    std::string parameter;
    bool isConstant;
};


#endif //PROJECT5_PARAMETER_H
