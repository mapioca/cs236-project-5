//
// Created by Victoria Madera on 5/4/21.
//

#ifndef PROJECT_5_COMMENTAUTOMATON_H
#define PROJECT_5_COMMENTAUTOMATON_H

#include "Automaton.h"


class CommentAutomaton : public Automaton{
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
};


#endif //PROJECT_5_COMMENTAUTOMATON_H