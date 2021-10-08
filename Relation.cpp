//
// Created by moisa on 6/15/2021.
//

#include "Relation.h"

/*
 * Relation constructor
 * Made up of a name which holds the table/relation name
 * And a header which has the column names (called attributes) for the relation
 */
Relation::Relation(std::string tableName, Header tableHeader) {
    name = tableName;
    header = tableHeader;
}

/*
 * Adds a tuple to a collection of tuples (called rows)
 */
void Relation::addTuple(Tuple tupleToBeAdded) {
    rows.insert(tupleToBeAdded);
}

/*
 * Prints each attribute followed by a "=" and its respective row value
 */
std::string Relation::toString() {
    std::string output = "";
    std::stringstream ss;
    for (Tuple t : rows) {
        if((int)rows.size() != 0){
            ss << t.printTuple(t, header); // print each attribute & value
        }
    }
    output = ss.str();
    return output;
}

/*
 * Sets the name for the relation
 */
void Relation::setRelationName(std::string inputName) {
    name = inputName;
}

/*
 * Sets the values for the relation header
 */
void Relation::setHeaderAttributes(Header atributesList) {
    header = atributesList;
}

/*
 * Retrieves/returns the name of the relation
 */
std::string Relation::getRelationName() {
    return name;
}

/*
 * Selects the rows to be printed according to certain criteria
 *
 */
Relation Relation::selectOne(int index, const std::string& value) {
    Relation newRelation;
    newRelation.setRelationName(name);
    newRelation.setHeaderAttributes(header);
    for(Tuple t: rows){
        if(t.getValue(index) == value){
            newRelation.addTuple(t);
        }
    }
    return newRelation;
}

/*
 * Another method that selects the rows to be printed based on certain criteria
 */
Relation Relation::selectTwo(int index, int theIndex) {
    Relation newRelation;
    newRelation.setRelationName(name);
    newRelation.setHeaderAttributes(header);
    for(Tuple t: rows){
        if(t.getValue(index) == t.getValue(theIndex)){
            newRelation.addTuple(t);
        }
    }
    return newRelation;
}

/*
 * Prints a certain column (based on specified criteria)
 */
Relation Relation::project(std::vector<int> indices) {
    Relation newRelation;
    Header newHeader;
    std::string newName = "";
    for(int i : indices){
        newName += name[i];
        newHeader.addToHeader(header.printAttributeByIndex(i));
    }
    newRelation.setRelationName(newName);
    newRelation.setHeaderAttributes(newHeader);
    for(Tuple t : rows){
        Tuple newTuple;
        for(int i : indices){
            newTuple.addToTuple(t.getValue(i));
        }
        newRelation.addTuple(newTuple);
    }
    return newRelation;
}

/*
 * Renames a specified relation header attribute and thus the relation name
 */
Relation Relation::rename(std::vector<std::string> attributes) {
    Relation newRelation;
    Header newHeader;
    std::string newName = "";
    for(std::string s : attributes){
        newName += s;
        newHeader.addToHeader(s);
    }
    newRelation.setRelationName(newName);
    newRelation.setHeaderAttributes(newHeader);
    newRelation.rows = rows;
    return newRelation;
}

/*
 * Gets the number of rows the relation has
 */
int Relation::getSize() {
    return (int)rows.size();
}

/*
 * Prints the entire relation
 */
void Relation::printTable(Relation relationToPrint) {
    std::cout << "   " << relationToPrint.getRelationName() << std::endl;
    for(Tuple t : rows){
        std::cout << t.toString() << std::endl;
    }
}


Relation Relation::unioner(Relation relationToMatch) {
    Relation newRelation(name, header);
    newRelation.setRows(rows);
    for(Tuple t : relationToMatch.rows){
        if(rows.insert(t).second){
            newRelation.addTuple(t);
            std::cout << t.printTuple(t, header);  //Print same way as Relation | same format
        }
    }
    return newRelation;
}

/*
 * Joins one relation with another and returns joined relation
 * Determine which tuples match - Check by index
 * If tuples from both relations match, combine tuples
 * To combine tuples - take the entire first tuple and add the unique tuple values from the second relation
 * Must use same process as done for columns
 */
Relation Relation::joiner(Relation relationToJoinWith) {
    Relation newJoinedRelation;
    std::map<int, int> matchingColumns;

    //Handling Columns
    if(columnMatcher(relationToJoinWith.getHeader())){
        matchingColumns = columnMatcherX(relationToJoinWith.getHeader());
        std::vector<int> uniqueColumns = findUniqueColumns(relationToJoinWith.getHeader());
        relationToJoinWith.header.setUniqueColumns(uniqueColumns);
    }
    else{
        std::vector<int> uniqueColumns = findUniqueColumns(relationToJoinWith.getHeader());
        relationToJoinWith.header.setUniqueColumns(uniqueColumns);
    }
    Header combinedHeader = headerCombiner(relationToJoinWith.getHeader());
    newJoinedRelation.setHeaderAttributes(combinedHeader);

    //Handling Rows
    newJoinedRelation.setRows(tupleBodyMatcher(relationToJoinWith.getTuples(), relationToJoinWith.getHeader(), matchingColumns));
    return newJoinedRelation;
}

