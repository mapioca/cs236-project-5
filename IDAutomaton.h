//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_IDAUTOMATON_H
#define PROJECT5_IDAUTOMATON_H


#include "Automaton.h"
#include <cctype>

class IDAutomaton : public Automaton{
public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);

};


#endif //PROJECT5_IDAUTOMATON_H
