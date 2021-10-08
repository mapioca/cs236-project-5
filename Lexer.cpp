#include "Lexer.h"


using namespace std;

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for(auto& i : automata){
        delete i;
    }
    for(auto& token : tokens){
        delete token;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MatcherAutomaton(":", TokenType::COLON));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new CommentAutomaton());
    automata.push_back(new Full_CommentAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new IDAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    Automaton *maxAutomaton = nullptr;
    Automaton *automaton = nullptr;
    Token *newToken = nullptr;

    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.at(0);

        // Whitespace in between tokens
        while(input.size() > 0) {
            if (isspace(input.at(0))) {
                if (input.at(0) == '\n') {
                    lineNumber++;
                }
                input.erase(0, 1);
            }
            else
            {
                break;
            }
        }

        if(input == ""){
            break;
        }

        // Here is the "Parallel" part of the algorithm
        for (int i = 0; i < (int)automata.size(); ++i) {   //   Each automaton runs with the same input foreach automaton in automata {
            automaton = automata.at(i);
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead(); //increment lineNumber by maxAutomaton.NewLinesRead()
            if(newToken->getType() == TokenType::COMMENT){
            }else{
                tokens.push_back(newToken);
            }
        }
        else{  // No automaton accepted input  // Create single character undefined token
            maxRead = 1;    //set maxRead to 1
            newToken = new Token(TokenType::UNDEFINED, input.substr(0,1), lineNumber);
            tokens.push_back(newToken);
        }
        input.erase(0, maxRead);
    }

    newToken = new Token(TokenType::EOF_TOKEN, "", lineNumber);
    tokens.push_back(newToken);
}

void Lexer::ToString(){
    for(int i = 0; i < (int)tokens.size(); i++){
        cout << tokens.at(i)->toString();
    }
    cout << "Total Tokens = " << tokens.size();
}

vector<Token*> Lexer::getTokens() {
    return tokens;
}

