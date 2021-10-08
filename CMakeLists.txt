cmake_minimum_required(VERSION 3.16)
project(project5)

set(CMAKE_CXX_STANDARD 14)

add_executable(project5 main.cpp
        ColonDashAutomaton.h ColonDashAutomaton.cpp
        ColonAutomaton.h ColonAutomaton.cpp
        Lexer.h Lexer.cpp
        Token.cpp Token.h
        BadStringAutomaton.cpp BadStringAutomaton.h
        CommentAutomaton.cpp CommentAutomaton.h
        Database.cpp Database.h
        DatalogProgram.cpp DatalogProgram.h
        Full_CommentAutomaton.cpp Full_CommentAutomaton.h
        Graph.cpp Graph.h
        Header.cpp Header.h
        IDAutomaton.cpp IDAutomaton.h
        Interpreter.cpp Interpreter.h
        MatcherAutomaton.cpp MatcherAutomaton.h
        Node.cpp Node.h
        Parameter.cpp Parameter.h
        Parser.cpp Parser.h
        Predicate.cpp Predicate.h
        Relation.cpp Relation.h
        Rule.cpp Rule.h
        StringAutomaton.cpp StringAutomaton.h Tuple.cpp Tuple.h)