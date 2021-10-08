//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_RELATION_H
#define PROJECT5_RELATION_H


#include <iostream>
#include <set>
#include <vector>
#include "Header.h"
#include "Tuple.h"
#include "Parameter.h"
#include <map>

class Relation {
public:
    Relation()= default;;
    Relation(std::string tableName, Header tableHeader);
    void addTuple(Tuple tupleToBeAdded);
    std::string toString();
    void setRelationName(std::string inputName);
    void setHeaderAttributes(Header atributesList);
    void setRows(std::set<Tuple> rowsToSet);
    std::string getRelationName();
    Header getHeader();
    std::set<Tuple> getTuples();
    Relation selectOne(int index, const std::string& value);   // Relation column and value to selectOne
    Relation selectTwo(int index, int theIndex);  //Relation columns to selectOne on same values
    Relation project(std::vector<int> indices); //The columns to keep
    Relation rename(std::vector<std::string> attributes);   //Defines the new header
    int getSize();  //Return the number of tuples. Used in the output.
    void printTable(Relation relationToPrint);

    Relation unioner(Relation relationToMatch);    //TODO: #1 Implement union function - remember cant use union word

    Relation joiner(Relation relationToJoinWith);
    std::vector<int> findUniqueColumns(Header headerToMatch);
    std::vector<std::string> findUniqueTuples(const Tuple& tupleMatcher, Tuple tupleToMatch, Header headerToMatch, const std::map<int, int>& matchingColumns);
    Header headerCombiner(Header headerToMatch);
    Tuple tuplesCombiner(const Tuple& tupleOne, const Tuple& tupleTwo, Header headerToMatch, const std::map<int, int>& matchingColumns);
    //bool isJoinable(Tuple tupleOne, Tuple tupleTwo, Header headerOne, Header headerTwo);


private:
    std::string name;   //Name of the relation/table
    std::set<Tuple> rows;   //Data structure holding all the tuples (rows)
    Header header; //Contains a vector of atributes (strings)
    bool columnMatcher(Header headerToMatch);   //DATA MEMBERS SPECIFIC FOR JOINER
    bool tupleMatcher(Tuple thisTupleMatcher, Tuple tupleToMatch, std::map<int, int> matchingColumns); //DATA MEMBERS SPECIFIC FOR JOINER
    std::set<Tuple> tupleBodyMatcher(const std::set<Tuple>& rowsToMatch, const Header& headerToMatch, const std::map<int, int>& matchingColumns);    //DATA MEMBERS SPECIFIC FOR JOINER
    std::map<int, int> columnMatcherX(Header headerToMatch);
};


#endif //PROJECT5_RELATION_H
