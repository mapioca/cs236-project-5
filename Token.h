#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
using namespace std;

enum TokenType {  // All token types
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOF_TOKEN,
    UNDEFINED
};

class Token
{
private:
    std::string tokenValue;
    int lineNumber;
    TokenType tokenType;

public:
    Token(TokenType type, std::string description, int line);
    std::string toString();
    TokenType getType();
    std::string getValue();

};

#endif // TOKEN_H

