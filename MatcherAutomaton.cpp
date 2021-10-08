//
// Created by moisa on 6/15/2021.
//

#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(std::string toMatch, TokenType tokenType)
{
    this->toMatch = toMatch;
    this->type = tokenType;
}



void MatcherAutomaton::S0(const std::string &input) {
    bool isMatch = true;
    inputRead = 0;
    for(int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if(input[i] != toMatch[i])  {
            isMatch = false;
        }
    }
    if(isMatch) {
        inputRead = toMatch.size();
    }
}
