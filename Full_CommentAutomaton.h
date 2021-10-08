//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_FULL_COMMENTAUTOMATON_H
#define PROJECT5_FULL_COMMENTAUTOMATON_H


#include "Automaton.h"
#include <cctype>


class Full_CommentAutomaton : public Automaton{
public:
    Full_CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
};


#endif //PROJECT5_FULL_COMMENTAUTOMATON_H
