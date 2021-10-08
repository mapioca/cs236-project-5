//
// Created by Moises Carpio on 5/6/21.
//

#include "BadStringAutomaton.h"

void BadStringAutomaton::S0(const std::string& input){
    if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
}
void BadStringAutomaton::S1(const std::string& input){
    if(input[index] != '\'' && index < (int)input.size()){
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] == '\''){
        inputRead++;
        index++;
        S2(input);
    }
    else{
        type = TokenType::UNDEFINED;
    }
}

void BadStringAutomaton::S2(const std::string& input){
    if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] != '\'' || index >= (int)input.size()){
        return;
    }
}
