//
// Created by Victoria Madera on 5/6/21.
//

#ifndef PROJECT5_BADSTRINGAUTOMATON_H
#define PROJECT5_BADSTRINGAUTOMATON_H


#include "Automaton.h"

class BadStringAutomaton : public Automaton{
public:
    BadStringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
};


#endif //PROJECT5_BADSTRINGAUTOMATON_H
