//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_STRINGAUTOMATON_H
#define PROJECT5_STRINGAUTOMATON_H


#include "Automaton.h"

class StringAutomaton : public Automaton{
public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
};


#endif //PROJECT5_STRINGAUTOMATON_H
