//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_PARSER_H
#define PROJECT5_PARSER_H


#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>


class Parser {
public:
    Parser(const vector<Token *> &tokener);
    void print();
    void parseDatalog();
    void parseSchemeList(); //Inside function check for a token type or calling another function
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIDList();
    void parseParameter();
    void parseTerminal(vector<Token*> tokens,TokenType type);
    DatalogProgram getDatalog();


private:
    std::vector<Token*> tokener;
    DatalogProgram datalog;
    std::string nameTemp;
    Predicate TempPredicate;
    vector<Parameter> parameterListTemp;
    vector<Predicate> RuleListTemp;
    int index = 0;
    void advance();
    bool Match(TokenType tokens, TokenType tokenType);
};


#endif //PROJECT5_PARSER_H
