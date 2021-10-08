#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include "Full_CommentAutomaton.h"
#include <iostream>

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();


public:
    Lexer();
    ~Lexer();
    int maxRead = 0;

    void Run(std::string& input);
    void ToString();
    std::vector<Token*> getTokens();

};

#endif // LEXER_H

