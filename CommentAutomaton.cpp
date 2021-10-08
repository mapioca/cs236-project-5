//
// Created by Moises Carpio on 5/4/21.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        Serr();
    } else {
        S2(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if(input[index] == '\n' || index >= (int)input.size()){
        return;
    }
    else if (input[index] != '\n') {
        inputRead++;
        index++;
        S2(input);
    }
}