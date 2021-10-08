//
// Created by moisa on 6/15/2021.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    std::string IDString = "";
    if(IDString == "Schemes" || IDString == "Facts" || IDString == "Rules" || IDString == "Queries") {
        Serr();
    }
    if (isalnum(input[index])) {
        IDString += input[index];
        inputRead++;
        index++;
        S1(input);
    }
    if(isspace(input[index]) || !isalnum(input[index])){
    }
    else {
        Serr();
    }

}

