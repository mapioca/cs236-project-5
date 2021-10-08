//
// Created by Moises Carpio on 5/26/21.
//

#ifndef PROJECT5_DATABASE_H
#define PROJECT5_DATABASE_H
#include <map>
#include <iostream>
#include "Relation.h"

class Database {
public:
    Database();
    void addToDatabase(std::string relationName, Relation relation);
    Relation& getRelation(const std::string& toAdd);
    int databaseSize();
private:
    std::map<std::string, Relation> databaseMap;
};


#endif //PROJECT5_DATABASE_H