Header Relation::getHeader() {
    return header;
}

std::set<Tuple> Relation::getTuples() {
    return rows;
}

std::vector<int> Relation::findUniqueColumns(Header headerToMatch) {
    std::vector<int> uniqueColumnList;
    bool didMatch = false;
    for(int i = 0; i < (int)headerToMatch.getSize();i++){
        for(int j = 0; j < (int)header.getSize(); j++){
            if(headerToMatch.printAttributeByIndex(i) == header.printAttributeByIndex(j)){
                didMatch = true;
                break;
            }
            else{
                didMatch = false;
            }
        }
        if(!didMatch){
            uniqueColumnList.push_back(i);
        }
    }
    return uniqueColumnList;
}

/*
 * Returns a bool - states whether relation columns match or not
 */
bool Relation::columnMatcher(Header headerToMatch) {
    bool didMatch = false;
    for(int i = 0; i < (int)header.getSize(); i++){
        for(int j  = 0; j < (int)headerToMatch.getSize(); j++){
            if(header.printAttributeByIndex(i) == headerToMatch.printAttributeByIndex(j)){
                didMatch = true;
                break;
            }
        }
    }
    return didMatch;
}

/*
 * Returns a map with the actual indices of each relation header attribute that match
 */
std::map<int, int> Relation::columnMatcherX(Header headerToMatch) {
    std::map<int, int> mapOutput;
    for(int i = 0; i < (int)header.getSize(); i++){
        for(int j  = 0; j < (int)headerToMatch.getSize(); j++){
            if(header.printAttributeByIndex(i) == headerToMatch.printAttributeByIndex(j)){
                mapOutput[i] = j;
                break;
            }
        }
    }
    return mapOutput;
}

Header Relation::headerCombiner(Header headerToMatch) {
    Header newCombinedHeader(header.getAttributes());
    for(int i = 0; i < (int)headerToMatch.getUniqueColumns().size(); i++){
        newCombinedHeader.addToHeader(headerToMatch.printAttributeByIndex(headerToMatch.getUniqueColumns()[i]));
    }
    return newCombinedHeader;
}

bool Relation::tupleMatcher(Tuple thisTupleMatcher, Tuple tupleToMatch, std::map<int, int> matchingColumns) {
    bool didMatch = true;
    std::map<int, int>::iterator itr;
    for (itr = matchingColumns.begin(); itr != matchingColumns.end(); itr++) {
        if (thisTupleMatcher.getValue(itr->first) != tupleToMatch.getValue(itr->second)) {
            didMatch = false;
            break;
        }
    }
    return didMatch;
}

std::set<Tuple> Relation::tupleBodyMatcher(const std::set<Tuple>& rowsToMatch, const Header& headerToMatch, const std::map<int, int>& matchingColumns) {
    std::set<Tuple> newRows;
    for (const Tuple &t1 : rows) {
        for (const Tuple &t2 : rowsToMatch) {
            if (tupleMatcher(t1, t2, matchingColumns)){
                newRows.insert(tuplesCombiner(t1, t2, headerToMatch, matchingColumns));//Keep on going
            }
        }
    }
    return newRows;
}

Tuple Relation::tuplesCombiner(const Tuple& tuple, const Tuple& tupleToMatch, Header headerToMatch, const std::map<int, int>& matchingColumns) {
    std::vector<int> uniqueColumns = headerToMatch.getUniqueColumns();
    Tuple newCombinedTuple = tuple;
    if(tupleMatcher(tuple, tupleToMatch, matchingColumns)){
        std::vector<std::string> uniqueValues = findUniqueTuples(tuple, tupleToMatch, headerToMatch, matchingColumns);
        for(const std::string& s : uniqueValues) {
            newCombinedTuple.addToTuple(s);
        }
    }
    return newCombinedTuple;
}

std::vector<std::string> Relation::findUniqueTuples(const Tuple& tuple1, Tuple tuple2, Header headerToMatch, const std::map<int, int>& matchingColumns) {
    std::vector<int> uniqueColumns = headerToMatch.getUniqueColumns();
    std::vector<std::string> uniqueValues;
    //for (int i : uniqueColumns) {
    if (tupleMatcher(tuple1, tuple2, matchingColumns)) {
        for(int i = 0; i < (int)uniqueColumns.size(); i++){
            uniqueValues.push_back(tuple2.getValue(uniqueColumns[i]));
        }

    }
    //}
    return uniqueValues;
}

void Relation::setRows(std::set<Tuple> rowsToSet) {
    rows = rowsToSet;
}
