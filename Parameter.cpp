//
// Created by moisa on 6/15/2021.
//

#include "Parameter.h"

Parameter::Parameter(std::string inputParameter){
    std::string parameter = inputParameter;
}

std::string Parameter::toString() {
    return parameter;
}

void Parameter::setParameter(std::string parameterString) {
    parameter = parameterString;
}

void Parameter::determineConstant(bool trueOrFalse) {
    isConstant = trueOrFalse;
}

bool Parameter::getBoolType() {
    return isConstant;
}
