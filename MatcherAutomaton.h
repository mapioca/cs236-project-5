//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_MATCHERAUTOMATON_H
#define PROJECT5_MATCHERAUTOMATON_H


#include "Automaton.h"


class MatcherAutomaton : public Automaton{
private:
    std::string toMatch = "";

public:
    MatcherAutomaton(std::string toMatch, TokenType tokenType);
    void S0(const std::string &input);
};


#endif //PROJECT5_MATCHERAUTOMATON_H
