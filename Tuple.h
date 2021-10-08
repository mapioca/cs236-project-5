//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_TUPLE_H
#define PROJECT5_TUPLE_H


#include <iostream>
#include <vector>
#include <sstream>
#include "Header.h"


class Tuple {
public:
    bool operator<(const Tuple & other) const;
    void addToTuple(std::string value);
    std::string toString();
    std::string printTuple(Tuple tuple, Header header);
    std::string getValue(int index);

private:
    std::vector<std::string> values;
};


#endif //PROJECT5_TUPLE_H
