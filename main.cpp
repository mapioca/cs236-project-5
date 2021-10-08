#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    string line;
    std::string input;
    ifstream myFile(argv[1]);
    if(myFile.is_open())
    {
        while(getline(myFile, line))    //Reads form file
        {
            line += '\n';
            input += line;
        }
        myFile.close();
    }

    else
    {
        cout << "Unable to open file." << endl;
    }

    Lexer* lexer = new Lexer();
    lexer->Run(input);
    //lexer->ToString();

    //Beginning of project-2
    Parser* parser = new Parser(lexer->getTokens());
    parser->parseDatalog();

    //Beginning of project-3
    Interpreter* interpreter = new Interpreter(parser->getDatalog());
    interpreter->optimizedRun();

    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}