//
// Created by moisa on 6/15/2021.
//

#include "Tuple.h"

bool Tuple::operator<(const Tuple &other) const {
    return this->values < other.values;
}

void Tuple::addToTuple(std::string value) {
    values.push_back(value);
}

std::string Tuple::toString() {
    std::string output = "Nothing here";
    std::stringstream ss;
    for(int i = 0; i < (int)values.size(); i++){
        ss << "| " << values.at(i) << " |";
    }
    output = ss.str();
    return output;
}

std::string Tuple::printTuple(Tuple tuple, Header header) {
    std::stringstream ss;
    std::string output = "";
    for(int i = 0; i < (int)values.size();i++){
        if(i == 0){
            ss << "  "  << header.printAttributeByIndex(i) << "=" << values.at(i);
            if(i < ((int)values.size() - 1)){
                ss << ", ";
            }
            else{
                ss << std::endl;
            }
        }
        else if(i > 0){
            ss << header.printAttributeByIndex(i) << "=" << values.at(i);
            if(i < ((int)values.size() - 1)){
                ss << ", ";
            }
            else{
                ss << std::endl;
            }
        }
    }
    output = ss.str();
    ss.clear();
    return output;
}

std::string Tuple::getValue(int index) {
    return values[index];
}
