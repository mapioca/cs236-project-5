//
// Created by Victoria Madera on 5/26/21.
//

#include "Database.h"

Database::Database() {
}

void Database::addToDatabase(std::string relationName, Relation relation) {
    databaseMap[relationName] = relation;
}

Relation &Database::getRelation(const std::string &toAdd) {
    return databaseMap.at(toAdd);
}

int Database::databaseSize() {
    int size = 0;
    for(auto p : databaseMap){
        size += (int)p.second.getTuples().size();
    }
    return size;
}


