//
// Created by moisa on 6/15/2021.
//

#include "Full_CommentAutomaton.h"

void Full_CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void Full_CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] != '|'){
        Serr();
    }
}

void Full_CommentAutomaton::S2(const std::string& input) {
    if (input[index] != '|' && index < (int)input.size()) {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }
    else {
        type = TokenType::UNDEFINED;
        newLines++;
    }
}

void Full_CommentAutomaton::S3(const std::string& input){
    if (input[index] == '#') {
        inputRead++;
        return;
    }
    else if(input[index] != '#'){
        inputRead++;
        index++;
        S2(input);
    }
    else if(index == (int)input.size()){
        type = TokenType::UNDEFINED;
    }
}
