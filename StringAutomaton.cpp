//
// Created by moisa on 6/15/2021.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input){
    if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
}
void StringAutomaton::S1(const std::string& input){
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

void StringAutomaton::S2(const std::string& input){
    if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] != '\'' || index >= (int)input.size()){
        return;
    }
}

